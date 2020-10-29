#pragma once

#include "ViewModelsBase.h"
#include "LoadStateEventArgs.h"
#include "RelayCommand.h"
#include "Controls\ShopMenuControl.xaml.h"
#include "Controls\ImageShopControl.xaml.h"
#include "DataModel\GroupCategorySource.h"
#include "DataModel\Storage\AutorizationStorage.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace ViewModels
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class AboutShopViewModels sealed : public ViewModelsBase
		{
		public:
			virtual ~AboutShopViewModels();

			property IVector<EnterStore::Models::ShopListModels^>^ ShopCollection
			{
				IVector<EnterStore::Models::ShopListModels^>^ get();
				void set(IVector<EnterStore::Models::ShopListModels^>^ val);
			}

			property unsigned int CountImages
			{
				unsigned int get();
				void set(unsigned int val);
			}

			property EnterStore::Models::ShopListModels^ Shop
			{
				EnterStore::Models::ShopListModels^ get();
				void set(EnterStore::Models::ShopListModels^ val);
			}

			property double WidthAbout
			{
				double get();
				void set(double value);
			}

			property RelayCommand^ ImageCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ MoreShopCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ RefreshCommand
			{
				RelayCommand^ get();
			}
		internal:
			AboutShopViewModels(Windows::UI::Xaml::Controls::Page^ page);
			void LoadedTask(bool isCached);
			void OnElementShop(EnterStore::Models::ShopListModels^ element);
			void OnTappedImage();
			void OnShopPopup();
		private:
			Windows::UI::Xaml::Controls::Primitives::Popup^ popupShop;
			IVector<EnterStore::Models::ShopListModels^>^ about_shopCollection;
			EnterStore::Models::ShopListModels^ about_Shop;
			unsigned int about_countImages;
			Enter::Controls::ShopMenuControl^ shopControlMenu;
			double m_widthAbout;

			EventRegistrationToken eventTappedCity;
			EventRegistrationToken windowActivatedToken;
			EventRegistrationToken popupShopToken;

			void OnTappedCityPopup(Object ^sender, Enter::Controls::CityResultEventArgs ^args);
			void OnClosePopupCity(Platform::Object ^sender, Platform::Object ^args);
			void OnWindowsActivated(Platform::Object ^sender, Windows::UI::Core::WindowActivatedEventArgs ^e);
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
		};
	}
}