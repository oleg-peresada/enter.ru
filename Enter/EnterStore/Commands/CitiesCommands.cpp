#include "pch.h"
#include "CitiesCommands.h"

using namespace EnterStore;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Data::Json;

const std::wstring interface_name = L"geo";
const std::wstring category_name = L"get-menu-cities";

CitiesCommands::CitiesCommands()
{
}

IAsyncOperationWithProgress<IObservableVector<CitiesModels^>^, HttpProgress>^ CitiesCommands::MenuCitiesAsync()
{
	using namespace concurrency;
	return create_async([&](progress_reporter<HttpProgress> reporter, cancellation_token token)-> task<IObservableVector<CitiesModels^>^>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());

		auto command = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter);
		command->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto operation = command->ToCommandOperationAsync(interface_name, category_name);

		return create_task(operation, token).then([](String^ content) -> IObservableVector<CitiesModels^>^
		{
			auto vect = ref new Vector<CitiesModels^>();
			auto json = JsonObject::Parse(content);
			
			if (json->HasKey("result") && json->GetNamedValue("result")->ValueType == JsonValueType::Array)
			{
				auto jsonResult = json->GetNamedArray("result");
				for (const auto &item : jsonResult)
				{
					auto jsonValue = item->GetObject();
					auto citiesModel = ref new CitiesModels(jsonValue->HasKey("id") ? Helpers::ToNumber(jsonValue->GetNamedValue("id")) : 0.0,
						jsonValue->HasKey("parent_id") ? Helpers::ToNumber(jsonValue->GetNamedValue("parent_id")) : 0.0,
						jsonValue->HasKey("name") ? Helpers::ToString(jsonValue->GetNamedValue("name")) : "",
						jsonValue->HasKey("token") ? Helpers::ToString(jsonValue->GetNamedValue("token")) : "",
						jsonValue->HasKey("is_main") ? Helpers::ToBool(jsonValue->GetNamedValue("is_main")) : false,
						jsonValue->HasKey("has_shop") ? Helpers::ToBool(jsonValue->GetNamedValue("has_shop")) : false,
						jsonValue->HasKey("has_delivery") ? Helpers::ToBool(jsonValue->GetNamedValue("has_delivery")) : false,
						jsonValue->HasKey("has_subway") ? Helpers::ToBool(jsonValue->GetNamedValue("has_subway")) : false,
						jsonValue->HasKey("coord_long") ? Helpers::ToNumber(jsonValue->GetNamedValue("coord_long")) : 0.0,
						jsonValue->HasKey("coord_lat") ? Helpers::ToNumber(jsonValue->GetNamedValue("coord_lat")) : 0.0,
						jsonValue->HasKey("tk_available") ? Helpers::ToBool(jsonValue->GetNamedValue("tk_available")) : false);
					vect->Append(citiesModel);
				}
			}

			return vect;

		}, task_continuation_context::use_current());
	});
}


const std::wstring geo_InterfaceName = L"geo";
const std::wstring geo_CategoryName = L"autocomplete";

IAsyncOperationWithProgress<IObservableVector<AutoCityModels^>^, HttpProgress>^ CitiesCommands::AutoCompleteCities(String^ letters)
{
	using namespace concurrency;

	return create_async([&](progress_reporter<HttpProgress> reporter, cancellation_token token) -> task<IObservableVector<AutoCityModels^>^>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["letters"] = letters;

		auto command = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter);
		command->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto commandOperation = command->ToCommandOperationAsync(geo_InterfaceName, geo_CategoryName);

		return create_task(commandOperation, token).then([this](String^ content) -> IObservableVector<AutoCityModels^>^
		{
			auto vect = ref new Vector<AutoCityModels^>();
			auto obj = JsonObject::Parse(content);
			if (obj->HasKey("result") && obj->GetNamedValue("result")->ValueType == JsonValueType::Array)
			{
				auto arrayResult = obj->GetNamedArray("result");
				unsigned int size = arrayResult->Size;

				for (unsigned int index = 0; index < size; index++)
				{
					auto elem = arrayResult->GetAt(index)->GetObject();
					if (elem->HasKey("region") && elem->GetNamedValue("region")->ValueType == JsonValueType::Object)
					{
						auto objRegion = elem->GetNamedObject("region");

						auto cityModel = ref new AutoCityModels(elem->HasKey("id") ? Helpers::ToNumber(elem->GetNamedValue("id")) : 0,
							elem->HasKey("name") ? Helpers::ToString(elem->GetNamedValue("name")) : "",
							ref new AutoRegionModels(objRegion->HasKey("id") ? Helpers::ToNumber(objRegion->GetNamedValue("id")) : 0,
							objRegion->HasKey("name") ? Helpers::ToString(objRegion->GetNamedValue("name")) : ""));

						vect->Append(cityModel);
					}
					else
					{
						auto cityModel = ref new AutoCityModels(elem->HasKey("id") ? Helpers::ToNumber(elem->GetNamedValue("id")) : 0,
							elem->HasKey("name") ? Helpers::ToString(elem->GetNamedValue("name")) : "",
							ref new AutoRegionModels(0, ""));
						vect->Append(cityModel);
					}
				}
			}

			return vect;

		}).then(TaskExceptionExtensions<IObservableVector<AutoCityModels^>^>(), task_continuation_context::use_current());
	});
}