//
// TrackerView.xaml.cpp
// Реализация класса TrackerView
//

#pragma once

#include "View\TrackerView.g.h"
#include "ViewModels\TrackerViewModels.h"

namespace Enter
{
	namespace View
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class TrackerView sealed
		{
		public:
			TrackerView();
		private:
			Enter::ViewModels::TrackerViewModels^ m_orderHistory;
			void OnItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
		protected:
			virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
			virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		};
	}
}
