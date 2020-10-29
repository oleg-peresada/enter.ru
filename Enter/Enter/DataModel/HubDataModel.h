#pragma once

using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace DataModel
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class HubDataModel sealed
		{
		public:
			property Platform::String^ Name
			{
				Platform::String^ get();
			}

			property Platform::String^ Description
			{
				Platform::String^ get();
			}
		internal:
			HubDataModel(Platform::String^ name, Platform::String^ description);
		private:
			Platform::String^ hub_name;
			Platform::String^ hub_description;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class TrackerNewDataModel sealed
		{
		public:
			property TrackerProductOrderModels^ TrackerOrder
			{
				TrackerProductOrderModels^ get();
			}

			property ProductCardModels^ OrderCard
			{
				ProductCardModels^ get();
			}
		internal:
			TrackerNewDataModel(TrackerProductOrderModels^ trackerOrder, ProductCardModels^ orderCard);
		private:
			TrackerProductOrderModels^ m_trackerOrder;
			ProductCardModels^ m_orderCard;
		};
	}
}