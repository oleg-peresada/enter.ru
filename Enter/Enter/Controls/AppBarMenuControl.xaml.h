//
// AppBarMenuControl.xaml.h
// Объявление класса AppBarMenuControl
//

#pragma once

#include "Controls\AppBarMenuControl.g.h"

#include "View\CategoryTreeView.xaml.h"
#include "View\BasketView.xaml.h"

namespace Enter
{
	namespace Controls
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class AppBarMenuControl sealed
		{
		public:
			AppBarMenuControl();
		private:
			void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
			void OnItemClickCategory(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
			void OnHomeClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
			void OnBasketClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		};
	}
}
