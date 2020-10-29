#include "pch.h"
#include "AccountDataCommands.h"

using namespace EnterStore;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Data::Json;
using namespace Windows::Storage::Streams;

#pragma region Информация о деступных сроках доставки

std::wstring interfaceDelivery = L"delivery";
std::wstring categoryDelivery = L"calc";

ProductListOrder::ProductListOrder()
{
}

ProductListOrder::ProductListOrder(int id, int quantity)
	: source_id(id), source_quantity(quantity)
{
}

int ProductListOrder::Id::get()
{
	return source_id;
}

int ProductListOrder::Quantity::get()
{
	return source_quantity;
}

OrderCalcCommands::OrderCalcCommands(int geoId, IVector<ProductListOrder^>^ val)
	: source_geoId(geoId), source_ProductList(val)
{
}

OrderCalcModels^ OrderCalcCommands::FromOrderCalc(String^ content)
{
	auto jsonBegin = JsonObject::Parse(content);
	if (jsonBegin->HasKey("result") && jsonBegin->GetNamedValue("result")->ValueType == JsonValueType::Object)
	{
		auto result = jsonBegin->GetNamedObject("result");

		auto vectInterval = ref new Vector<IntervalListModels^>();
		if (result->HasKey("interval_list") && result->GetNamedValue("interval_list")->ValueType == JsonValueType::Object)
		{
			auto interval_list = result->GetNamedObject("interval_list");
			for (const auto &intervalItem : interval_list)
			{
				auto elementInterval = intervalItem->Value->GetObject();
				auto intervalModel = ref new IntervalListModels(elementInterval->HasKey("id") ? Helpers::ToNumber(elementInterval->GetNamedValue("id")) : 0,
					elementInterval->HasKey("ui") ? Helpers::ToString(elementInterval->GetNamedValue("ui")) : "",
					elementInterval->HasKey("time_begin") ? Helpers::ToString(elementInterval->GetNamedValue("time_begin")) : "",
					elementInterval->HasKey("time_end") ? Helpers::ToString(elementInterval->GetNamedValue("time_end")) : "");
				vectInterval->Append(intervalModel);
			}
		}

		auto vectShop = ref new Vector<OrderShopListModels^>();
		if (result->HasKey("shop_list") && result->GetNamedValue("shop_list")->ValueType == JsonValueType::Object)
		{
			auto shop_list = result->GetNamedObject("shop_list");
			for (const auto &itemShop : shop_list)
			{
				auto elementShop = itemShop->Value->GetObject();

				auto shopModel = ref new OrderShopListModels(elementShop->HasKey("id") ? Helpers::ToNumber(elementShop->GetNamedValue("id")) : 0,
					elementShop->HasKey("ui") ? Helpers::ToString(elementShop->GetNamedValue("ui")) : "",
					elementShop->HasKey("name") ? Helpers::ToString(elementShop->GetNamedValue("name")) : "",
					elementShop->HasKey("geo_id") ? Helpers::ToNumber(elementShop->GetNamedValue("geo_id")) : 0,
					elementShop->HasKey("address") ? Helpers::ToString(elementShop->GetNamedValue("address")) : "",
					elementShop->HasKey("working_time") ? Helpers::ToString(elementShop->GetNamedValue("working_time")) : "",
					elementShop->HasKey("coord_lat") ? Helpers::ToNumber(elementShop->GetNamedValue("coord_lat")) : 0.0,
					elementShop->HasKey("coord_long") ? Helpers::ToNumber(elementShop->GetNamedValue("coord_long")) : 0.0);
				vectShop->Append(shopModel);
			}
		}

		auto vectProduct = ref new Vector<DeliveryModeListModels^>();
		if (result->HasKey("product_list") && result->GetNamedValue("product_list")->ValueType == JsonValueType::Object)
		{
			auto product_list = result->GetNamedObject("product_list");
			for (const auto &itemProduct : product_list)
			{
				auto elementProduct = itemProduct->Value->GetObject();
				auto deliveryModel = ref new DeliveryModeListModels(elementProduct->HasKey("id") ? Helpers::ToNumber(elementProduct->GetNamedValue("id")) : 0,
					elementProduct->HasKey("token") ? Helpers::ToString(elementProduct->GetNamedValue("token")) : "");

				if (elementProduct->HasKey("delivery_mode_list") && elementProduct->GetNamedValue("delivery_mode_list")->ValueType == JsonValueType::Object)
				{
					auto elementMode = elementProduct->GetNamedObject("delivery_mode_list");
					for (const auto &itemMode : elementMode)
					{
						auto valueMode = itemMode->Value->GetObject();

						auto vectPickupDate = ref new Vector<PickupDateListModels^>();
						if (itemMode->Key == "3")
						{
							auto pickupModel = ref new PickupDeliveryModels(valueMode->HasKey("id") ? Helpers::ToNumber(valueMode->GetNamedValue("id")) : 0,
								valueMode->HasKey("name") ? Helpers::ToString(valueMode->GetNamedValue("name")) : "",
								valueMode->HasKey("token") ? Helpers::ToString(valueMode->GetNamedValue("token")) : "",
								valueMode->HasKey("delivery_id") ? Helpers::ToNumber(valueMode->GetNamedValue("delivery_id")) : 0,
								valueMode->HasKey("price") ? Helpers::ToNumber(valueMode->GetNamedValue("price")) : 0.0);

							if (valueMode->HasKey("date_list") && valueMode->GetNamedValue("date_list")->ValueType == JsonValueType::Object)
							{
								auto dateList = valueMode->GetNamedObject("date_list");
								for (const auto &dateItem : dateList)
								{
									auto elementDate = dateItem->Value->GetObject();

									auto vect_Shop = ref new Vector<PickupDateShopListModels^>();
									if (elementDate->HasKey("shop_list") && elementDate->GetNamedValue("shop_list")->ValueType == JsonValueType::Array)
									{
										auto elementShop = elementDate->GetNamedArray("shop_list");
										for (const auto &itemShop : elementShop)
										{
											auto element = itemShop->GetObject();
											if (element->HasKey("interval_list") && element->GetNamedValue("interval_list")->ValueType == JsonValueType::Array)
											{
												auto elementInterval = element->GetNamedArray("interval_list");
												auto intervalArray = ref new Array<int>(elementInterval->Size);
												unsigned int index = 0;

												for (const auto &itemInterval : elementInterval)
												{
													if (itemInterval->ValueType == JsonValueType::Number)
													{
														intervalArray[index] = itemInterval->GetNumber();
													}
													else
													{
														intervalArray[index] = 0;
													}
													index++;
												}

												vect_Shop->Append(ref new PickupDateShopListModels(element->HasKey("id") ? 
													Helpers::ToNumber(element->GetNamedValue("id")) : 0,
													intervalArray));
											}
										}
									}

									vectPickupDate->Append(ref new PickupDateListModels(elementDate->HasKey("date") ? 
										Helpers::ToString(elementDate->GetNamedValue("date")) : "", vect_Shop));
								}
							}

							pickupModel->VectorDateInterval = vectPickupDate;
							deliveryModel->PickupDelivery = pickupModel;
						}
						else if (itemMode->Key == "1")
						{
							auto vect_datelist = ref new Vector<StandartDateListModels^>();
							auto standartModel = ref new StandartDeliveryModels(valueMode->HasKey("id") ? Helpers::ToNumber(valueMode->GetNamedValue("id")) : 0,
								valueMode->HasKey("name") ? Helpers::ToString(valueMode->GetNamedValue("name")) : "",
								valueMode->HasKey("token") ? Helpers::ToString(valueMode->GetNamedValue("token")) : "",
								valueMode->HasKey("delivery_id") ? Helpers::ToNumber(valueMode->GetNamedValue("delivery_id")) : 0,
								valueMode->HasKey("price") ? Helpers::ToNumber(valueMode->GetNamedValue("price")) : 0.0);

							if (valueMode->HasKey("date_list") && valueMode->GetNamedValue("date_list")->ValueType == JsonValueType::Array)
							{
								auto arrayDate = valueMode->GetNamedArray("date_list");
								for (const auto &itemDate : arrayDate)
								{
									auto elementDate = itemDate->GetObject();
									
									if (elementDate->HasKey("interval_list") && elementDate->GetNamedValue("interval_list")->ValueType == JsonValueType::Array)
									{
										auto elementInterval = elementDate->GetNamedArray("interval_list");
										auto arrayInterval = ref new Array<int>(elementInterval->Size);
										unsigned int index = 0;

										for (const auto &itemInterval : elementInterval)
										{
											if (itemInterval->ValueType == JsonValueType::Number)
											{
												arrayInterval[index] = itemInterval->GetNumber();
											}
											else
											{
												arrayInterval[index] = 0;
											}

											index++;
										}

										vect_datelist->Append(ref new StandartDateListModels(elementDate->HasKey("date") ?
											Helpers::ToString(elementDate->GetNamedValue("date")) : "", arrayInterval));
									}
								}
							}

							standartModel->Datalist = vect_datelist;
							deliveryModel->StandartDelivery = standartModel;
						}
						else if (itemMode->Key == "4")
						{
							auto vectPickupDate = ref new Vector<PickupDateListModels^>();
							auto newPickupModel = ref new PickupUpNowDeliveryModels(valueMode->HasKey("id") ? Helpers::ToNumber(valueMode->GetNamedValue("id")) : 0,
								valueMode->HasKey("name") ? Helpers::ToString(valueMode->GetNamedValue("name")) : "",
								valueMode->HasKey("token") ? Helpers::ToString(valueMode->GetNamedValue("token")) : "",
								valueMode->HasKey("description") ? Helpers::ToString(valueMode->GetNamedValue("description")) : "");

							if (valueMode->HasKey("date_list") && valueMode->GetNamedValue("date_list")->ValueType == JsonValueType::Array)
							{
								auto dateArray = valueMode->GetNamedArray("date_list");
								for (const auto &itemDate : dateArray)
								{
									auto elementDate = itemDate->GetObject();

									if (elementDate->HasKey("shop_list") && elementDate->GetNamedValue("shop_list")->ValueType == JsonValueType::Array)
									{
										auto vect_Shop = ref new Vector<PickupDateShopListModels^>();
										auto shopArray = elementDate->GetNamedArray("shop_list");
										for (const auto &itemShop : shopArray)
										{
											auto elementShop = itemShop->GetObject();

											if (elementShop->HasKey("interval_list") && elementShop->GetNamedValue("interval_list")->ValueType == JsonValueType::Array)
											{
												auto intervalArray = elementShop->GetNamedArray("interval_list");
												auto arrayInterval = ref new Array<int>(intervalArray->Size);
												unsigned int index = 0;

												for (const auto &itemInterval : intervalArray)
												{
													if (itemInterval->ValueType == JsonValueType::Number)
													{
														arrayInterval[index] = itemInterval->GetNumber();
													}
													else
													{
														arrayInterval[index] = 0;
													}

													index++;
												}

												vect_Shop->Append(ref new PickupDateShopListModels(elementShop->HasKey("id") ? 
													Helpers::ToNumber(elementShop->GetNamedValue("id")) : 0, arrayInterval));
											}
										}
										vectPickupDate->Append(ref new PickupDateListModels(elementDate->HasKey("date") 
											? Helpers::ToString(elementDate->GetNamedValue("date")) : "", vect_Shop));
									}
								}
							}

							newPickupModel->VectorDateInterval = vectPickupDate;
							deliveryModel->PickupDeliveryUp = newPickupModel;
						}
					}
				}

				vectProduct->Append(deliveryModel);
			}
		}

		return ref new OrderCalcModels(vectProduct, vectInterval, vectShop);
	}

	return nullptr;
}

IAsyncOperationWithProgress<Object^, HttpProgress>^ OrderCalcCommands::OrderCalcAsync()
{
	using namespace concurrency;

	return create_async([&](progress_reporter<HttpProgress> reporter, cancellation_token token) -> task<Object^>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());
		queryParameter["geo_id"] = GeoId.ToString();

		auto arrayData = ref new JsonArray();
		for (const auto &item : this->ProductList)
		{
			auto itemJson = ref new JsonObject();
			itemJson->SetNamedValue("id", JsonValue::CreateNumberValue(item->Id));
			itemJson->SetNamedValue("quantity", JsonValue::CreateNumberValue(item->Quantity));
			arrayData->Append(itemJson);
		}
		auto data = ref new JsonObject();
		data->SetNamedValue("product_list", arrayData);
		
		auto contentString = ref new HttpStringContent(data->Stringify(), UnicodeEncoding::Utf8, "application/json");
		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter, HttpMethod::Post, contentString, nullptr);
		httpCommand->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto operationCommand = httpCommand->ToCommandOperationAsync(interfaceDelivery, categoryDelivery);

		return create_task(operationCommand, token).then([&](String^ content) -> Object^
		{
			auto json = JsonObject::Parse(content);
			if (json->HasKey("result"))
			{
				return this->FromOrderCalc(content);
			}
			else if (json->HasKey("error") && json->GetNamedValue("error")->ValueType == JsonValueType::Object)
			{
				auto errorValue = json->GetNamedObject("error");
				if (errorValue->HasKey("message") && errorValue->GetNamedValue("message")->ValueType == JsonValueType::String)
				{
					return errorValue->GetNamedString("message");
				}
			}
		}, task_continuation_context::use_current());
	});
}

int OrderCalcCommands::GeoId::get()
{
	return source_geoId;
}

IVector<ProductListOrder^>^ OrderCalcCommands::ProductList::get()
{
	return source_ProductList;
}

#pragma endregion

std::wstring interfaceUser = L"user";
std::wstring categoryUser = L"get";

UserContentCommands::UserContentCommands(String^ token) : source_token(token)
{
}

IAsyncOperationWithProgress<UserContentModels^, HttpProgress>^ UserContentCommands::CurrentUserAsync()
{
	using namespace concurrency;

	return create_async([&](progress_reporter<HttpProgress> reporter, cancellation_token token) -> task<UserContentModels^>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());
		queryParameter["token"] = Token;

		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter);
		httpCommand->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto httpOperation = httpCommand->ToCommandOperationAsync(interfaceUser, categoryUser);

		return create_task(httpOperation, token).then([&](String^ content) -> UserContentModels^
		{
			auto jsonSource = JsonObject::Parse(content);
			if (jsonSource->HasKey("result") && jsonSource->GetNamedValue("result")->ValueType == JsonValueType::Object)
			{
				auto resultValue = jsonSource->GetNamedObject("result");
				
				auto userModel = ref new UserContentModels(resultValue->HasKey("id") ? Helpers::ToNumber(resultValue->GetNamedValue("id")) : 0,
					resultValue->HasKey("ui") ? Helpers::ToString(resultValue->GetNamedValue("ui")) : "",
					resultValue->HasKey("first_name") ? Helpers::ToString(resultValue->GetNamedValue("first_name")) : "",
					resultValue->HasKey("last_name") ? Helpers::ToString(resultValue->GetNamedValue("last_name")) : "",
					resultValue->HasKey("middle_name") ? Helpers::ToString(resultValue->GetNamedValue("middle_name")) : "",
					resultValue->HasKey("sex") ? Helpers::ToString(resultValue->GetNamedValue("sex")) : "",
					resultValue->HasKey("occupation") ? Helpers::ToString(resultValue->GetNamedValue("occupation")) : "",
					resultValue->HasKey("email") ? Helpers::ToString(resultValue->GetNamedValue("email")) : "",
					resultValue->HasKey("phone") ? Helpers::ToString(resultValue->GetNamedValue("phone")) : "",
					resultValue->HasKey("mobile") ? Helpers::ToString(resultValue->GetNamedValue("mobile")) : "",
					resultValue->HasKey("skype") ? Helpers::ToString(resultValue->GetNamedValue("skype")) : "",
					resultValue->HasKey("birthday") ? Helpers::ToString(resultValue->GetNamedValue("birthday")) : "");

				return userModel;
			}

			return nullptr;
		}, task_continuation_context::use_current());
	});
}

String^ UserContentCommands::Token::get()
{
	return source_token;
}

std::wstring interfaceUpdate = L"user";
std::wstring categoryUpdate = L"update";

PersonalDataUpdateCommands::PersonalDataUpdateCommands(String^ token) : source_token(token)
{
}

IAsyncOperation<bool>^ PersonalDataUpdateCommands::UpdateAsync(PersonalDataUpdateModels^ dataValue)
{
	using namespace concurrency;

	return create_async([=, &dataValue](cancellation_token token) -> task<bool>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());
		queryParameter["token"] = this->Token;

		auto contentString = ref new HttpStringContent(Stringify(dataValue), UnicodeEncoding::Utf8, "application/json");
		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter, HttpMethod::Post, contentString, nullptr);
		httpCommand->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto operation = httpCommand->ToCommandOperationAsync(interfaceUpdate, categoryUpdate);

		return create_task(operation, token).then([=](String^ content) -> bool
		{
			auto jsonSource = JsonObject::Parse(content);
			if (jsonSource->HasKey("result") && jsonSource->GetNamedValue("result")->ValueType == JsonValueType::Object)
			{
				auto resultValue = jsonSource->GetNamedObject("result");
				return resultValue->HasKey("confirmed") ? Helpers::ToBool(resultValue->GetNamedValue("confirmed")) : false;
			}

			return false;
		}, task_continuation_context::use_current());
	});
}

String^ PersonalDataUpdateCommands::Token::get()
{
	return source_token;
}

String^ PersonalDataUpdateCommands::Stringify(PersonalDataUpdateModels^ dataValue)
{
	auto postObject = ref new JsonObject();

	if (dataValue->FirstName != nullptr) 
		postObject->SetNamedValue("first_name", JsonValue::CreateStringValue(dataValue->FirstName));

	if (dataValue->LastName != nullptr)
		postObject->SetNamedValue("last_name", JsonValue::CreateStringValue(dataValue->LastName));

	if (dataValue->MiddleName != nullptr)
		postObject->SetNamedValue("middle_name", JsonValue::CreateStringValue(dataValue->MiddleName));

	if (dataValue->Sex != nullptr)
		postObject->SetNamedValue("sex", JsonValue::CreateStringValue(dataValue->Sex));

	if (dataValue->Occupation != nullptr)
		postObject->SetNamedValue("occupation", JsonValue::CreateStringValue(dataValue->Occupation));

	if (dataValue->Email != nullptr)
		postObject->SetNamedValue("email", JsonValue::CreateStringValue(dataValue->Email));

	if (dataValue->Phone != nullptr)
		postObject->SetNamedValue("phone", JsonValue::CreateStringValue(dataValue->Phone));

	if (dataValue->MobilePhone != nullptr)
		postObject->SetNamedValue("mobile", JsonValue::CreateStringValue(dataValue->MobilePhone));

	if (dataValue->Birthday != nullptr)
		postObject->SetNamedValue("birthday", JsonValue::CreateStringValue(dataValue->Birthday));

	if (dataValue->Skype != nullptr)
		postObject->SetNamedValue("skype", JsonValue::CreateStringValue(dataValue->Skype));

	return postObject->Stringify();
}