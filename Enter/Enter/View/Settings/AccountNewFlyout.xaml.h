//
// AccountNewFlyout.xaml.h
// Declaration of the AccountNewFlyout class
//

#pragma once

#include "Helpers.h"
#include "DataModel\Storage\AutorizationStorage.h"
#include "View\Settings\AccountNewFlyout.g.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace View
	{
		namespace Settings
		{
			[Windows::Foundation::Metadata::WebHostHidden]
			public ref class AccountNewFlyout sealed
			{
			public:
				AccountNewFlyout();
			private:
				void OnGoStateVisual(bool stateTransition);
				void OnRegistration(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
				void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
				void OnRecoveryClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
			};
		}
	}
}
