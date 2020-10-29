#pragma once

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace EnterStore
{
	namespace Models
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PickupDateShopListModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property Array<int>^ IntervalList
			{
				Array<int>^ get();
			}
		internal:
			PickupDateShopListModels(int id, Array<int>^ interval_list);
		private:
			int source_id;
			Array<int>^ source_intervallist;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PickupDateListModels sealed
		{
		public:
			property String^ DateTime
			{
				String^ get();
			}

			property IVector<PickupDateShopListModels^>^ VectShop
			{
				IVector<PickupDateShopListModels^>^ get();
			}
		internal:
			PickupDateListModels(String^ dateTime, IVector<PickupDateShopListModels^>^ vectShop);
		private:
			String^ source_dateTime;
			IVector<PickupDateShopListModels^>^ source_vectShop;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class StandartDateListModels sealed
		{
		public:
			property String^ DateTime
			{
				String^ get();
			}

			property Array<int>^ IntervalList
			{
				Array<int>^ get();
			}
		internal:
			StandartDateListModels(String^ dateTime, Array<int>^ intervalList);
		private:
			String^ source_dateTime;
			Array<int>^ source_intervalList;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PickupUpNowDeliveryModels sealed
		{
		public:
			property unsigned int Id
			{
				unsigned int get();
			}

			property String^ Name
			{
				String^ get();
			}

			property String^ Token
			{
				String^ get();
			}

			property String^ Description
			{
				String^ get();
			}

			property IVector<PickupDateListModels^>^ VectorDateInterval
			{
				IVector<PickupDateListModels^>^ get();
				void set(IVector<PickupDateListModels^>^ val);
			}
		internal:
			PickupUpNowDeliveryModels(unsigned int id, String^ name, String^ token, String^ description);
		private:
			unsigned int source_Id;
			String^ source_name;
			String^ source_Token;
			String^ source_description;
			IVector<PickupDateListModels^>^ source_VectorDateInterval;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PickupDeliveryModels sealed
		{
		public:
			property unsigned int Id
			{
				unsigned int get();
			}

			property String^ Name
			{
				String^ get();
			}

			property String^ Token
			{
				String^ get();
			}

			property int DeliveryId
			{
				int get();
			}

			property double Price
			{
				double get();
			}

			property IVector<PickupDateListModels^>^ VectorDateInterval
			{
				IVector<PickupDateListModels^>^ get();
				void set(IVector<PickupDateListModels^>^ val);
			}
		internal:
			PickupDeliveryModels(unsigned int id, String^ name, String^ token, int deliveryId, double price);
		private:
			unsigned int source_id;
			String^ source_name;
			String^ source_token;
			int source_deliveryId;
			double source_price;
			IVector<PickupDateListModels^>^ source_VectorDateInterval;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class StandartDeliveryModels sealed
		{
		public:
			property unsigned int Id
			{
				unsigned int get();
			}

			property String^ Name
			{
				String^ get();
			}

			property String^ Token
			{
				String^ get();
			}

			property int DeliveryId
			{
				int get();
			}

			property double Price
			{
				double get();
			}

			property IVector<StandartDateListModels^>^ Datalist
			{
				IVector<StandartDateListModels^>^ get();
				void set(IVector<StandartDateListModels^>^ val);
			}
		internal:
			StandartDeliveryModels(unsigned int id, String^ name, String^ token, int deliveryId, double price);
		private:
			unsigned int source_id;
			String^ source_name;
			String^ source_token;
			int source_deliveryId;
			double source_price;
			IVector<StandartDateListModels^>^ source_datalist;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class DeliveryModeListModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ Token
			{
				String^ get();
			}

			property PickupDeliveryModels^ PickupDelivery
			{
				PickupDeliveryModels^ get();
				void set(PickupDeliveryModels^ val);
			}

			property PickupUpNowDeliveryModels^ PickupDeliveryUp
			{
				PickupUpNowDeliveryModels^ get();
				void set(PickupUpNowDeliveryModels^ val);
			}

			property StandartDeliveryModels^ StandartDelivery
			{
				StandartDeliveryModels^ get();
				void set(StandartDeliveryModels^ val);
			}
		internal:
			DeliveryModeListModels(int id, String^ token);
		private:
			int source_id;
			String^ source_token;
			PickupDeliveryModels^ source_pickupDelivery;
			PickupUpNowDeliveryModels^ source_pickupDeliveryUp;
			StandartDeliveryModels^ source_standartDelivery;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class IntervalListModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ Ui
			{
				String^ get();
			}

			property String^ TimeBegin
			{
				String^ get();
			}

			property String^ TimeEnd
			{
				String^ get();
			}
		internal:
			IntervalListModels(int id, String^ ui, String^ timeBegin, String^ timeEnd);
		private:
			int source_id;
			String^ source_ui;
			String^ source_TimeBegin;
			String^ source_TimeEnd;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class OrderShopListModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ Ui
			{
				String^ get();
			}

			property String^ Name
			{
				String^ get();
			}

			property int GeoId
			{
				int get();
			}

			property String^ Address
			{
				String^ get();
			}

			property String^ WorkingTime
			{
				String^ get();
			}

			property double CoordLat
			{
				double get();
			}

			property double CoordLong
			{
				double get();
			}
		internal:
			OrderShopListModels(int id, String^ ui, String^ name, int geoId, String^ address, String^ workingTime, double coordLat, double coordLong);
		private:
			int source_id;
			String^ source_ui;
			String^ source_name;
			int source_geoId;
			String^ source_address;
			String^ source_workingTime;
			double source_coordLat;
			double source_coordLong;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class OrderCalcModels sealed
		{
		public:
			property IVector<DeliveryModeListModels^>^ Mode
			{
				IVector<DeliveryModeListModels^>^ get();
			}

			property IVector<IntervalListModels^>^ IntervalList
			{
				IVector<IntervalListModels^>^ get();
			}

			property IVector<OrderShopListModels^>^ ShopList
			{
				IVector<OrderShopListModels^>^ get();
			}
		internal:
			OrderCalcModels(IVector<DeliveryModeListModels^>^ mode,
				IVector<IntervalListModels^>^ intervalList,
				IVector<OrderShopListModels^>^ shopList);
		private:
			IVector<DeliveryModeListModels^>^ source_Mode;
			IVector<IntervalListModels^>^ source_intervalList;
			IVector<OrderShopListModels^>^ source_OrderShopList;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class UserContentModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ Ui
			{
				String^ get();
			}

			property String^ FirstName
			{
				String^ get();
			}

			property String^ LastName
			{
				String^ get();
			}

			property String^ MiddleName
			{
				String^ get();
			}

			property String^ Sex
			{
				String^ get();
			}

			property String^ Occupation
			{
				String^ get();
			}

			property String^ Email
			{
				String^ get();
			}

			property String^ Phone
			{
				String^ get();
			}

			property String^ MobilePhone
			{
				String^ get();
			}

			property String^ Skype
			{
				String^ get();
			}

			property String^ Birtday
			{
				String^ get();
			}
		internal:
			UserContentModels(int id, String^ ui,
				String^ firstName, String^ lastName,
				String^ middleName, String^ sex,
				String^ occupation, String^ email,
				String^ phone, String^ mobilePhone,
				String^ skype, String^ birthday);
		private:
			int source_id;
			String^ source_ui;
			String^ source_firstName;
			String^ source_lastName;
			String^ source_middleName;
			String^ source_sex;
			String^ source_occupation;
			String^ source_email;
			String^ source_phone;
			String^ source_mobilePhone;
			String^ source_skype;
			String^ source_birthday;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PersonalDataUpdateModels sealed
		{
		public:
			PersonalDataUpdateModels(String^ firstName, String^ lastName, String^ middleName,
				String^ sex, String^ occupation, String^ email, String^ phone,
				String^ mobilePhone, String^ birtday, String^ skype);

			property String^ FirstName
			{
				String^ get();
			}

			property String^ LastName
			{
				String^ get();
			}

			property String^ MiddleName
			{
				String^ get();
			}

			property String^ Sex
			{
				String^ get();
			}

			property String^ Occupation
			{
				String^ get();
			}

			property String^ Email
			{
				String^ get();
			}

			property String^ Phone
			{
				String^ get();
			}

			property String^ MobilePhone
			{
				String^ get();
			}

			property String^ Birthday
			{
				String^ get();
			}

			property String^ Skype
			{
				String^ get();
			}
		private:
			String^ source_firstName;
			String^ source_lastName;
			String^ source_middleName;
			String^ source_sex;
			String^ source_Occupation;
			String^ source_Email;
			String^ source_phone;
			String^ source_mobilePhone;
			String^ source_birthday;
			String^ source_skype;
		};
	}
}