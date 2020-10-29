#pragma once

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation::Collections;

namespace EnterStore
{
	namespace Models
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class StateCard sealed
		{
		public:
			property bool IsBuyable
			{
				bool get();
			}
		internal:
			StateCard(bool is_buyable);
		private:
			bool m_isbuyable;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PromoCard sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ Name
			{
				String^ get();
			}

			property String^ MediaImage
			{
				String^ get();
			}

		internal:
			PromoCard(int id, String^ name, String^ mediaImage);
		private:
			int m_id;
			String^ m_name;
			String^ m_mediaImage;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductCardModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ Name
			{
				String^ get();
			}

			property String^ Token
			{
				String^ get();
			}

			property String^ Article
			{
				String^ get();
			}

			property String^ BarCode
			{
				String^ get();
			}

			property String^ Announce
			{
				String^ get();
			}

			property String^ Rating
			{
				String^ get();
			}

			property double Price
			{
				double get();
			}

			property String^ MediaImage
			{
				String^ get();
			}

			property IVector<PromoCard^>^ LabelCard
			{
				IVector<PromoCard^>^ get();
				void set(IVector<PromoCard^>^ value);
			}

			property StateCard^ State
			{
				StateCard^ get();
				void set(StateCard^ value);
			}
		internal:
			ProductCardModels(int id, 
				String^ name, 
				String^ token, 
				String^ article, 
				String^ barCode, 
				String^ announce, 
				String^ rating, 
				double price, 
				String^ media_image);
		private:
			int source_id;
			String^ source_name;
			String^ source_token;
			String^ source_article;
			String^ source_barCode;
			String^ source_announce;
			String^ source_rating;
			double source_price;
			String^ source_mediaImage;
			IVector<PromoCard^>^ source_labelCard;
			StateCard^ source_state;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class TrackerIntervalOrderModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ Name
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
			TrackerIntervalOrderModels(int id, String^ name, String^ time_begin, String^ time_end);
		private:
			int m_id;
			String^ m_name;
			String^ m_time_begin;
			String^ m_time_end;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class TrackerProductOrderModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property int Price
			{
				int get();
			}

			property int Quantity
			{
				int get();
			}

			property double Sum
			{
				double get();
			}
		internal:
			TrackerProductOrderModels(int id, int price, int quantity, double sum);
		private:
			int m_id;
			int m_price;
			int m_quantity;
			double m_sum;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class TrackerDeliveryOrderModels sealed
		{
		public:
			property int DeliveryId
			{
				int get();
			}

			property double Price
			{
				double get();
			}

			property int DeliveryTypeId
			{
				int get();
			}

			property int DeliveryPeriodId
			{
				int get();
			}

			property String^ DeliveryDate
			{
				String^ get();
			}
		internal:
			TrackerDeliveryOrderModels(int delivery_id,
				double price, 
				int delivery_type_id,
				int delivery_period_id, 
				String^ delivery_date);
		private:
			int m_delivery_id;
			double m_price;
			int m_delivery_type_id;
			int m_delivery_period_id;
			String^ m_delivery_date;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class TrackerOrderModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property int TypeId
			{
				int get();
			}

			property int StatusId
			{
				int get();
			}

			property String^ Number
			{
				String^ get();
			}

			property String^ NumberExp
			{
				String^ get();
			}

			property int UserId
			{
				int get();
			}

			property String^ Email
			{
				String^ get();
			}

			property String^ LastName
			{
				String^ get();
			}

			property String^ FirstName
			{
				String^ get();
			}

			property String^ MiddleName
			{
				String^ get();
			}

			property String^ Phone
			{
				String^ get();
			}

			property String^ Mobile
			{
				String^ get();
			}

			property int PaymentStatusId
			{
				int get();
			}

			property int PaymentId
			{
				int get();
			}

			property String^ PaymentDetail
			{
				String^ get();
			}

			property String^ CreditCardNumber
			{
				String^ get();
			}

			property String^ PaymentCardCode
			{
				String^ get();
			}

			property double Sum
			{
				double get();
			}

			property bool IsDelivery
			{
				bool get();
			}

			property bool IsDeliveryPaid
			{
				bool get();
			}

			property int DeliveryTypeId
			{
				int get();
			}

			property String^  DeliveryDate
			{
				String^ get();
			}

			property int DeliveryIntervalId
			{
				int get();
			}

			property int StoreId
			{
				int get();
			}

			property int ShopId
			{
				int get();
			}

			property int GeoId
			{
				int get();
			}

			property int RegionId
			{
				int get();
			}

			property String^ Address
			{
				String^ get();
			}

			property String^ Added
			{
				String^ get();
			}

			property String^ Updated
			{
				String^ get();
			}

			property unsigned int ProductSize
			{
				unsigned int get();
				void set(unsigned int value);
			}

			property IVector<TrackerIntervalOrderModels^>^ Interval
			{
				IVector<TrackerIntervalOrderModels^>^ get();
				void set(IVector<TrackerIntervalOrderModels^>^ value);
			}

			property IVector<TrackerProductOrderModels^>^ Product
			{
				IVector<TrackerProductOrderModels^>^ get();
				void set(IVector<TrackerProductOrderModels^>^ value);
			}

			property IVector<TrackerDeliveryOrderModels^>^ Delivery
			{
				IVector<TrackerDeliveryOrderModels^>^ get();
				void set(IVector<TrackerDeliveryOrderModels^>^ value);
			}
		internal:
			TrackerOrderModels(int id,
				int type_id,
				int status_id,
				String^ number,
				String^ number_exp,
				int user_id,
				String^ email,
				String^ last_name,
				String^ first_name,
				String^ middle_name,
				String^ phone,
				String^ mobile,
				int payment_status_id,
				int payment_id,
				String^ payment_detail,
				String^ credit_card_number,
				String^ payment_card_code,
				double sum,
				bool is_delivery,
				bool is_delivery_paid,
				int delivery_type_id,
				String^ delivery_date,
				int delivery_interval_id,
				int store_id,
				int shop_id,
				int geo_id,
				int region_id,
				String^ address,
				String^ added,
				String^ updated);
		private:
			int m_id;
			int m_typeId;
			int m_statusId;
			String^ m_number;
			String^ m_numberExp;
			int m_userId;
			String^ m_email;
			String^ m_lastName;
			String^ m_firstName;
			String^ m_middleName;
			String^ m_phone;
			String^ m_mobile;
			int m_payment_status_id;
			int m_payment_id;
			String^ m_payment_detail;
			String^ m_credit_card_number;
			String^ m_payment_card_code;
			double m_sum;
			bool m_isDelivery;
			bool m_isDeliveryPaid;
			int m_delivery_type_id;
			String^ m_delivery_date;
			int m_delivery_interval_id;
			int m_store_id;
			int m_shopId;
			int m_geoId;
			int m_regionId;
			String^ m_address;
			String^ m_added;
			String^ m_updated;
			unsigned int m_productSize;
			IVector<TrackerIntervalOrderModels^>^ m_interval;
			IVector<TrackerProductOrderModels^>^ m_product;
			IVector<TrackerDeliveryOrderModels^>^ m_delivery;
		};
	}
}