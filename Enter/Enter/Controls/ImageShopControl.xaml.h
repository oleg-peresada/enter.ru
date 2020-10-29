//
// ImageShopControl.xaml.h
// Объявление класса ImageShopControl
//

#pragma once

#include "Controls\ImageShopControl.g.h"

namespace Enter
{
	namespace Controls
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ImageShopControl sealed
		{
		public:
			ImageShopControl();
		private:
			void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		};
	}
}
