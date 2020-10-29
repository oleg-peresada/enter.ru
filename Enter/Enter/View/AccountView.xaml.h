//
// AccountView.xaml.h
// Объявление класса AccountView
//

#pragma once

#include "View\AccountView.g.h"
#include "ViewModels\AccountViewModels.h"

namespace Enter
{
	namespace View
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class AccountView sealed
		{
		public:
			AccountView();
		private:
			Enter::ViewModels::AccountViewModels^ accountView;
		protected:
			virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
			virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		};
	}
}
