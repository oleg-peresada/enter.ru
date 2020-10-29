//
// BasketView.xaml.cpp
// Реализация класса BasketView
//

#include "pch.h"
#include "BasketView.xaml.h"

using namespace Enter::ViewModels;
using namespace Enter::View;

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

BasketView::BasketView()
{
	InitializeComponent();

	basketView = ref new BasketViewModels(this);
	this->DataContext = basketView;
}

void BasketView::OnNavigatedTo(NavigationEventArgs^ e)
{
	basketView->OnNavigatedTo(e);
}

void BasketView::OnNavigatedFrom(NavigationEventArgs^ e)
{
	basketView->OnNavigatedFrom(e);
	basketView = nullptr;
}

void BasketView::OnSelectionChanged(Object^ sender, SelectionChangedEventArgs^ e)
{
	basketView->OnSelectionProduct(sender, e);
}


void BasketView::OnItemClickView(Object^ sender, ItemClickEventArgs^ e)
{
	basketView->OnItemClickView(e->ClickedItem);
}
