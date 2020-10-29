//
// ProductExtensionsPhotoView.xaml.h
// Объявление класса ProductExtensionsPhotoView
//

#pragma once

#include "View\ProductExtensionsPhotoView.g.h"
#include "ViewModels\ProductExtensionsPhotoViewModels.h"

namespace Enter
{
	namespace View
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductExtensionsPhotoView sealed
		{
		public:
			ProductExtensionsPhotoView();
		private:
			Enter::ViewModels::ProductExtensionsPhotoViewModels^ productPhotoView;
		protected:
			virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
			virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		};
	}
}
