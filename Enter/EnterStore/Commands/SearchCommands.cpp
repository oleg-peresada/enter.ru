#include "pch.h"
#include "SearchCommands.h"

using namespace EnterStore::Models;
using namespace EnterStore::Commands;
using namespace EnterStore::Commands::Filters;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Filters;
using namespace Windows::Web::Http::Headers;
using namespace Windows::Data::Json;
using namespace Windows::Storage::Streams;

SearchIsCategory::SearchIsCategory(int id, int count, String^ name) 
	: source_id(id), source_count(count), source_name(name)
{
}

int SearchIsCategory::Id::get()
{
	return source_id;
}

int SearchIsCategory::Count::get()
{
	return source_count;
}

String^ SearchIsCategory::Name::get()
{
	return source_name;
}

SearchProductQuery::SearchProductQuery(int categoryId, SearchSortType sortType, SortCommon sort)
: source_categoryId(categoryId), source_sortType(sortType), source_sort(sort)
{
}

int SearchProductQuery::CategoryId::get()
{
	return source_categoryId;
}

SearchSortType SearchProductQuery::SearchSort::get()
{
	return source_sortType;
}

SortCommon SearchProductQuery::Sort::get()
{
	return source_sort;
}

std::wstring interfaceSearch = L"search";
std::wstring categorySearch = L"get";

SearchCommands::SearchCommands(String^ request, 
	int geoId, int shopId, SearchType typeId) : source_request(request), 
	source_geoId(geoId), source_shopId(shopId), source_typeId(typeId)
{
}

void SearchCommands::ParseInnerCategory(String^ contentValue)
{
	auto vectInner = ref new Vector<SearchIsCategory^>();
	auto categorySource = JsonObject::Parse(contentValue);
	if (categorySource->HasKey("result"))
	{
		auto resultCategory = categorySource->GetNamedObject("result");
		auto valueJson = resultCategory->GetNamedObject(static_cast<int>(this->TypeId).ToString());
		if (valueJson->HasKey("category_list"))
		{
			auto arrayCategory = valueJson->GetNamedArray("category_list");

			for (const auto &itemCategory : arrayCategory)
			{
				auto itemValue = itemCategory->GetObject();

				auto innerModel = ref new SearchIsCategory(itemValue->HasKey("category_id") ? Helpers::ToNumber(itemValue->GetNamedValue("category_id")) : 0,
					itemValue->HasKey("count") ? Helpers::ToNumber(itemValue->GetNamedValue("count")) : 0,
					itemValue->HasKey("category_name") ? Helpers::ToString(itemValue->GetNamedValue("category_name")) : "");
				vectInner->Append(innerModel);
			}
		}
	}

	source_categoryVector = vectInner;
}

IAsyncOperationWithProgress<IVector<ProductCardModels^>^, HttpProgress>^ SearchCommands::SearchAsync()
{
	using namespace concurrency;

	return create_async([=](progress_reporter<HttpProgress> report, cancellation_token token) -> task<IVector<ProductCardModels^>^>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["request"] = this->Request;
		queryParameter["type_id"] = static_cast<int>(this->TypeId).ToString();

		if (this->GeoId != 0) queryParameter["geo_id"] = this->GeoId.ToString();
		if (this->ShopId != 0) queryParameter["shop_id"] = this->ShopId.ToString();

		auto productPost = ref new JsonObject();
		if (this->ProductQuery != nullptr)
		{
			auto data = ref new JsonObject();
			if (ProductQuery->CategoryId != 0)
				data->SetNamedValue("category_id", JsonValue::CreateNumberValue(ProductQuery->CategoryId));

			auto dataSort = ref new JsonObject();
			dataSort->SetNamedValue(safe_cast<SearchSortType>(ProductQuery->SearchSort).ToString(), 
				JsonValue::CreateStringValue(safe_cast<SortCommon>(ProductQuery->Sort).ToString()));
			data->SetNamedValue("sort", dataSort);

			productPost->SetNamedValue("product", data);
		}

		auto baseFilter = ref new HttpBaseProtocolFilter();
		baseFilter->AutomaticDecompression = true;
		baseFilter->CacheControl->ReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto searchFilter = ref new SearchProductFilter(baseFilter, this->GeoId, static_cast<int>(this->TypeId));

		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, 
			queryParameter, 
			productPost->Size > 0 ? HttpMethod::Post : HttpMethod::Get,
			productPost->Size > 0 ? ref new HttpStringContent(productPost->Stringify(), UnicodeEncoding::Utf8, "application/json") : nullptr, 
			searchFilter);
		httpCommand->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto httpOperation = httpCommand->ToCommandOperationAsync(interfaceSearch, categorySearch);

		return create_task(httpOperation, token).then([=](String^ content) -> IVector<ProductCardModels^>^
		{
			if (searchFilter->InnerCategory != nullptr)
			{
				this->ParseInnerCategory(searchFilter->InnerCategory);
			}

			auto searchSource = JsonObject::Parse(content);
			if (searchSource->HasKey("result"))
			{
				auto resultValue = searchSource->GetNamedArray("result");
				auto vect = ref new Vector<ProductCardModels^>();
				for (const auto &item : resultValue)
				{
					auto itemValue = item->GetObject();

					auto productCard = ref new ProductCardModels(itemValue->HasKey("id") ? Helpers::ToNumber(itemValue->GetNamedValue("id")) : 0,
						itemValue->HasKey("name") ? Helpers::ToString(itemValue->GetNamedValue("name")) : "",
						itemValue->HasKey("token") ? Helpers::ToString(itemValue->GetNamedValue("token")) : "",
						itemValue->HasKey("article") ? Helpers::ToString(itemValue->GetNamedValue("article")) : "",
						itemValue->HasKey("bar_code") ? Helpers::ToString(itemValue->GetNamedValue("bar_code")) : "",
						itemValue->HasKey("announce") ? Helpers::ToString(itemValue->GetNamedValue("announce")) : "",
						itemValue->HasKey("rating") ? Helpers::ToString(itemValue->GetNamedValue("rating")) : "",
						itemValue->HasKey("price") ? Helpers::ToNumber(itemValue->GetNamedValue("price")) : 0.0,
						itemValue->HasKey("media_image") ? Helpers::ToString(itemValue->GetNamedValue("media_image")) : "");

					vect->Append(productCard);
				}
				return vect;
			}
			return nullptr;

		}, task_continuation_context::use_current()).then(TaskExceptionExtensions<IVector<ProductCardModels^>^>());
	});
}

String^ SearchCommands::Request::get()
{
	return source_request;
}

int SearchCommands::GeoId::get()
{
	return source_geoId;
}

int SearchCommands::ShopId::get()
{
	return source_shopId;
}

SearchType SearchCommands::TypeId::get()
{
	return source_typeId;
}

SearchProductQuery^ SearchCommands::ProductQuery::get()
{
	return source_productQuery;
}

void SearchCommands::ProductQuery::set(SearchProductQuery^ val)
{
	source_productQuery = val;
}

IVector<SearchIsCategory^>^ SearchCommands::CategoryVector::get()
{
	return source_categoryVector;
}