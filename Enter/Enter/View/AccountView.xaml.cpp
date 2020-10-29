//
// AccountView.xaml.cpp
// Реализация класса AccountView
//

#include "pch.h"
#include "AccountView.xaml.h"

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

AccountView::AccountView()
{
	InitializeComponent();

	accountView = ref new AccountViewModels(this);
	this->DataContext = accountView;
}

void AccountView::OnNavigatedTo(NavigationEventArgs^ e)
{
	accountView->OnNavigatedTo(e);
}

void AccountView::OnNavigatedFrom(NavigationEventArgs^ e)
{
	accountView->OnNavigatedFrom(e);
	accountView = nullptr;
}