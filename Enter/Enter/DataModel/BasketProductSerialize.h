#pragma once

#include <string>
#include "Helpers.h"

#include <algorithm>

using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace DataModel
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class BasketProductDataModel sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ Article
			{
				String^ get();
			}

			property String^ Token
			{
				String^ get();
			}

			property String^ Name
			{
				String^ get();
			}

			property String^ Image
			{
				String^ get();
			}

			property int Count
			{
				int get();
			}

			property int Quantity
			{
				int get();
			}

			property float64 Price
			{
				float64 get();
			}
		internal:
			BasketProductDataModel(int id, String^ article, String^ token, 
				String^ name, String^ image, int count, int quantity, float64 price);
		private:
			int source_id;
			String^ source_article;
			String^ source_token;
			String^ source_name;
			String^ source_image;
			int source_count;
			int source_quantity;
			float64 source_price;
		};

		class BasketProductSerialize
		{
		public:
			BasketProductSerialize();
			~BasketProductSerialize();
			IAsyncOperation<IVector<BasketProductDataModel^>^>^ Open();
			IAsyncAction^ Save(IVector<BasketProductDataModel^>^ basketValue);
		private:
			const static std::wstring fileNameJson;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductDeliveryDataModel sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property double DeliveryPrice
			{
				double get();
			}

			property IVector<OrderShopListModels^>^ Shop
			{
				IVector<OrderShopListModels^>^ get();
			}

			property IVector<IntervalListModels^>^ Interval
			{
				IVector<IntervalListModels^>^ get();
			}

			property BasketProductDataModel^ Item
			{
				BasketProductDataModel^ get();
			}

			property OrderShopListModels^ CurrentShop
			{
				OrderShopListModels^ get();
			}

			property IntervalListModels^ CurrentInterval
			{
				IntervalListModels^ get();
				void set(IntervalListModels^ val);
			}

			property String^ CurrentDateTime
			{
				String^ get();
				void set(String^ value);
			}

			property IVector<String^>^ DateTimeDelivery
			{
				IVector<String^>^ get();
				void set(IVector<String^>^ value);
			}
		internal:
			ProductDeliveryDataModel(IVector<OrderShopListModels^>^ shop, 
				IVector<IntervalListModels^>^ interval,
				double deliveryPrice,
				int deliveryId,
				BasketProductDataModel^ item, OrderShopListModels^ orderShop);
		private:
			IVector<OrderShopListModels^>^ source_shop;
			IVector<IntervalListModels^>^ source_interval;
			double source_deliveryPrice;
			int source_id;
			OrderShopListModels^ source_currentShop;
			IntervalListModels^ source_currentInterval;
			BasketProductDataModel^ source_item;
			String^ source_currentDateTime;
			IVector<String^>^ source_dateTimeDelivery;
		};

		[Platform::Metadata::Flags]
		public enum class ProductGroupDelivery : unsigned int
		{
			Standart = 1,
			Pickup = 3,
			PickupUp = 4,
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class DeliveryGroupProductDataModel sealed
		{
		public:
			DeliveryGroupProductDataModel(IVector<BasketProductDataModel^>^ vectorProduct, OrderCalcModels^ vectorDelivery);

			property IVector<BasketProductDataModel^>^ VectorProduct
			{
				IVector<BasketProductDataModel^>^ get();
			}

			property OrderCalcModels^ Delivery
			{
				OrderCalcModels^ get();
			}

			IAsyncOperation<IObservableVector<ProductDeliveryDataModel^>^>^ ToProductDeliveryAsync(ProductGroupDelivery valueElement);
		private:
			bool IsInterval(IntervalListModels^ element, IVector<IntervalListModels^>^ collection);
			bool IsShop(IVector<OrderShopListModels^>^ shop, int id_shop);

			BasketProductDataModel^ FindProductBasket(int productId);
			IntervalListModels^ FindInterval(int intervalList);
			OrderShopListModels^ FindShop(int shopId);

			ProductDeliveryDataModel^ StandartDelivery(int idProduct, StandartDeliveryModels^ element);
			ProductDeliveryDataModel^ PickupDelivery(int idProduct, PickupDeliveryModels^ element);
			ProductDeliveryDataModel^ PickupUpDelivery(int idProduct, PickupUpNowDeliveryModels^ element);

			IVector<BasketProductDataModel^>^ source_vectorProduct;
			OrderCalcModels^ source_vectorDelivery;
		};
	}
}