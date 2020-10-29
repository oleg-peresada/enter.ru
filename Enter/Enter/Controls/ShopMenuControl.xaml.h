//
// ShopMenuControl.xaml.h
// Объявление класса ShopMenuControl
//

#pragma once

#include "Controls\ShopMenuControl.g.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace Controls
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class CityResultEventArgs sealed : Windows::UI::Xaml::RoutedEventArgs
		{
		public:
			CityResultEventArgs();

			property EnterStore::Models::ShopListModels^ Item
			{
				EnterStore::Models::ShopListModels^ get();
			}
		internal:
			CityResultEventArgs(EnterStore::Models::ShopListModels^ shopItem);
		private:
			EnterStore::Models::ShopListModels^ source_Shop;
		};

		public delegate void TappedCityHandler(Object^ sender, CityResultEventArgs^ args);

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ShopMenuControl sealed
		{
		public:
			ShopMenuControl();
			event TappedCityHandler^ TappedCity;

			event TappedCityHandler^ OnTappedCityHandler
			{
				EventRegistrationToken add(TappedCityHandler^ token)
				{
					return TappedCity += token;
				}

				void remove(EventRegistrationToken token)
				{
					TappedCity -= token;
				}

				void raise(Object^ sender, CityResultEventArgs^ args)
				{
					TappedCity(sender, args);
				}
			}
		private:
			void OnSaveClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
			void OnCloseClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		};
	}
}
