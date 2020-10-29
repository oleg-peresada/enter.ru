//
// AutorizationFlyout.xaml.h
// Declaration of the AutorizationFlyout class
//

#pragma once

#include <ctype.h>

#include "Helpers.h"
#include "View\Settings\AutorizationFlyout.g.h"
#include "View\AccountView.xaml.h"
#include "DataModel\Storage\AutorizationStorage.h"

using namespace Platform;

namespace Enter
{
	namespace View
	{
		namespace Settings
		{
			[Windows::Foundation::Metadata::WebHostHidden]
			public ref class AutorizationFlyout sealed
			{
			public:
				AutorizationFlyout();
			private:
				void IsGoVisualState(bool stateTransition);
				void IsError(bool state);
				void OnClickRegistration(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
				void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
				void OnNoClickRegistration(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
				void OnPasswordRecovery(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
			};
		}
	}
}
