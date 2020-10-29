#include "pch.h"
#include "FilterProductCommands.h"

using namespace EnterStore;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Data::Json;

const std::wstring interfaceNameFilter = L"listing";
const std::wstring categoryNameFilter = L"filter";

const std::wstring interfaceNameBanner = L"promo";
const std::wstring categoryNameBanner = L"get";

FilterProductCommands::FilterProductCommands(int regionId, int categoryId)
	: source_regionId(regionId), source_categoryId(categoryId)
{
}

IAsyncOperationWithProgress<IVector<FilterProductModels^>^, HttpProgress>^ FilterProductCommands::FilterAsync()
{
	using namespace concurrency;

	return create_async([&](progress_reporter<HttpProgress> reporter, cancellation_token token)-> task<IVector<FilterProductModels^>^>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["region_id"] = RegionId.ToString();
		queryParameter["category_id"] = CategoryId.ToString();
		queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());

		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter);
		httpCommand->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto operation = httpCommand->ToCommandOperationAsync(interfaceNameFilter, categoryNameFilter);

		return create_task(operation, token).then([&](String^ content) -> IVector<FilterProductModels^>^
		{
			auto vect = ref new Vector<FilterProductModels^>();
			auto json = JsonObject::Parse(content);
			
			if (json->HasKey("result") && json->GetNamedValue("result")->ValueType == JsonValueType::Array)
			{
				auto jsonResult = json->GetNamedArray("result");
				for (const auto &item : jsonResult)
				{
					auto itemValue = item->GetObject();
					auto filterModel = ref new FilterProductModels(itemValue->HasKey("filter_id") ? Helpers::ToString(itemValue->GetNamedValue("filter_id")) : "",
						itemValue->HasKey("name") ? Helpers::ToString(itemValue->GetNamedValue("name")) : "",
						itemValue->HasKey("type_id") ? Helpers::ToNumber(itemValue->GetNamedValue("type_id")) : 0,
						itemValue->HasKey("unit") ? Helpers::ToString(itemValue->GetNamedValue("unit")) : "",
						itemValue->HasKey("is_multiple") ? Helpers::ToBool(itemValue->GetNamedValue("is_multiple")) : false,
						itemValue->HasKey("is_slider") ? Helpers::ToBool(itemValue->GetNamedValue("is_slider")) : false,
						itemValue->HasKey("step") ? Helpers::ToString(itemValue->GetNamedValue("step")) : "",
						itemValue->HasKey("min") ? Helpers::ToNumber(itemValue->GetNamedValue("min")) : 0.0,
						itemValue->HasKey("max") ? Helpers::ToNumber(itemValue->GetNamedValue("max")) : 0.0,
						itemValue->HasKey("max_global") ? Helpers::ToNumber(itemValue->GetNamedValue("max_global")) : 0.0,
						itemValue->HasKey("min_global") ? Helpers::ToNumber(itemValue->GetNamedValue("min_global")) : 0.0);

					auto vectOptions = ref new Vector<FilterOptionsModels^>();
					if (itemValue->HasKey("options") && itemValue->GetNamedValue("options")->ValueType == JsonValueType::Array)
					{
						auto jsonOptions = itemValue->GetNamedArray("options");
						for (const auto &option : jsonOptions)
						{
							auto optionValue = option->GetObject();
							auto optionModel = ref new FilterOptionsModels(optionValue->HasKey("id") ? Helpers::ToNumber(optionValue->GetNamedValue("id")) : 0.0,
								optionValue->HasKey("name") ? Helpers::ToString(optionValue->GetNamedValue("name")) : "",
								optionValue->HasKey("global") ? Helpers::ToNumber(optionValue->GetNamedValue("global")) : 0.0,
								optionValue->HasKey("quantity") ? Helpers::ToNumber(optionValue->GetNamedValue("quantity")) : 0.0,
								optionValue->HasKey("property_id") ? Helpers::ToNumber(optionValue->GetNamedValue("property_id")) : 0);
							vectOptions->Append(optionModel);
						}
					}

					filterModel->Options = vectOptions;
					vect->Append(filterModel);
				}
			}

			return vect;
		}, task_continuation_context::use_current());
	});
}

int FilterProductCommands::RegionId::get()
{
	return source_regionId;
}

int FilterProductCommands::CategoryId::get()
{
	return source_categoryId;
}

PromoBannerCommands::PromoBannerCommands(int geoId, BannerType bannerType)
	: source_geoId(geoId), source_bannerType(bannerType)
{
}

IAsyncOperation<IVector<PromoBannerModels^>^>^ PromoBannerCommands::PromoBannerAsync(bool isCached)
{
	using namespace concurrency;

	return create_async([&](cancellation_token token) -> task<IVector<PromoBannerModels^>^>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["type_id"] = static_cast<int>(TypeBanner).ToString();
		
		if (GeoId != 0)
		{
			queryParameter["geo_id"] = GeoId.ToString();
		}

		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter);
		httpCommand->CacheReadBehavior = isCached == false ? HttpCacheReadBehavior::Default : HttpCacheReadBehavior::MostRecent;
		auto operation = httpCommand->ToCommandOperationAsync(interfaceNameBanner, categoryNameBanner);

		return create_task(operation, token).then([&](String^ content) -> IVector<PromoBannerModels^>^
		{
			auto vect = ref new Vector<PromoBannerModels^>();
			auto jsonContent = JsonObject::Parse(content);
			
			if (jsonContent->HasKey("result") && jsonContent->GetNamedValue("result")->ValueType == JsonValueType::Array)
			{
				auto jsonArray = jsonContent->GetNamedArray("result");
				for (const auto &item : jsonArray)
				{
					auto itemValue = item->GetObject();

					auto vectItems = ref new Vector<PromoItem^>();
					if (itemValue->HasKey("item_list") && itemValue->GetNamedValue("item_list")->ValueType == JsonValueType::Array)
					{
						auto items = itemValue->GetNamedArray("item_list");
						for (const auto &listItem : items)
						{
							auto elementItem = listItem->GetObject();
							auto promoItem = ref new PromoItem(elementItem->HasKey("id") ? Helpers::ToNumber(elementItem->GetNamedValue("id")) : 0,
								elementItem->HasKey("type_id") ? Helpers::ToNumber(elementItem->GetNamedValue("type_id")) : 0);
							vectItems->Append(promoItem);
						}
					}

					auto promoBannerModel = ref new PromoBannerModels(itemValue->HasKey("id") ? Helpers::ToString(itemValue->GetNamedValue("id")) : "",
						itemValue->HasKey("type_id") ? Helpers::ToString(itemValue->GetNamedValue("type_id")) : "",
						itemValue->HasKey("name") ? Helpers::ToString(itemValue->GetNamedValue("name")) : "",
						itemValue->HasKey("media_image") ? Helpers::ToString(itemValue->GetNamedValue("media_image")) : "",
						itemValue->HasKey("url") ? Helpers::ToString(itemValue->GetNamedValue("url")) : "",
						vectItems);
					vect->Append(promoBannerModel);
				}
			}

			return vect;
		}).then(TaskExceptionExtensions<IVector<PromoBannerModels^>^>(), task_continuation_context::use_current());
	});
}

int PromoBannerCommands::GeoId::get()
{
	return source_geoId;
}

BannerType PromoBannerCommands::TypeBanner::get()
{
	return source_bannerType;
}