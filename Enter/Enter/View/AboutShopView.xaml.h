//
// AboutShopView.xaml.h
// Объявление класса AboutShopView
//

#pragma once

#include "View\AboutShopView.g.h"
#include "ViewModels\AboutShopViewModels.h"

namespace Enter
{
	namespace View
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class AboutShopView sealed
		{
		public:
			AboutShopView();
		private:
			Enter::ViewModels::AboutShopViewModels^ aboutShopView;
		protected:
			virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
			virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		};
	}
}
