//
// ChangedPasswordControl.xaml.h
// Объявление класса ChangedPasswordControl
//

#pragma once

#include "Controls\ChangedPasswordControl.g.h"
#include "DataModel\Storage\AutorizationStorage.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace Controls
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ChangedPasswordControl sealed
		{
		public:
			ChangedPasswordControl();
		private:
			void ChangedClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
			void VisualStateOldTransitions(bool isTransition);
			void VisualStateNewTransitions(bool isTransition);
			void VisualStateError(bool isTransition, String^ message = "Ошибка изменения пароля.");
		};
	}
}
