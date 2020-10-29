//
// OrderCompletedControl.xaml.cpp
// Реализация класса OrderCompletedControl
//

#include "pch.h"
#include "OrderCompletedControl.xaml.h"

using namespace Enter;
using namespace Enter::Controls;

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

OrderCompletedControl::OrderCompletedControl()
{
	InitializeComponent();
}


void OrderCompletedControl::OnClick(Object^ sender, RoutedEventArgs^ e)
{
	auto popup = dynamic_cast<Popup^>(this->Parent);
	if (popup != nullptr)
	{
		popup->IsOpen = false;
	}
}
