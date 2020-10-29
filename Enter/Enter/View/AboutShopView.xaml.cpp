//
// AboutShopView.xaml.cpp
// Реализация класса AboutShopView
//

#include "pch.h"
#include "AboutShopView.xaml.h"

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

AboutShopView::AboutShopView()
{
	InitializeComponent();

	aboutShopView = ref new AboutShopViewModels(this);
	this->DataContext = aboutShopView;
}

void AboutShopView::OnNavigatedTo(NavigationEventArgs^ e)
{
	aboutShopView->OnNavigatedTo(e);
}

void AboutShopView::OnNavigatedFrom(NavigationEventArgs^ e)
{
	aboutShopView->OnNavigatedFrom(e);
	aboutShopView = nullptr;
}