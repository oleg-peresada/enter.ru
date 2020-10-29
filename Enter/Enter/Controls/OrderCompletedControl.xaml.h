//
// OrderCompletedControl.xaml.h
// Объявление класса OrderCompletedControl
//

#pragma once

#include "Controls\OrderCompletedControl.g.h"

namespace Enter
{
	namespace Controls
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class OrderCompletedControl sealed
		{
		public:
			OrderCompletedControl();
		private:
			void OnClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		};
	}
}
