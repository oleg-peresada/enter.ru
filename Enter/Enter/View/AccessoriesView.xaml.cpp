//
// AccessoriesView.xaml.cpp
// Реализация класса AccessoriesView
//

#include "pch.h"
#include "AccessoriesView.xaml.h"

using namespace Enter;
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

AccessoriesView::AccessoriesView()
{
	InitializeComponent();

	accessoriesView = ref new AccessoriesViewModels(this);
	this->DataContext = accessoriesView;
}

void AccessoriesView::OnNavigatedTo(NavigationEventArgs^ e)
{
	accessoriesView->OnNavigatedTo(e);
}

void AccessoriesView::OnNavigatedFrom(NavigationEventArgs^ e)
{
	accessoriesView->OnNavigatedFrom(e);
	accessoriesView = nullptr;
}

void AccessoriesView::OnItemClick(Object^ sender, ItemClickEventArgs^ e)
{
	accessoriesView->OnItemClick(sender, e);
}