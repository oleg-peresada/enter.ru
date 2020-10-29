//
// AutorizationFlyout.xaml.cpp
// Реализация класса AutorizationFlyout
//

#include "pch.h"
#include "AutorizationFlyout.xaml.h"

using namespace Enter;
using namespace Enter::View::Settings;
using namespace Enter::DataModel::Storage;

using namespace EnterStore::Commands;

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
using namespace Windows::UI::Popups;

AutorizationFlyout::AutorizationFlyout()
{
	InitializeComponent();
}

void AutorizationFlyout::IsGoVisualState(bool stateTransition)
{
	if (stateTransition)
	{
		RootGrid->Visibility = Windows::UI::Xaml::Visibility::Visible;
		InnerGrid->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
	else
	{
		RootGrid->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		InnerGrid->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}

void AutorizationFlyout::IsError(bool state)
{
	if (!state)
	{
		ErrorInnerGrid->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
	else
	{
		ErrorInnerGrid->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}

void AutorizationFlyout::OnClickRegistration(Object^ sender, RoutedEventArgs^ e)
{
	Windows::UI::Popups::MessageDialog^ message = nullptr;
	if (emailAndmobile->Text == nullptr)
	{
		message = ref new Windows::UI::Popups::MessageDialog("Введите телефон или email для продолжения");
		message->ShowAsync();
		return;
	}

	if (password->Password == nullptr)
	{
		message = ref new Windows::UI::Popups::MessageDialog("Введите пароль");
		message->ShowAsync();
		return;
	}

	AuthType value_auth = AuthType::Email;
	if (Helpers::IsNumberToString(emailAndmobile->Text))
	{
		value_auth = AuthType::Mobile;
	}
	else
	{
		value_auth = AuthType::Email;
	}

	auto operationCommand = ref new AutorizationCommands(emailAndmobile->Text, value_auth, password->Password);
	concurrency::create_task(operationCommand->AutorizationToResultTokenAsync()).then([this](String^ contentToken)
	{
		if (contentToken != nullptr)
		{
			AutorizationStorage::Current->CreateSaveToken(contentToken);
			this->IsGoVisualState(false);	
		}
		else
		{
			IsError(true);
		}
	});
}


void AutorizationFlyout::OnLoaded(Object^ sender, RoutedEventArgs^ e)
{
	auto token = AutorizationStorage::Current->Token;
	if (token == nullptr)
	{
		IsGoVisualState(true);
	}
	else
	{
		IsGoVisualState(false);
	}
}


void AutorizationFlyout::OnNoClickRegistration(Object^ sender, RoutedEventArgs^ e)
{
	AutorizationStorage::Current->Token = nullptr;
	IsGoVisualState(true);
}

void AutorizationFlyout::OnPasswordRecovery(Object^ sender, RoutedEventArgs^ e)
{
	Frame^ currentFrame = dynamic_cast<Frame^>(Window::Current->Content);
	if (currentFrame != nullptr)
	{
		this->Hide();
		currentFrame->Navigate(Enter::View::AccountView::typeid);
	}
}
