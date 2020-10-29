//
// TrackerView.xaml.cpp
// Реализация класса TrackerView
//

#include "pch.h"
#include "TrackerView.xaml.h"

using namespace Enter;
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

TrackerView::TrackerView()
{
	InitializeComponent();

	this->m_orderHistory = ref new Enter::ViewModels::TrackerViewModels(this);
	this->DataContext = m_orderHistory;
}

void TrackerView::OnNavigatedTo(NavigationEventArgs^ e)
{
	m_orderHistory->OnNavigatedTo(e);
}

void TrackerView::OnNavigatedFrom(NavigationEventArgs^ e)
{
	m_orderHistory->OnNavigatedFrom(e);
	m_orderHistory = nullptr;
}

void TrackerView::OnItemClick(Object^ sender, ItemClickEventArgs^ e)
{
	m_orderHistory->OnItemClick(sender, e);
}