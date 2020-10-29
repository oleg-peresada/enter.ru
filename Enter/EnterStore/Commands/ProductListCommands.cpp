#include "pch.h"
#include "ProductListCommands.h"

using namespace EnterStore;
using namespace EnterStore::Commands;
using namespace EnterStore::Commands::Filters;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Data::Json;
using namespace Windows::Web::Http;
using namespace Windows::Storage::Streams;

SortProduct::SortProduct(String^ id, SortCommon sortType)
	: source_Id(id), source_sortType(sortType)
{
}

String^ SortProduct::Id::get()
{
	return source_Id;
}

SortCommon SortProduct::SortType::get()
{
	return source_sortType;
}

RangeSelectedFilter::RangeSelectedFilter()
{
}

RangeSelectedFilter::RangeSelectedFilter(String^ filterId, double min, double max)
: source_filterId(filterId), source_min(min), source_max(max)
{
}

String^ RangeSelectedFilter::FilterId::get()
{
	return source_filterId;
}

double RangeSelectedFilter::Min::get()
{
	return source_min;
}

double RangeSelectedFilter::Max::get()
{
	return source_max;
}

MultipleSelectedFilter::MultipleSelectedFilter()
{
}

MultipleSelectedFilter::MultipleSelectedFilter(String^ filterId) : source_filterId(filterId)
{
}

String^ MultipleSelectedFilter::FilterId::get()
{
	return source_filterId;
}

IVector<int>^ MultipleSelectedFilter::SelectedType::get()
{
	return source_SelectedType;
}

void MultipleSelectedFilter::SelectedType::set(IVector<int>^ value)
{
	source_SelectedType = value;
}

BooleanSelectedFilter::BooleanSelectedFilter()
{
}

BooleanSelectedFilter::BooleanSelectedFilter(String^ filterId, bool checked) : source_filterId(filterId), source_checked(checked)
{
}

String^ BooleanSelectedFilter::FilterId::get()
{
	return source_filterId;
}

bool BooleanSelectedFilter::Checked::get()
{
	return source_checked;
}

FilterProductQuery::FilterProductQuery(int category_id, unsigned int limit, unsigned int offset, SortProduct^ sortType)
	: source_categoryId(category_id), source_limit(limit), source_offset(offset), source_sortType(sortType)
{
}

String^ FilterProductQuery::Stringify()
{
	auto filtersArrayJson = ref new JsonArray();
	if (this->Filters != nullptr)
	{
		unsigned int size = this->Filters->Size;
		for (unsigned int i = 0; i < size; i++)
		{
			auto element = this->Filters->GetAt(i);

			auto rangeItem = dynamic_cast<RangeSelectedFilter^>(element);
			if (rangeItem != nullptr)
			{
				auto rangeArray = ref new JsonArray();
				rangeArray->Append(JsonValue::CreateStringValue(rangeItem->FilterId));
				rangeArray->Append(JsonValue::CreateNumberValue(2));
				rangeArray->Append(JsonValue::CreateNumberValue(rangeItem->Min));
				rangeArray->Append(JsonValue::CreateNumberValue(rangeItem->Max));
				rangeArray->Append(JsonValue::CreateBooleanValue(true));

				filtersArrayJson->Append(rangeArray);
			}
			
			auto multipleItem = dynamic_cast<MultipleSelectedFilter^>(element);
			if (multipleItem != nullptr)
			{
				auto multipleArray = ref new JsonArray();
				multipleArray->Append(JsonValue::CreateStringValue(multipleItem->FilterId));
				multipleArray->Append(JsonValue::CreateNumberValue(1));

				auto arrayType = ref new JsonArray();
				unsigned int sizeMultiple = multipleItem->SelectedType->Size;
				for (unsigned int i = 0; i < sizeMultiple; i++)
				{
					arrayType->Append(JsonValue::CreateNumberValue(multipleItem->SelectedType->GetAt(i)));
				}

				multipleArray->Append(arrayType);
				filtersArrayJson->Append(multipleArray);
			}

			auto booleanItem = dynamic_cast<BooleanSelectedFilter^>(element);
			if (booleanItem != nullptr)
			{
				auto booleanArray = ref new JsonArray();
				booleanArray->Append(JsonValue::CreateStringValue(booleanItem->FilterId));
				booleanArray->Append(JsonValue::CreateNumberValue(1));

				byte number = booleanItem->Checked == true ? 1 : 0;
				booleanArray->Append(JsonValue::CreateNumberValue(number));
				booleanArray->Append(JsonValue::CreateBooleanValue(true));
				filtersArrayJson->Append(booleanArray);
			}
		}
	}

	auto sortJson = ref new JsonObject();
	sortJson->SetNamedValue(SortType->Id, JsonValue::CreateStringValue(SortType->SortType.ToString()));

	auto filterJson = ref new JsonObject();
	filterJson->SetNamedValue("limit", JsonValue::CreateNumberValue(Limit));
	filterJson->SetNamedValue("offset", JsonValue::CreateNumberValue(Offset));
	filterJson->SetNamedValue("category_id", JsonValue::CreateNumberValue(CategoryId));

	if (filtersArrayJson->Size > 0)
	{
		filterJson->SetNamedValue("filters", filtersArrayJson);
	}

	filterJson->SetNamedValue("sort", sortJson);

	auto sourceContent = ref new JsonObject();
	sourceContent->SetNamedValue("filter", filterJson);
	return sourceContent->Stringify();
}

int FilterProductQuery::CategoryId::get()
{
	return source_categoryId;
}

unsigned int FilterProductQuery::Limit::get()
{
	return source_limit;
}

unsigned int FilterProductQuery::Offset::get()
{
	return source_offset;
}

SortProduct^ FilterProductQuery::SortType::get()
{
	return source_sortType;
}

IVector<Object^>^ FilterProductQuery::Filters::get()
{
	return source_filters;
}

void FilterProductQuery::Filters::set(IVector<Object^>^ value)
{
	source_filters = value;
}

const std::wstring interface_name = L"listing";
const std::wstring category_name = L"list";

ProductListCommands::ProductListCommands(int regionId, FilterProductQuery^ filter_query)
	: source_regionId(regionId), source_filterQuery(filter_query)
{
}

IAsyncOperationWithProgress<IObservableVector<ProductCardModels^>^, HttpProgress>^ ProductListCommands::ProductOperationAsync()
{
	using namespace concurrency;

	std::map<String^, String^> queryParameter;
	queryParameter["region_id"] = RegionId.ToString();
	queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());

	return create_async([&](progress_reporter<HttpProgress> progress_reporter, cancellation_token token) -> task<IObservableVector<ProductCardModels^>^>
	{
		auto content = ref new HttpStringContent(FilterSource->Stringify(), UnicodeEncoding::Utf8, "application/json");

		auto baseFilter = ref new HttpBaseProtocolFilter();
		baseFilter->AutomaticDecompression = true;
		auto productFilter = ref new ProductListFilters(baseFilter);
		productFilter->GeoId = 14974;

		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter, HttpMethod::Post, content, productFilter);
		httpCommand->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto operation = httpCommand->ToCommandOperationAsync(interface_name, category_name);

		return create_task(operation, token).then([&](String^ content) -> IObservableVector<ProductCardModels^>^
		{
			auto vect = ref new Vector<ProductCardModels^>();
			auto contentJson = JsonObject::Parse(content);
			if (contentJson->HasKey("result") && contentJson->GetNamedValue("result")->ValueType == JsonValueType::Array)
			{
				auto arrayResult = contentJson->GetNamedArray("result");
				for (const auto &item : arrayResult)
				{
					auto element = item->GetObject();
					auto productCard = ref new ProductCardModels(element->HasKey("id") ? Helpers::ToNumber(element->GetNamedValue("id")) : 0,
						element->HasKey("name") ? Helpers::ToString(element->GetNamedValue("name")) : "",
						element->HasKey("token") ? Helpers::ToString(element->GetNamedValue("token")) : "",
						element->HasKey("article") ? Helpers::ToString(element->GetNamedValue("article")) : "",
						element->HasKey("bar_code") ? Helpers::ToString(element->GetNamedValue("bar_code")) : "",
						element->HasKey("announce") ? Helpers::ToString(element->GetNamedValue("announce")) : "",
						element->HasKey("rating") ? Helpers::ToString(element->GetNamedValue("rating")) : "",
						element->HasKey("price") ? Helpers::ToNumber(element->GetNamedValue("price")) : 0.0,
						element->HasKey("media_image") ? Helpers::ToString(element->GetNamedValue("media_image")) : "");

					auto vectPromo = ref new Vector<PromoCard^>();
					if (element->HasKey("label"))
					{
						if (element->GetNamedValue("label")->ValueType == JsonValueType::Array)
						{
							auto promoArray = element->GetNamedArray("label");
							unsigned int size = promoArray->Size;

							for (unsigned int i = 0; i < size; i++)
							{
								if (promoArray->GetAt(i)->ValueType == JsonValueType::Object)
								{
									auto elementPromo = promoArray->GetAt(i)->GetObject();
									auto promoLabel = ref new PromoCard(elementPromo->HasKey("id") ? Helpers::ToNumber(elementPromo->GetNamedValue("id")) : 0,
										elementPromo->HasKey("name") ? Helpers::ToString(elementPromo->GetNamedValue("name")) : "",
										elementPromo->HasKey("media_image") ? Helpers::ToString(elementPromo->GetNamedValue("media_image")) : "");
									vectPromo->Append(promoLabel);
								}
							}
						}
					}

					if (element->HasKey("state"))
					{
						if (element->GetNamedObject("state")->ValueType == JsonValueType::Object)
						{
							auto stateElement = element->GetNamedObject("state");
							auto stateCard = ref new StateCard(stateElement->HasKey("is_buyable") ? Helpers::ToBool(stateElement->GetNamedValue("is_buyable")) : false);

							productCard->State = stateCard;
						}
					}
					else
					{
						productCard->State = ref new StateCard(false);
					}

					productCard->LabelCard = vectPromo;
					vect->Append(productCard);
				}
			}

			return vect;
		}, task_continuation_context::use_current()).then(TaskExceptionExtensions<IObservableVector<ProductCardModels^>^>());
	});
}

int ProductListCommands::RegionId::get()
{
	return source_regionId;
}

FilterProductQuery^ ProductListCommands::FilterSource::get()
{
	return source_filterQuery;
}