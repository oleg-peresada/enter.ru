//
// PersonalDataChangedControl.xaml.h
// Объявление класса PersonalDataChangedControl
//

#pragma once

#include <string>
#include <sstream>

#include "Controls\PersonalDataChangedControl.g.h"
#include "DataModel\Storage\AutorizationStorage.h"

namespace Enter
{
	namespace Controls
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PersonalDataChangedControl sealed
		{
		public:
			PersonalDataChangedControl();
		private:
			Windows::Foundation::EventRegistrationToken tokenLoaded;

			Windows::Foundation::DateTime ParseTime(Platform::String^ time);
			void OnUpdateElement(EnterStore::Models::UserContentModels^ data);
			void OnLoaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
			void OnUnloaded(Platform::Object ^sender, Windows::UI::Xaml::RoutedEventArgs ^e);
			void OnSaveClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
			void OnStateSaveTransition(bool isTransitions);
		};
	}
}
