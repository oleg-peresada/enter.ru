#pragma once

#include "ViewModelsBase.h"
#include "LoadStateEventArgs.h"
#include "RelayCommand.h"

#include "View\ProductExtensionsView.xaml.h"
#include "DataModel\HubDataModel.h"

using namespace Enter;
using namespace Enter::DataModel;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace ViewModels
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class TrackerExtensionsViewModels sealed : public ViewModelsBase
		{
		public:
			property String^ NumberTracker
			{
				String^ get();
				void set(String^ value);
			}

			property IVector<ProductCardModels^>^ ProductVector
			{
				IVector<ProductCardModels^>^ get();
				void set(IVector<ProductCardModels^>^ value);
			}

			property TrackerOrderModels^ OrderTracker
			{
				TrackerOrderModels^ get();
				void set(TrackerOrderModels^ value);
			}

			property IVector<TrackerNewDataModel^>^ VectorTracker
			{
				IVector<TrackerNewDataModel^>^ get();
				void set(IVector<TrackerNewDataModel^>^ value);
			}
		internal:
			TrackerExtensionsViewModels(Windows::UI::Xaml::Controls::Page^ page);
			TrackerNewDataModel^ FindNewTracker(TrackerProductOrderModels^ new_value);
			void OnProductItemClick(Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
		private:
			String^ m_numberTracker;
			IVector<ProductCardModels^>^ m_productVector;
			TrackerOrderModels^ m_orderTracker;
			IVector<TrackerNewDataModel^>^ m_VectorTracker;
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
		};
	}
}