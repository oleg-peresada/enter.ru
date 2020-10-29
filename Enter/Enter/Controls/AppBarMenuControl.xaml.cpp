//
// AppBarMenuControl.xaml.cpp
// Реализация класса AppBarMenuControl
//

#include "pch.h"
#include "AppBarMenuControl.xaml.h"

using namespace Enter;
using namespace Enter::Controls;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

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

AppBarMenuControl::AppBarMenuControl()
{
	InitializeComponent();
}


void AppBarMenuControl::OnLoaded(Object^ sender, RoutedEventArgs^ e)
{
	auto catCommand = ref new CategoryTreeCommands(0, 1, 14974, false);
	auto catOper = catCommand->CategoryTreeCommandAsync();

	concurrency::create_task(catOper).then([this](IVector<CategoryTreeModels^>^ vect)
	{
		gridViewCategory->ItemsSource = vect;
	});
}


void AppBarMenuControl::OnItemClickCategory(Object^ sender, ItemClickEventArgs^ e)
{
	auto currentFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Window::Current->Content);
	if (currentFrame != nullptr)
	{
		currentFrame->Navigate(Enter::View::CategoryTreeView::typeid, e->ClickedItem);
	}
}


void AppBarMenuControl::OnHomeClick(Object^ sender, RoutedEventArgs^ e)
{
	auto currentFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Window::Current->Content);
	if (currentFrame != nullptr)
	{
		while (currentFrame->CanGoBack)
		{
			currentFrame->GoBack();
		}
	}
}


void AppBarMenuControl::OnBasketClick(Object^ sender, RoutedEventArgs^ e)
{
	auto currentFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Window::Current->Content);
	if (currentFrame != nullptr && currentFrame->CurrentSourcePageType.Name != TypeName(Enter::View::BasketView::typeid).Name)
	{
		currentFrame->Navigate(Enter::View::BasketView::typeid);
	}
}
