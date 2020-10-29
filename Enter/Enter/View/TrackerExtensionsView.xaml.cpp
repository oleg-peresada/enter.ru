//
// TrackerExtensionsView.xaml.cpp
// Реализация класса TrackerExtensionsView
//

#include "pch.h"
#include "TrackerExtensionsView.xaml.h"

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

TrackerExtensionsView::TrackerExtensionsView()
{
	InitializeComponent();

	m_trackerView = ref new TrackerExtensionsViewModels(this);
	this->DataContext = m_trackerView;
}

void TrackerExtensionsView::OnNavigatedTo(NavigationEventArgs^ e)
{
	m_trackerView->OnNavigatedTo(e);
}

void TrackerExtensionsView::OnNavigatedFrom(NavigationEventArgs^ e)
{
	m_trackerView->OnNavigatedFrom(e);
	m_trackerView = nullptr;
}

void TrackerExtensionsView::OnProductItemClick(Object^ sender, ItemClickEventArgs^ e)
{
	m_trackerView->OnProductItemClick(sender, e);
}