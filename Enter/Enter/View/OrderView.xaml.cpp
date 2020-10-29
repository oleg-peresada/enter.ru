//
// OrderView.xaml.cpp
// Реализация класса OrderView
//

#include "pch.h"
#include "OrderView.xaml.h"

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

OrderView::OrderView()
{
	InitializeComponent();

	orderView = ref new OrderViewModels(this);
	this->DataContext = orderView;
}

void OrderView::OnNavigatedTo(NavigationEventArgs^ e)
{
	orderView->OnNavigatedTo(e);
}

void OrderView::OnNavigatedFrom(NavigationEventArgs^ e)
{
	orderView->OnNavigatedFrom(e);
	orderView = nullptr;
}