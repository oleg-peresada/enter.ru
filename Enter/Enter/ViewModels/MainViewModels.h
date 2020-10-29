#pragma once

#include <sstream>
#include <string>

#include "ViewModelsBase.h"
#include "LoadStateEventArgs.h"

#include "DataModel\HubDataModel.h"
#include "DataModel\Storage\AutorizationStorage.h"

#include "View\AboutShopView.xaml.h"
#include "View\AccountView.xaml.h"
#include "View\CategoryTreeView.xaml.h"
#include "View\BasketView.xaml.h"
#include "View\AccessoriesView.xaml.h"
#include "View\ProductView.xaml.h"
#include "View\ProductExtensionsView.xaml.h"

#include "Controls\CitiesMenuControl.xaml.h"

using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace ViewModels
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class MainViewModels sealed : public ViewModelsBase
		{
		public:
			virtual ~MainViewModels();

			property IObservableVector<Enter::DataModel::HubDataModel^>^ MainHubDataModel
			{
				IObservableVector<Enter::DataModel::HubDataModel^>^ get();
			}

			property IVector<CategoryTreeModels^>^ CategoryCollection
			{
				IVector<CategoryTreeModels^>^ get();
				void set(IVector<CategoryTreeModels^>^ value);
			}

			property IVector<PromoBannerModels^>^ PromoBanner
			{
				IVector<PromoBannerModels^>^ get();
				void set(IVector<PromoBannerModels^>^ value);
			}

			property Visibility ProgressPanel
			{
				Visibility get();
				void set(Visibility value);
			}

			property Visibility ContentPanel
			{
				Visibility get();
				void set(Visibility value);
			}

			property RelayCommand^ BasketCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ PromoCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ RefreshCommand
			{
				RelayCommand^ get();
			}
		internal:
			MainViewModels(Windows::UI::Xaml::Controls::Page^ page);
			concurrency::task<void> TaskLoaded(Object^ parameter, bool isCached);
			void OnMainHubClick(Object^ parameter);
			void OnCategoryHubClick(Object^ parameter);
			void OnCitiesPopupFlyout(Object^ parameter);
			void OnClosedPopup(Platform::Object ^sender, Platform::Object ^args);
			void OnWindowsActivated(Platform::Object ^sender, Windows::UI::Core::WindowActivatedEventArgs ^e);
			bool IsBackgroundTask(String^ nameTask);
			void ProgressOrContent(bool state);
		private:
			int GeoId;
			Windows::UI::Xaml::Controls::Primitives::Popup^ popupCities;
			IVector<PromoBannerModels^>^ source_promoBanner;
			EventRegistrationToken windowActivatedToken;
			EventRegistrationToken popupCloseCityToken;
			IVector<CategoryTreeModels^>^ m_CategoryCollection;
			Visibility m_progressPanel;
			Visibility m_contentPanel;
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
		};
	}
}