//
// OrderView.xaml.h
// Объявление класса OrderView
//

#pragma once

#include "View\OrderView.g.h"
#include "ViewModels\OrderViewModels.h"

namespace Enter
{
	namespace View
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class OrderView sealed
		{
		public:
			OrderView();
		private:
			Enter::ViewModels::OrderViewModels^ orderView;
		protected:
			virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
			virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		};
	}
}
