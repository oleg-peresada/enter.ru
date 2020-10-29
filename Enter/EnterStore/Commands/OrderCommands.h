#pragma once

#include <collection.h>
#include <string>
#include <vector>

#include "HttpCommand.h"
#include "Helpers.h"
#include "Models\TrackerCardModels.h"

using namespace EnterStore;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;

namespace EnterStore
{
	namespace Commands
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class OrderDeliveryResult sealed
		{
		public:
			OrderDeliveryResult(Object^ confirmed,
				Object^ id,
				Object^ number,
				Object^ numberExp,
				double paySum,
				double price,
				Object^ user_id);

			property Object^ Confirmed
			{
				Object^ get();
			}

			property Object^ Id
			{
				Object^ get();
			}

			property Object^ Number
			{
				Object^ get();
			}

			property Object^ NumberExp
			{
				Object^ get();
			}

			property double PaySum
			{
				double get();
			}

			property double Price
			{
				double get();
			}

			property Object^ UserId
			{
				Object^ get();
			}
		private:
			Object^ source_confirmed;
			Object^ source_id;
			Object^ source_number;
			Object^ source_numberErp;
			double source_paySum;
			double source_price;
			Object^ source_userId;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class OrderQueryProduct sealed
		{
		public:
			OrderQueryProduct(int id, int quantity);

			property int Id
			{
				int get();
			}

			property int Quantity
			{
				int get();
			}
		private:
			int source_id;
			int source_quantity;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class OrderQueryField sealed
		{
		public:
			OrderQueryField(int typeId,
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
				String^ addressApartment);

			property int TypeId
			{
				int get();
			}

			property int GeoId
			{
				int get();
			}

			property int PaymentId
			{
				int get();
			}

			property int PaymentStatusId
			{
				int get();
			}

			property int DeliveryTypeId
			{
				int get();
			}

			property String^ DeliveryDate
			{
				String^ get();
			}

			property int DeliveryIntervalId
			{
				int get();
			}

			property int ShopId
			{
				int get();
			}

			property String^ FirstName
			{
				String^ get();
			}

			property String^ LastName
			{
				String^ get();
			}

			property String^ Phone
			{
				String^ get();
			}

			property String^ Email
			{
				String^ get();
			}

			property String^ AddressStreet
			{
				String^ get();
			}

			property String^ AddressBuilding
			{
				String^ get();
			}

			property String^ AddressNumber
			{
				String^ get();
			}

			property String^ AddressFloor
			{
				String^ get();
			}

			property String^ AddressApartment
			{
				String^ get();
			}

			property OrderQueryProduct^ Product
			{
				OrderQueryProduct^ get();
				void set(OrderQueryProduct^ value);
			}
		internal:
			property IVector<OrderQueryProduct^>^ OrderProduct
			{
				IVector<OrderQueryProduct^>^ get();
				void set(IVector<OrderQueryProduct^>^ val);
			}

		private:
			int source_typeId;
			int source_geoId;
			int source_paymentId;
			int source_paymentStatusId;
			int source_deliveryTypeId;
			String^ source_deliveryDate;
			int source_deliveryIntervalId;
			int source_shopId;
			String^ source_firstName;
			String^ source_lastName;
			String^ source_phone;
			String^ source_email;
			String^ source_addressStreet;
			String^ source_addressBuilding;
			String^ source_addressNumber;
			String^ source_addressFloor;
			String^ source_addressApartment;
			IVector<OrderQueryProduct^>^ source_OrderProduct;
			OrderQueryProduct^ m_product;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class OrderCommands sealed
		{
		public:
			OrderCommands(String^ token);
			IAsyncOperationWithProgress<IVector<OrderDeliveryResult^>^, HttpProgress>^ OrderAsync(IVector<OrderQueryField^>^ fieldValue);

			property String^ Token
			{
				String^ get();
			}
		private:
			String^ source_token;
			int DeliveryOrder(IVector<OrderQueryField^>^ vect, int idDelivery, int shopId);
			IVector<OrderQueryField^>^ FromDeliveryOrder(IVector<OrderQueryField^>^ valueOrder);
			IVector<IHttpContent^>^ Stringify(IVector<OrderQueryField^>^ valueOrder);
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class TrackerCommands sealed
		{
		public:
			TrackerCommands(String^ token, int id);

			property String^ Token
			{
				String^ get();
			}

			property int Id
			{
				int get();
			}

			IAsyncOperationWithProgress<IVector<TrackerOrderModels^>^, HttpProgress>^ TrackerOrderAsync(bool isCached);
			IAsyncOperationWithProgress<IVector<TrackerOrderModels^>^, HttpProgress>^ TrackerOrderAsync();
		private:
			String^ source_token;
			int source_id;
		};
	}
}