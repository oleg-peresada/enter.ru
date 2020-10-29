//
// ShopMenuControl.xaml.cpp
// Реализация класса ShopMenuControl
//

#include "pch.h"
#include "ShopMenuControl.xaml.h"

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

CityResultEventArgs::CityResultEventArgs()
{
}

CityResultEventArgs::CityResultEventArgs(EnterStore::Models::ShopListModels^ item)
	: source_Shop(item)
{
}

EnterStore::Models::ShopListModels^ CityResultEventArgs::Item::get()
{
	return source_Shop;
}

ShopMenuControl::ShopMenuControl()
{
	InitializeComponent();
}

void ShopMenuControl::OnSaveClick(Object^ sender, RoutedEventArgs^ e)
{
	auto popup = dynamic_cast<Popup^>(this->Parent);
	if (popup != nullptr)
	{
		if (gridView->SelectedItem != nullptr)
		{
			TappedCity(this, ref new CityResultEventArgs(safe_cast<EnterStore::Models::ShopListModels^>(gridView->SelectedItem)));
			popup->IsOpen = false;
		}
	}
}

void ShopMenuControl::OnCloseClick(Object^ sender, RoutedEventArgs^ e)
{
	auto popup = dynamic_cast<Popup^>(this->Parent);
	if (popup != nullptr)
	{
		popup->IsOpen = false;
	}
}