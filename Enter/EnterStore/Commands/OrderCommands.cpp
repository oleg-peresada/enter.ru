#include "pch.h"
#include "OrderCommands.h"

using namespace EnterStore;
using namespace EnterStore::Commands;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Headers;
using namespace Windows::Data::Json;
using namespace Windows::Storage::Streams;

OrderDeliveryResult::OrderDeliveryResult(Object^ confirmed,
	Object^ id,
	Object^ number,
	Object^ numberExp,
	double paySum,
	double price,
	Object^ user_id) : source_confirmed(confirmed), source_id(id),
	source_number(number), source_numberErp(numberExp), 
	source_paySum(paySum), source_price(price), source_userId(user_id)
{
}

Object^ OrderDeliveryResult::Confirmed::get()
{
	return source_confirmed;
}

Object^ OrderDeliveryResult::Id::get()
{
	return source_id;
}

Object^ OrderDeliveryResult::Number::get()
{
	return source_number;
}

Object^ OrderDeliveryResult::NumberExp::get()
{
	return source_numberErp;
}

double OrderDeliveryResult::PaySum::get()
{
	return source_paySum;
}

double OrderDeliveryResult::Price::get()
{
	return source_price;
}

Object^ OrderDeliveryResult::UserId::get()
{
	return source_userId;
}

OrderQueryProduct::OrderQueryProduct(int id, int quantity)
	: source_id(id), source_quantity(quantity)
{
}

int OrderQueryProduct::Id::get()
{
	return source_id;
}

int OrderQueryProduct::Quantity::get()
{
	return source_quantity;
}

OrderQueryField::OrderQueryField(int typeId,
	int geoId,
	int paymentId,
	int paymentStatusId,
	int deliveryTypeId,
	String^ deliveryDate,
	int deliveryIntervalId,
	int shopId,
	String^ firstName,
	String^ lastName,
	String^ phone,
	String^ email,
	String^ addressStreet,
	String^ addressBuilding,
	String^ addressNumber,
	String^ addressFloor,
	String^ addressApartament) : source_typeId(typeId),
	source_geoId(geoId), source_paymentId(paymentId), source_paymentStatusId(paymentStatusId),
	source_deliveryTypeId(deliveryTypeId), source_deliveryDate(deliveryDate), 
	source_deliveryIntervalId(deliveryIntervalId), source_shopId(shopId),
	source_firstName(firstName), source_lastName(lastName), source_phone(phone), source_email(email),
	source_addressStreet(addressStreet), source_addressBuilding(addressBuilding),
	source_addressNumber(addressNumber), source_addressFloor(addressFloor), source_addressApartment(addressApartament)
{
}

int OrderQueryField::TypeId::get()
{
	return source_typeId;
}

int OrderQueryField::GeoId::get()
{
	return source_geoId;
}

int OrderQueryField::PaymentId::get()
{
	return source_paymentId;
}

int OrderQueryField::PaymentStatusId::get()
{
	return source_paymentStatusId;
}

int OrderQueryField::DeliveryTypeId::get()
{
	return source_deliveryTypeId;
}

String^ OrderQueryField::DeliveryDate::get()
{
	return source_deliveryDate;
}

int OrderQueryField::DeliveryIntervalId::get()
{
	return source_deliveryIntervalId;
}

int OrderQueryField::ShopId::get()
{
	return source_shopId;
}

String^ OrderQueryField::FirstName::get()
{
	return source_firstName;
}

String^ OrderQueryField::LastName::get()
{
	return source_lastName;
}

String^ OrderQueryField::Phone::get()
{
	return source_phone;
}

String^ OrderQueryField::Email::get()
{
	return source_email;
}

String^ OrderQueryField::AddressStreet::get()
{
	return source_addressStreet;
}

String^ OrderQueryField::AddressBuilding::get()
{
	return source_addressBuilding;
}

String^ OrderQueryField::AddressNumber::get()
{
	return source_addressNumber;
}

String^ OrderQueryField::AddressFloor::get()
{
	return source_addressFloor;
}

String^ OrderQueryField::AddressApartment::get()
{
	return source_addressApartment;
}

OrderQueryProduct^ OrderQueryField::Product::get()
{
	return m_product;
}

void OrderQueryField::Product::set(OrderQueryProduct^ value)
{
	m_product = value;
}

IVector<OrderQueryProduct^>^ OrderQueryField::OrderProduct::get()
{
	return source_OrderProduct;
}

void OrderQueryField::OrderProduct::set(IVector<OrderQueryProduct^>^ val)
{
	source_OrderProduct = val;
}

std::wstring interfaceOrder = L"order";
std::wstring categoryOrder = L"create";

OrderCommands::OrderCommands(String^ token)
	: source_token(token)
{
}

IAsyncOperationWithProgress<IVector<OrderDeliveryResult^>^, HttpProgress>^ OrderCommands::OrderAsync(IVector<OrderQueryField^>^ fieldValue)
{
	using namespace concurrency;
	return create_async([&, fieldValue](progress_reporter<HttpProgress> report, cancellation_token token)-> task<IVector<OrderDeliveryResult^>^>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());
		queryParameter["token"] = this->Token;
		queryParameter["check_stocks"] = "true";

		auto contents = this->Stringify(fieldValue);
		std::vector<task<String^>> resultsTasks;

		for (const auto item : contents)
		{
			auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter, HttpMethod::Post, item, nullptr);
			httpCommand->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
			auto httpOperation = httpCommand->ToCommandOperationAsync(interfaceOrder, categoryOrder);
			resultsTasks.push_back(create_task(httpOperation));
		}

		auto joinTask = concurrency::when_all(std::begin(resultsTasks), std::end(resultsTasks));
		return joinTask.then([this](std::vector<String^> vects) -> IVector<OrderDeliveryResult^>^
		{
			auto VectorOrder = ref new Vector<OrderDeliveryResult^>();
			if (vects.size() > 0)
			{
				for (const auto newValue : vects)
				{
					auto json = JsonObject::Parse(newValue);
					if (json->HasKey("result") && json->GetNamedValue("result")->ValueType == JsonValueType::Object)
					{
						auto valueOrder = json->GetNamedObject("result");
						auto orderResultModel = ref new OrderDeliveryResult(valueOrder->HasKey("confirmed") ? Helpers::ToString(valueOrder->GetNamedValue("confirmed")) : "",
							valueOrder->HasKey("id") ? Helpers::ToString(valueOrder->GetNamedValue("id")) : "",
							valueOrder->HasKey("number") ? Helpers::ToString(valueOrder->GetNamedValue("number")) : "",
							valueOrder->HasKey("number_erp") ? Helpers::ToString(valueOrder->GetNamedValue("number_erp")) : "",
							valueOrder->HasKey("pay_sum") ? Helpers::ToNumber(valueOrder->GetNamedValue("pay_sum")) : 0.0,
							valueOrder->HasKey("price") ? Helpers::ToNumber(valueOrder->GetNamedValue("price")) : 0.0,
							valueOrder->HasKey("user_id") ? Helpers::ToString(valueOrder->GetNamedValue("user_id")) : "");
						VectorOrder->Append(orderResultModel);
					}
				}
			}

			return VectorOrder;
		}).then(TaskExceptionExtensions<IVector<OrderDeliveryResult^>^>(), task_continuation_context::use_current());
	});
}

String^ OrderCommands::Token::get()
{
	return source_token;
}

int OrderCommands::DeliveryOrder(IVector<OrderQueryField^>^ vect, int idDelivery, int shopId)
{
	unsigned int size = vect->Size;
	for (unsigned int i = 0; i < size; i++)
	{
		auto element = vect->GetAt(i);
		if (element->DeliveryTypeId == idDelivery && element->ShopId == shopId)
		{
			return (int)i;
		}
		else if (element->DeliveryTypeId == idDelivery && shopId == -1)
		{
			return (int)i;
		}
	}

	return -1;
}

IVector<OrderQueryField^>^ OrderCommands::FromDeliveryOrder(IVector<OrderQueryField^>^ valueOrder)
{
	auto vectDelivery = ref new Vector<OrderQueryField^>();

	for (const auto &item : valueOrder)
	{
		auto OrderAppend = [item, vectDelivery](OrderQueryProduct^ product)
		{
			auto newItem = ref new Vector<OrderQueryProduct^>();
			newItem->Append(product);
			item->OrderProduct = newItem;
			vectDelivery->Append(item);
		};

		auto OrderSet = [item, vectDelivery](unsigned int index)
		{
			auto elem = vectDelivery->GetAt(index);
			auto productVect = ref new Vector<OrderQueryProduct^>(begin(elem->OrderProduct), end(elem->OrderProduct));
			auto new_elem = item->Product;
			productVect->Append(new_elem);
			elem->OrderProduct = productVect;
			vectDelivery->SetAt(index, elem);
		};

		if (item->DeliveryTypeId == 1)
		{
			int result = DeliveryOrder(vectDelivery, item->DeliveryTypeId, -1);
			if (result == -1)
			{
				OrderAppend(item->Product);
			}
			else
			{
				OrderSet(result);
			}
		}
		else if (item->DeliveryTypeId == 3)
		{
			int result = DeliveryOrder(vectDelivery, item->DeliveryTypeId, item->ShopId);
			if (result == -1)
			{
				OrderAppend(item->Product);
			}
			else
			{
				OrderSet(result);
			}
		}
		else if (item->DeliveryTypeId == 4)
		{
			int result = DeliveryOrder(vectDelivery, item->DeliveryTypeId, item->ShopId);
			if (result == -1)
			{
				OrderAppend(item->Product);
			}
			else
			{
				OrderSet(result);
			}
		}
	}

	return vectDelivery;
}

IVector<IHttpContent^>^ OrderCommands::Stringify(IVector<OrderQueryField^>^ valueOrder)
{
	auto vectDelivery = FromDeliveryOrder(valueOrder);
	auto httpContentVect = ref new Vector<IHttpContent^>();
	for (const auto &orderItem : vectDelivery)
	{
		auto order = ref new JsonObject();
		order->SetNamedValue("type_id", JsonValue::CreateNumberValue(orderItem->TypeId));
		order->SetNamedValue("geo_id", JsonValue::CreateNumberValue(orderItem->GeoId));
		order->SetNamedValue("payment_id", JsonValue::CreateNumberValue(orderItem->PaymentId));
		order->SetNamedValue("payment_status_id", JsonValue::CreateNumberValue(orderItem->PaymentStatusId));
		order->SetNamedValue("delivery_type_id", JsonValue::CreateNumberValue(orderItem->DeliveryTypeId));
		order->SetNamedValue("delivery_date", JsonValue::CreateStringValue(orderItem->DeliveryDate));
		order->SetNamedValue("delivery_interval_id", JsonValue::CreateNumberValue(orderItem->DeliveryIntervalId));

		if (orderItem->ShopId != -1) order->SetNamedValue("shop_id", JsonValue::CreateNumberValue(orderItem->ShopId));

		order->SetNamedValue("first_name", JsonValue::CreateStringValue(orderItem->FirstName));
		order->SetNamedValue("last_name", JsonValue::CreateStringValue(orderItem->LastName));
		order->SetNamedValue("phone", JsonValue::CreateStringValue(orderItem->Phone));
		order->SetNamedValue("email", JsonValue::CreateStringValue(orderItem->Email));
		order->SetNamedValue("is_receive_sms", JsonValue::CreateBooleanValue(true));

		if (orderItem->AddressStreet != nullptr) order->SetNamedValue("address_street", JsonValue::CreateStringValue(orderItem->AddressStreet));
		if (orderItem->AddressBuilding != nullptr) order->SetNamedValue("address_building", JsonValue::CreateStringValue(orderItem->AddressBuilding));
		if (orderItem->AddressNumber != nullptr) order->SetNamedValue("address_number", JsonValue::CreateStringValue(orderItem->AddressNumber));
		if (orderItem->AddressFloor != nullptr) order->SetNamedValue("address_floor", JsonValue::CreateStringValue(orderItem->AddressFloor));
		if (orderItem->AddressApartment != nullptr) order->SetNamedValue("address_apartment", JsonValue::CreateStringValue(orderItem->AddressApartment));

		if (orderItem->OrderProduct != nullptr)
		{
			auto orderProduct = ref new JsonArray();
			unsigned int size = orderItem->OrderProduct->Size;
			for (unsigned int index = 0; index < size; index++)
			{
				auto newValue = orderItem->OrderProduct->GetAt(index);
				auto valueProduct = ref new JsonObject();
				valueProduct->SetNamedValue("id", JsonValue::CreateNumberValue(newValue->Id));
				valueProduct->SetNamedValue("quantity", JsonValue::CreateNumberValue(newValue->Quantity));
				orderProduct->Append(valueProduct);
			}

			order->SetNamedValue("product", orderProduct);
		}

		auto s = order->Stringify();
		httpContentVect->Append(ref new HttpStringContent(order->Stringify(), UnicodeEncoding::Utf8, "application/json"));
	}

	return httpContentVect;
}

std::wstring interfacePersonalOrder = L"order";
std::wstring categoryPersonalOrder = L"get";

TrackerCommands::TrackerCommands(String^ token, int id)
: source_token(token), source_id(id)
{
}

String^ TrackerCommands::Token::get()
{
	return source_token;
}

int TrackerCommands::Id::get()
{
	return source_id;
}

IAsyncOperationWithProgress<IVector<TrackerOrderModels^>^, HttpProgress>^ TrackerCommands::TrackerOrderAsync()
{
	return this->TrackerOrderAsync(false);
}

IAsyncOperationWithProgress<IVector<TrackerOrderModels^>^, HttpProgress>^ TrackerCommands::TrackerOrderAsync(bool isCached)
{
	using namespace concurrency;
	
	return create_async([&](progress_reporter<HttpProgress> report, cancellation_token token) -> task<IVector<TrackerOrderModels^>^>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());
		queryParameter["token"] = this->Token;
		if (this->Id != -1) queryParameter["id"] = this->Id.ToString();

		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter);
		httpCommand->CacheReadBehavior = isCached == false ? HttpCacheReadBehavior::Default : HttpCacheReadBehavior::MostRecent;
		auto operationHttp = httpCommand->ToCommandOperationAsync(interfacePersonalOrder, categoryPersonalOrder);

		return create_task(operationHttp, token).then([&](String^ content) -> IVector<TrackerOrderModels^>^
		{
			auto vect = ref new Vector<TrackerOrderModels^>();
			auto jsonObject = JsonObject::Parse(content);

			if (jsonObject->HasKey("result") && jsonObject->GetNamedValue("result")->ValueType == JsonValueType::Array)
			{
				auto result = jsonObject->GetNamedArray("result");
				unsigned int size = result->Size;
				for (unsigned int i = 0; i < size; i++)
				{
					auto productValue = result->GetAt(i)->GetObject();
					auto order = ref new TrackerOrderModels(productValue->HasKey("id") ? Helpers::ToNumber(productValue->GetNamedValue("id")) : 0,
						productValue->HasKey("type_id") ? Helpers::ToNumber(productValue->GetNamedValue("type_id")) : 0,
						productValue->HasKey("status_id") ? Helpers::ToNumber(productValue->GetNamedValue("status_id")) : 0,
						productValue->HasKey("number") ? Helpers::ToString(productValue->GetNamedValue("number")) : "",
						productValue->HasKey("number_erp") ? Helpers::ToString(productValue->GetNamedValue("number_erp")) : "",
						productValue->HasKey("user_id") ? Helpers::ToNumber(productValue->GetNamedValue("user_id")) : 0,
						productValue->HasKey("email") ? Helpers::ToString(productValue->GetNamedValue("email")) : "",
						productValue->HasKey("last_name") ? Helpers::ToString(productValue->GetNamedValue("last_name")) : "",
						productValue->HasKey("first_name") ? Helpers::ToString(productValue->GetNamedValue("first_name")) : "",
						productValue->HasKey("middle_name") ? Helpers::ToString(productValue->GetNamedValue("middle_name")) : "",
						productValue->HasKey("phone") ? Helpers::ToString(productValue->GetNamedValue("phone")) : "",
						productValue->HasKey("mobile") ? Helpers::ToString(productValue->GetNamedValue("mobile")) : "",
						productValue->HasKey("payment_status_id") ? Helpers::ToNumber(productValue->GetNamedValue("payment_status_id")) : 0,
						productValue->HasKey("payment_id") ? Helpers::ToNumber(productValue->GetNamedValue("payment_id")) : 0,
						productValue->HasKey("payment_detail") ? Helpers::ToString(productValue->GetNamedValue("payment_detail")) : "",
						productValue->HasKey("credit_card_number") ? Helpers::ToString(productValue->GetNamedValue("credit_card_number")) : "",
						productValue->HasKey("credit_card_number") ? Helpers::ToString(productValue->GetNamedValue("credit_card_number")) : "",
						productValue->HasKey("sum") ? Helpers::ToNumber(productValue->GetNamedValue("sum")) : 0.0,
						productValue->HasKey("is_delivery") ? Helpers::ToBool(productValue->GetNamedValue("is_delivery")) : false,
						productValue->HasKey("is_paid_delivery") ? Helpers::ToBool(productValue->GetNamedValue("is_paid_delivery")) : false,
						productValue->HasKey("delivery_type_id") ? Helpers::ToNumber(productValue->GetNamedValue("delivery_type_id")) : 0,
						productValue->HasKey("delivery_date") ? Helpers::ToString(productValue->GetNamedValue("delivery_date")) : "",
						productValue->HasKey("delivery_interval_id") ? Helpers::ToNumber(productValue->GetNamedValue("delivery_interval_id")) : 0,
						productValue->HasKey("store_id") ? Helpers::ToNumber(productValue->GetNamedValue("store_id")) : 0,
						productValue->HasKey("shop_id") ? Helpers::ToNumber(productValue->GetNamedValue("shop_id")) : 0,
						productValue->HasKey("geo_id") ? Helpers::ToNumber(productValue->GetNamedValue("geo_id")) : 0,
						productValue->HasKey("region_id") ? Helpers::ToNumber(productValue->GetNamedValue("region_id")) : 0,
						productValue->HasKey("address") ? Helpers::ToString(productValue->GetNamedValue("address")) : "",
						productValue->HasKey("added") ? Helpers::ToString(productValue->GetNamedValue("added")) : "",
						productValue->HasKey("updated") ? Helpers::ToString(productValue->GetNamedValue("updated")) : "");

					if (productValue->HasKey("interval"))
					{
						auto vect = ref new Vector<TrackerIntervalOrderModels^>();
						auto intervalValueType = productValue->GetNamedValue("interval")->ValueType;
						if (intervalValueType == JsonValueType::Object)
						{
							auto intervalValue = productValue->GetNamedObject("interval");
							auto interval = ref new TrackerIntervalOrderModels(intervalValue->HasKey("id") ? Helpers::ToNumber(intervalValue->GetNamedValue("id")) : 0,
								intervalValue->HasKey("name") ? Helpers::ToString(intervalValue->GetNamedValue("name")) : "",
								intervalValue->HasKey("time_begin") ? Helpers::ToString(intervalValue->GetNamedValue("time_begin")) : "",
								intervalValue->HasKey("time_end") ? Helpers::ToString(intervalValue->GetNamedValue("time_end")) : "");
							vect->Append(interval);
						}
						else if (intervalValueType == JsonValueType::Array)
						{
							auto productArray = productValue->GetNamedArray("interval");
							for (const auto &item : productArray)
							{
								auto valueContent = item->GetObject();
								auto interval = ref new TrackerIntervalOrderModels(valueContent->HasKey("id") ? Helpers::ToNumber(valueContent->GetNamedValue("id")) : 0,
									valueContent->HasKey("name") ? Helpers::ToString(valueContent->GetNamedValue("name")) : "",
									valueContent->HasKey("time_begin") ? Helpers::ToString(valueContent->GetNamedValue("time_begin")) : "",
									valueContent->HasKey("time_end") ? Helpers::ToString(valueContent->GetNamedValue("time_end")) : "");
								vect->Append(interval);
							}
						}

						order->Interval = vect;
					}
					else
					{
						order->Interval = ref new Vector<TrackerIntervalOrderModels^>();
					}

					if (productValue->HasKey("product"))
					{
						if (productValue->GetNamedValue("product")->ValueType == JsonValueType::Array)
						{
							auto productOrder = ref new Vector<TrackerProductOrderModels^>();
							auto productArray = productValue->GetNamedArray("product");
							for (const auto &item : productArray)
							{
								auto valueContent = item->GetObject();
								auto orderProduct = ref new TrackerProductOrderModels(valueContent->HasKey("id") ? Helpers::ToNumber(valueContent->GetNamedValue("id")) : 0,
									valueContent->HasKey("price") ? Helpers::ToNumber(valueContent->GetNamedValue("price")) : 0,
									valueContent->HasKey("quantity") ? Helpers::ToNumber(valueContent->GetNamedValue("quantity")) : 0,
									valueContent->HasKey("sum") ? Helpers::ToNumber(valueContent->GetNamedValue("sum")) : 0.0);

								productOrder->Append(orderProduct);
							}

							order->ProductSize = productOrder->Size;
							order->Product = productOrder;
						}
					}
					else
					{
						order->Product = ref new Vector<TrackerProductOrderModels^>();
					}

					if (productValue->HasKey("delivery"))
					{
						if (productValue->GetNamedArray("delivery")->ValueType == JsonValueType::Array)
						{
							auto productArray = productValue->GetNamedArray("delivery");
							auto deliveryVector = ref new Vector<TrackerDeliveryOrderModels^>();
							for (const auto &item : productArray)
							{
								auto valueContent = item->GetObject();
								auto deliveryOrder = ref new TrackerDeliveryOrderModels(valueContent->HasKey("delivery_id") ? Helpers::ToNumber(valueContent->GetNamedValue("delivery_id")) : 0,
									valueContent->HasKey("price") ? Helpers::ToNumber(valueContent->GetNamedValue("price")) : 0.0,
									valueContent->HasKey("delivery_type_id") ? Helpers::ToNumber(valueContent->GetNamedValue("delivery_type_id")) : 0,
									valueContent->HasKey("delivery_period_id") ? Helpers::ToNumber(valueContent->GetNamedValue("delivery_period_id")) : 0,
									valueContent->HasKey("delivery_date") ? Helpers::ToString(valueContent->GetNamedValue("delivery_date")) : "");

								deliveryVector->Append(deliveryOrder);
							}

							order->Delivery = deliveryVector;
						}
					}
					else
					{
						order->Delivery = ref new Vector<TrackerDeliveryOrderModels^>();
					}

					vect->InsertAt(0, order);
				}

				return vect;
			}
		}).then(TaskExceptionExtensions<IVector<TrackerOrderModels^>^>());
	});
}