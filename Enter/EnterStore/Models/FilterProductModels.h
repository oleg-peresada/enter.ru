#pragma once

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace EnterStore
{
	namespace Models
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class FilterOptionsModels sealed
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

			property int Global
			{
				int get();
			}

			property int Quantity
			{
				int get();
			}

			property int PropertyId
			{
				int get();
			}
		internal:
			FilterOptionsModels(int id, String^ name, int global, int quantity, int propertyId);
		private:
			int source_id;
			String^ source_name;
			int source_global;
			int source_quantity;
			int source_propertyId;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class FilterProductModels sealed
		{
		public:
			property String^ FilterId
			{
				String^ get();
			}

			property String^ Name
			{
				String^ get();
			}

			property int TypeId
			{
				int get();
			}

			property String^ Unit
			{
				String^ get();
			}

			property bool IsMultiple
			{
				bool get();
			}

			property bool IsSlider
			{
				bool get();
			}

			property String^ Step
			{
				String^ get();
			}

			property double Min
			{
				double get();
			}

			property double Max
			{
				double get();
			}

			property double GlobalMax
			{
				double get();
			}

			property double GlobalMin
			{
				double get();
			}

			property IVector<FilterOptionsModels^>^ Options
			{
				IVector<FilterOptionsModels^>^ get();
				void set(IVector<FilterOptionsModels^>^ val);
			}
		internal:
			FilterProductModels(String^ filterId, 
				String^ name,
				int filter_typeId,
				String^ unit,
				bool isMultiple,
				bool isSlider,
				String^ step,
				double filter_min,
				double filter_max,
				double globalMax,
				double globalMin);
		private:
			String^ source_filterId;
			String^ source_name;
			int source_typeId;
			String^ source_unit;
			bool source_isMultiple;
			bool source_isSlider;
			String^ source_step;
			double source_min;
			double source_max;
			double source_globalMax;
			double source_globalMin;
			IVector<FilterOptionsModels^>^ source_options;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PromoItem sealed
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
		internal:
			PromoItem(int id, int typeId);
		private:
			int m_id;
			int m_typeId;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PromoBannerModels sealed
		{
		public:
			property String^ Id
			{
				String^ get();
			}

			property String^ TypeId
			{
				String^ get();
			}

			property String^ Name
			{
				String^ get();
			}

			property String^ MediaImage
			{
				String^ get();
			}

			property String^ Url
			{
				String^ get();
			}

			property IVector<PromoItem^>^ PromoItems
			{
				IVector<PromoItem^>^ get();
			}

			PromoBannerModels();
			PromoBannerModels(String^ id, String^ typeId, String^ name, String^ mediaImage, String^ url, IVector<PromoItem^>^ promoItems);
		private:
			String^ source_id;
			String^ source_typeId;
			String^ source_name;
			String^ source_mediaImage;
			String^ m_url;
			IVector<PromoItem^>^ m_promoItems;
		};
	}
}