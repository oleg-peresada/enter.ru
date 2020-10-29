//
// ProductExtensionsPhotoView.xaml.cpp
// Реализация класса ProductExtensionsPhotoView
//

#include "pch.h"
#include "ProductExtensionsPhotoView.xaml.h"

using namespace Enter;
using namespace Enter::View;
using namespace Enter::ViewModels;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

ProductExtensionsPhotoView::ProductExtensionsPhotoView()
{
	InitializeComponent();

	this->productPhotoView = ref new ProductExtensionsPhotoViewModels(this);
	this->DataContext = productPhotoView;
}

void ProductExtensionsPhotoView::OnNavigatedTo(NavigationEventArgs^ e)
{
	productPhotoView->OnNavigatedTo(e);
}

void ProductExtensionsPhotoView::OnNavigatedFrom(NavigationEventArgs^ e)
{
	productPhotoView->OnNavigatedFrom(e);
	productPhotoView = nullptr;
}
