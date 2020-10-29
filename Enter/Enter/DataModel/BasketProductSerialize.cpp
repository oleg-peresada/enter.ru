#include "pch.h"
#include "BasketProductSerialize.h"

using namespace Enter::DataModel;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Data::Json;
using namespace Windows::Storage;

BasketProductDataModel::BasketProductDataModel(int id, String^ article, String^ token,
	String^ name, String^ image, int count, int quantity, float64 price)
	: source_id(id), source_article(article), source_token(token),
	source_name(name), source_image(image), source_count(count), 
	source_quantity(quantity), source_price(price)
{
}

int BasketProductDataModel::Id::get()
{
	return source_id;
}

String^ BasketProductDataModel::Article::get()
{
	return source_article;
}

String^ BasketProductDataModel::Token::get()
{
	return source_token;
}

String^ BasketProductDataModel::Name::get()
{
	return source_name;
}

String^ BasketProductDataModel::Image::get()
{
	return source_image;
}

int BasketProductDataModel::Count::get()
{
	return source_count;
}

int BasketProductDataModel::Quantity::get()
{
	return source_quantity;
}

float64 BasketProductDataModel::Price::get()
{
	return source_price;
}

const std::wstring BasketProductSerialize::fileNameJson = L"_basketProductSource.json";

BasketProductSerialize::BasketProductSerialize()
{
}

BasketProductSerialize::~BasketProductSerialize()
{
}

IAsyncOperation<IVector<BasketProductDataModel^>^>^ BasketProductSerialize::Open()
{
	using namespace concurrency;

	return create_async([this]() -> task<IVector<BasketProductDataModel^>^>
	{
		auto currentFolder = ApplicationData::Current->LocalFolder;
		return create_task(currentFolder->CreateFileAsync(StringReference(BasketProductSerialize::fileNameJson.c_str()), CreationCollisionOption::OpenIfExists)).then([this](StorageFile^ fileContent) -> task<IVector<BasketProductDataModel^>^>
		{
			return create_task(FileIO::ReadTextAsync(fileContent)).then([this](String^ content) -> IVector<BasketProductDataModel^>^
			{
				auto vect = ref new Vector<BasketProductDataModel^>();
				
				if (content != nullptr)
				{
					auto jsonContent = JsonObject::Parse(content);
					auto arrayProduct = jsonContent->GetNamedArray("product");

					for (const auto &item : arrayProduct)
					{
						auto jsonValue = item->GetObject();

						auto productModel = ref new BasketProductDataModel(jsonValue->GetNamedNumber("id"),
							jsonValue->GetNamedString("article"),
							jsonValue->GetNamedString("token"),
							jsonValue->GetNamedString("name"),
							jsonValue->GetNamedString("image"),
							jsonValue->GetNamedNumber("count"),
							jsonValue->GetNamedNumber("quantity"),
							jsonValue->GetNamedNumber("price"));
						vect->Append(productModel);
					}
				}

				return vect;
			});
		});
	});
}

IAsyncAction^ BasketProductSerialize::Save(IVector<BasketProductDataModel^>^ basketValue)
{
	using namespace concurrency;

	if (basketValue == nullptr && basketValue->Size == 0)
	{
		return nullptr;
	}

	return create_async([this, basketValue]()-> task<void>
	{
		auto currentFolder = ApplicationData::Current->LocalFolder;
		return create_task(currentFolder->CreateFileAsync(StringReference(BasketProductSerialize::fileNameJson.c_str()),
			CreationCollisionOption::ReplaceExisting)).then([this, basketValue](StorageFile^ fileContent)
		{
			auto jsonArray = ref new JsonArray();

			for (const auto &item : basketValue)
			{
				auto jsonProduct = ref new JsonObject();
				jsonProduct->SetNamedValue("id", JsonValue::CreateNumberValue(item->Id));
				jsonProduct->SetNamedValue("article", JsonValue::CreateStringValue(item->Article));
				jsonProduct->SetNamedValue("token", JsonValue::CreateStringValue(item->Token));
				jsonProduct->SetNamedValue("name", JsonValue::CreateStringValue(item->Name));
				jsonProduct->SetNamedValue("image", JsonValue::CreateStringValue(item->Image));
				jsonProduct->SetNamedValue("count", JsonValue::CreateNumberValue(item->Count));
				jsonProduct->SetNamedValue("quantity", JsonValue::CreateNumberValue(item->Quantity));
				jsonProduct->SetNamedValue("price", JsonValue::CreateNumberValue(item->Price));

				jsonArray->Append(jsonProduct);
			}

			auto jsonObject = ref new JsonObject();
			jsonObject->SetNamedValue("product", jsonArray);

			auto f = jsonObject->Stringify();
			return FileIO::WriteTextAsync(fileContent, jsonObject->Stringify());
		});
	});
}

ProductDeliveryDataModel::ProductDeliveryDataModel(IVector<OrderShopListModels^>^ shop,
	IVector<IntervalListModels^>^ interval,
	double deliveryPrice,
	int deliveryId, BasketProductDataModel^ item, OrderShopListModels^ orderShop) : source_id(deliveryId),
	source_deliveryPrice(deliveryPrice), source_shop(shop), source_interval(interval), source_item(item), source_currentShop(orderShop)
{
}

int ProductDeliveryDataModel::Id::get()
{
	return source_id;
}

double ProductDeliveryDataModel::DeliveryPrice::get()
{
	return source_deliveryPrice;
}

IVector<OrderShopListModels^>^ ProductDeliveryDataModel::Shop::get()
{
	return source_shop;
}

IVector<IntervalListModels^>^ ProductDeliveryDataModel::Interval::get()
{
	return source_interval;
}

BasketProductDataModel^ ProductDeliveryDataModel::Item::get()
{
	return source_item;
}

OrderShopListModels^ ProductDeliveryDataModel::CurrentShop::get()
{
	return source_currentShop;
}

IntervalListModels^ ProductDeliveryDataModel::CurrentInterval::get()
{
	return source_currentInterval;
}

void ProductDeliveryDataModel::CurrentInterval::set(IntervalListModels^ val)
{
	source_currentInterval = val;
}

String^ ProductDeliveryDataModel::CurrentDateTime::get()
{
	return source_currentDateTime;
}

void ProductDeliveryDataModel::CurrentDateTime::set(String^ valTime)
{
	source_currentDateTime = valTime;
}

IVector<String^>^ ProductDeliveryDataModel::DateTimeDelivery::get()
{
	return source_dateTimeDelivery;
}

void ProductDeliveryDataModel::DateTimeDelivery::set(IVector<String^>^ value)
{
	source_dateTimeDelivery = value;
}

DeliveryGroupProductDataModel::DeliveryGroupProductDataModel(IVector<BasketProductDataModel^>^ vectorProduct, OrderCalcModels^ vectorDelivery)
	: source_vectorProduct(vectorProduct), source_vectorDelivery(vectorDelivery)
{
}

IVector<BasketProductDataModel^>^ DeliveryGroupProductDataModel::VectorProduct::get()
{
	return source_vectorProduct;
}

OrderCalcModels^ DeliveryGroupProductDataModel::Delivery::get()
{
	return source_vectorDelivery;
}

bool DeliveryGroupProductDataModel::IsInterval(IntervalListModels^ element, IVector<IntervalListModels^>^ collection)
{
	for (const auto &item : collection)
	{
		if (item->Id == element->Id) return true;
	}

	return collection->Size == 0 ? false : true;
}

bool DeliveryGroupProductDataModel::IsShop(IVector<OrderShopListModels^>^ shop, int id_shop)
{
	if (shop == nullptr && shop->Size == 0) return false;

	unsigned int size = shop->Size;

	for (unsigned int index = 0; index < size; index++)
	{
		auto element = shop->GetAt(index);
		if (element->Id == id_shop)
		{
			return true;
		}
	}

	return false;
}

BasketProductDataModel^ DeliveryGroupProductDataModel::FindProductBasket(int productId)
{
	for (const auto &itemProduct : VectorProduct)
	{
		if (itemProduct->Id == productId) return itemProduct;
	}

	return nullptr;
}

IntervalListModels^ DeliveryGroupProductDataModel::FindInterval(int intervalId)
{
	auto interval = Delivery->IntervalList;
	for (const auto &itemInterval : interval)
	{
		if (itemInterval->Id == intervalId) return itemInterval;
	}

	return nullptr;
}

OrderShopListModels^ DeliveryGroupProductDataModel::FindShop(int shopId)
{
	auto shop = Delivery->ShopList;
	for (const auto &itemShop : shop)
	{
		if (itemShop->Id == shopId) return itemShop;
	}

	return nullptr;
}

ProductDeliveryDataModel^ DeliveryGroupProductDataModel::StandartDelivery(int idProduct, StandartDeliveryModels^ element)
{
	auto vectInterval = ref new Vector<IntervalListModels^>();
	auto vectShop = ref new Vector<OrderShopListModels^>();
	auto vectDateTime = ref new Vector<String^>();

	auto productItem = FindProductBasket(idProduct);
	auto Id = element->Id;
	auto deliveryPrice = element->Price;

	for (const auto &itemDate : element->Datalist)
	{
		vectDateTime->InsertAt(0, itemDate->DateTime);
		for (const auto itemInterval : itemDate->IntervalList)
		{
			auto interval = FindInterval(itemInterval);
			if (interval != nullptr) vectInterval->Append(interval);
		}
	}

	auto product = ref new ProductDeliveryDataModel(vectShop, vectInterval, deliveryPrice, Id, productItem, nullptr);
	product->CurrentInterval = vectInterval->Size > 0 ? vectInterval->GetAt(0) : nullptr;
	
	if (vectDateTime->Size > 0)
	{
		std::sort(begin(vectDateTime), end(vectDateTime));
		product->CurrentDateTime = vectDateTime->GetAt(0);
	}

	product->DateTimeDelivery = vectDateTime;

	return product;
}

ProductDeliveryDataModel^ DeliveryGroupProductDataModel::PickupDelivery(int idProduct, PickupDeliveryModels^ element)
{
	auto vectInterval = ref new Vector<IntervalListModels^>();
	auto vectShop = ref new Vector<OrderShopListModels^>();
	auto vectDateTime = ref new Vector<String^>();

	auto productItem = FindProductBasket(idProduct);
	auto Id = element->Id;
	auto deliveryPrice = element->Price;

	auto s = element->VectorDateInterval;
	for (const auto &itemDate : element->VectorDateInterval)
	{
		vectDateTime->InsertAt(0, itemDate->DateTime);
		for (const auto &itemShop : itemDate->VectShop)
		{
			if (!IsShop(vectShop, itemShop->Id))
			{
				auto elementShop = FindShop(itemShop->Id);
				if (elementShop != nullptr) vectShop->Append(elementShop);
			}

			for (const auto &itemInterval : itemShop->IntervalList)
			{
				auto elementInterval = FindInterval(itemInterval);
				if (elementInterval != nullptr && !this->IsInterval(elementInterval, vectInterval)) vectInterval->Append(elementInterval);
			}
		}
	}

	auto elementShop = vectShop->Size > 0 ? vectShop->GetAt(0) : nullptr;
	auto product = ref new ProductDeliveryDataModel(vectShop, vectInterval, deliveryPrice, Id, productItem, elementShop);
	product->CurrentInterval = vectInterval->Size > 0 ? vectInterval->GetAt(0) : nullptr;

	if (vectDateTime->Size > 0)
	{
		std::sort(begin(vectDateTime), end(vectDateTime));
		product->CurrentDateTime = vectDateTime->GetAt(0);
	}

	product->DateTimeDelivery = vectDateTime;

	return product;
}

ProductDeliveryDataModel^ DeliveryGroupProductDataModel::PickupUpDelivery(int idProduct, PickupUpNowDeliveryModels^ element)
{
	auto vectInterval = ref new Vector<IntervalListModels^>();
	auto vectShop = ref new Vector<OrderShopListModels^>();
	auto vectDateTime = ref new Vector<String^>();

	auto productItem = FindProductBasket(idProduct);
	auto Id = element->Id;
	auto deliveryPrice = 0.0;

	for (const auto &itemDate : element->VectorDateInterval)
	{
		vectDateTime->InsertAt(0, itemDate->DateTime);
		for (const auto &itemShop : itemDate->VectShop)
		{
			if (!IsShop(vectShop, itemShop->Id))
			{
				auto elementShop = FindShop(itemShop->Id);
				if (elementShop != nullptr) vectShop->Append(elementShop);
			}

			for (const auto &itemInterval : itemShop->IntervalList)
			{
				auto elementInterval = FindInterval(itemInterval);
				if (elementInterval != nullptr && !this->IsInterval(elementInterval, vectInterval)) vectInterval->Append(elementInterval);
			}
		}
	}

	auto elementShop = vectShop->Size > 0 ? vectShop->GetAt(0) : nullptr;
	auto product = ref new ProductDeliveryDataModel(vectShop, vectInterval, deliveryPrice, Id, productItem, elementShop);
	product->CurrentInterval = vectInterval->Size > 0 ? vectInterval->GetAt(0) : nullptr;

	if (vectDateTime->Size > 0)
	{
		std::sort(begin(vectDateTime), end(vectDateTime));
		product->CurrentDateTime = vectDateTime->GetAt(0);
	}

	product->DateTimeDelivery = vectDateTime;

	return product;
}

IAsyncOperation<IObservableVector<ProductDeliveryDataModel^>^>^ DeliveryGroupProductDataModel::ToProductDeliveryAsync(ProductGroupDelivery valueElement)
{
	return concurrency::create_async([this, valueElement](concurrency::cancellation_token token)-> concurrency::task<IObservableVector<ProductDeliveryDataModel^>^>
	{
		return concurrency::create_task([this, valueElement]()->IObservableVector<ProductDeliveryDataModel^>^
		{
			auto delivery = Delivery;
			auto vectContent = ref new Vector<ProductDeliveryDataModel^>();

			if (delivery == nullptr) return vectContent;

			for (const auto &item : delivery->Mode)
			{
				if (valueElement == ProductGroupDelivery::Standart)
				{
					if (item->StandartDelivery != nullptr)
					{
						auto product = StandartDelivery(item->Id, item->StandartDelivery);
						vectContent->Append(product);
					}
					else if (item->PickupDelivery != nullptr)
					{
						auto product = PickupDelivery(item->Id, item->PickupDelivery);
						vectContent->Append(product);
					}
					else if (item->PickupDeliveryUp != nullptr)
					{
						auto product = PickupUpDelivery(item->Id, item->PickupDeliveryUp);
						vectContent->Append(product);
					}
				}
				else if (valueElement == ProductGroupDelivery::Pickup)
				{
					if (item->PickupDelivery != nullptr)
					{
						auto product = PickupDelivery(item->Id, item->PickupDelivery);
						vectContent->Append(product);
					}
					else if (item->StandartDelivery != nullptr)
					{
						auto product = StandartDelivery(item->Id, item->StandartDelivery);
						vectContent->Append(product);
					}
					else if (item->PickupDeliveryUp != nullptr)
					{
						auto product = PickupUpDelivery(item->Id, item->PickupDeliveryUp);
						vectContent->Append(product);
					}
				}
				else if (valueElement == ProductGroupDelivery::PickupUp)
				{
					if (item->PickupDeliveryUp != nullptr)
					{
						auto product = PickupUpDelivery(item->Id, item->PickupDeliveryUp);
						vectContent->Append(product);
					}
					else if (item->PickupDelivery != nullptr)
					{
						auto product = PickupDelivery(item->Id, item->PickupDelivery);
						vectContent->Append(product);
					}
					else if (item->StandartDelivery != nullptr)
					{
						auto product = StandartDelivery(item->Id, item->StandartDelivery);
						vectContent->Append(product);
					}
				}
			}

			return vectContent;
		});
	});
}