#include "pch.h"
#include "ShopListCommands.h"

using namespace EnterStore;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Data::Json;

const std::wstring interface_name = L"shop";
const std::wstring category_name = L"get";

ShopListCommands::ShopListCommands(ShopListType type, String^ parameter)
	: shop_type(type), shop_parameter(parameter)
{
}

ShopListType ShopListCommands::Type::get()
{
	return shop_type;
}

String^ ShopListCommands::Parameter::get()
{
	return shop_parameter;
}

IAsyncOperationWithProgress<IVector<ShopListModels^>^, HttpProgress>^ ShopListCommands::ToShopCommandAsync()
{
	return this->ToShopCommandAsync(false);
}

IAsyncOperationWithProgress<IVector<ShopListModels^>^, HttpProgress>^ ShopListCommands::ToShopCommandAsync(bool isCached)
{
	using namespace concurrency;
	return create_async([&](progress_reporter<HttpProgress> progress_reporter, cancellation_token token)-> task< IVector<ShopListModels^> ^>
	{
		std::map<String^, String^> parameterQuery;

		if (this->Type != ShopListType::None)
		{
			if (this->Type == ShopListType::Id)
			{
				parameterQuery["id"] = Parameter;
			}
			else if (this->Type == ShopListType::Slug)
			{
				parameterQuery["slug"] = Parameter;
			}
			else if (this->Type == ShopListType::GeoId)
			{
				parameterQuery["geo_id"] = Parameter;
			}
		}

		auto command = ref new HttpCommand(Helpers::standartQueryCommand, parameterQuery);
		command->CacheReadBehavior = isCached == false ? HttpCacheReadBehavior::Default : HttpCacheReadBehavior::MostRecent;
		auto commandOperation = command->ToCommandOperationAsync(interface_name, category_name);

		return create_task(commandOperation, token).then([&](String^ content) -> IVector<ShopListModels^>^
		{
			auto vect = ref new Vector<ShopListModels^>();

			auto jsonObject = JsonObject::Parse(content);
			if (jsonObject->HasKey("result") && jsonObject->GetNamedValue("result")->ValueType == JsonValueType::Array)
			{
				auto resultArray = jsonObject->GetNamedArray("result");
				for (const auto &item : resultArray)
				{
					auto valueObject = item->GetObject();
					auto shopObject = ref new ShopListModels(valueObject->HasKey("id") ? Helpers::ToNumber(valueObject->GetNamedValue("id")) : 0,
						valueObject->HasKey("token") ? Helpers::ToString(valueObject->GetNamedValue("token")) : "",
						valueObject->HasKey("name") ? Helpers::ToString(valueObject->GetNamedValue("name")) : "",
						valueObject->HasKey("description") ? Helpers::ToString(valueObject->GetNamedValue("description")) : "",
						valueObject->HasKey("media_image") ? Helpers::ToString(valueObject->GetNamedValue("media_image")) : "",
						valueObject->HasKey("working_time") ? Helpers::ToString(valueObject->GetNamedValue("working_time")) : "",
						valueObject->HasKey("is_reconstruction") ? Helpers::ToBool(valueObject->GetNamedValue("is_reconstruction")) : false,
						valueObject->HasKey("phone") ? Helpers::ToString(valueObject->GetNamedValue("phone")) : "",
						valueObject->HasKey("address") ? Helpers::ToString(valueObject->GetNamedValue("address")) : "",
						valueObject->HasKey("coord_long") ? Helpers::ToNumber(valueObject->GetNamedValue("coord_long")) : 0.0f,
						valueObject->HasKey("coord_lat") ? Helpers::ToNumber(valueObject->GetNamedValue("coord_lat")) : 0.0f,
						valueObject->HasKey("way_walk") ? Helpers::ToString(valueObject->GetNamedValue("way_walk")) : "",
						valueObject->HasKey("way_auto") ? Helpers::ToString(valueObject->GetNamedValue("way_auto")) : "");

					if (valueObject->HasKey("geo"))
					{
						if (valueObject->GetNamedValue("geo")->ValueType == JsonValueType::Object)
						{
							auto geoValue = valueObject->GetNamedObject("geo");
							auto geoModel = ref new GeoShopModels(geoValue->HasKey("id") ? Helpers::ToNumber(geoValue->GetNamedValue("id")) : 0,
								geoValue->HasKey("name") ? Helpers::ToString(geoValue->GetNamedValue("name")) : "",
								geoValue->HasKey("coord_long") ? Helpers::ToString(geoValue->GetNamedValue("coord_long")) : "",
								geoValue->HasKey("coord_lat") ? Helpers::ToString(geoValue->GetNamedValue("coord_lat")) : "");
							shopObject->Geo = geoModel;
						}
					}
					else
					{
						shopObject->Geo = ref new GeoShopModels(0, "", "", "");
					}

					auto vectImage = ref new Vector<ImagesModels^>();

					if (valueObject->HasKey("images") && valueObject->GetNamedValue("images")->ValueType == JsonValueType::Array)
					{
						auto arrayImages = valueObject->GetNamedArray("images");
						for (const auto &image : arrayImages)
						{
							auto valueImage = image->GetObject();
							auto shopImage = ref new ImagesModels(valueImage->HasKey("source") ? Helpers::ToString(valueImage->GetNamedValue("source")) : "",
								valueImage->HasKey("position") ? Helpers::ToString(valueImage->GetNamedValue("position")) : "");

							vectImage->Append(shopImage);
						}

					}
					
					shopObject->Images = vectImage;
					vect->Append(shopObject);
				}
			}

			return vect;
		}, task_continuation_context::use_current()).then(TaskExceptionExtensions<IVector<ShopListModels^>^>());
	});
}