//
// PickShopControl.xaml.h
// Объявление класса PickShopControl
//

#pragma once

#include "Controls\PickShopControl.g.h"
#include "DataModel\GroupCategorySource.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace Controls
	{
		public delegate void PickShopItemClickHandler(Object^ sender, Object^ Item);

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PickShopControl sealed
		{
		public:
			PickShopControl();

			event PickShopItemClickHandler^ PickShopItemClick;
		internal:
			event PickShopItemClickHandler^ OnPickShopItemClick
			{
				EventRegistrationToken add(PickShopItemClickHandler^ handler)
				{
					return PickShopItemClick += handler;
				}

				void remove(EventRegistrationToken token)
				{
					PickShopItemClick -= token;
				}

				void raise(Object^ sender, Object^ item)
				{
					return PickShopItemClick(sender, item);
				}
			}
		private:
			Windows::UI::Xaml::Controls::ContentControl^ popupContent;

			void OnItemClickShop(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
			void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
			void OnMapTapped(Platform::Object^ sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs^ e);
			void OnTappedPushPin(Platform::Object ^sender, Windows::UI::Xaml::Input::TappedRoutedEventArgs ^e);
			void OnSelectedPush(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
			void OnUnloaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		};
	}
}
