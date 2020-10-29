//
// BasketView.xaml.h
// Объявление класса BasketView
//

#pragma once

#include "View\BasketView.g.h"
#include "ViewModels\BasketViewModels.h"

namespace Enter
{
	namespace View
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class BasketView sealed
		{
		public:
			BasketView();
		private:
			Enter::ViewModels::BasketViewModels^ basketView;
			void OnSelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
			void OnItemClickView(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
		protected:
			virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
			virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		};
	}
}
