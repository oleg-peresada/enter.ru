//
// TrackerExtensionsView.xaml.h
// Объявление класса TrackerExtensionsView
//

#pragma once

#include "View\TrackerExtensionsView.g.h"
#include "ViewModels\TrackerExtensionsViewModels.h"

namespace Enter
{
	namespace View
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class TrackerExtensionsView sealed
		{
		public:
			TrackerExtensionsView();
		private:
			Enter::ViewModels::TrackerExtensionsViewModels^ m_trackerView;
			void OnProductItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
		protected:
			virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
			virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		};
	}
}
