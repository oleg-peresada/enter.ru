//
// AccountNewFlyout.xaml.cpp
// Реализация класса AccountNewFlyout
//

#include "pch.h"
#include "AccountNewFlyout.xaml.h"

using namespace Enter;
using namespace Enter::View::Settings;
using namespace Enter::DataModel::Storage;
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
using namespace Windows::UI::Popups;

AccountNewFlyout::AccountNewFlyout()
{
	InitializeComponent();
}

void AccountNewFlyout::OnGoStateVisual(bool stateTransition)
{
	if (stateTransition)
	{
		registerGrid->Visibility = Windows::UI::Xaml::Visibility::Visible;
		notRegisterGrid->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
	}
	else
	{
		registerGrid->Visibility = Windows::UI::Xaml::Visibility::Collapsed;
		notRegisterGrid->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}

void AccountNewFlyout::OnRegistration(Object^ sender, RoutedEventArgs^ e)
{
	Windows::UI::Popups::MessageDialog^ message = nullptr;
	if (firstNameBox->Text == nullptr)
	{
		message = ref new Windows::UI::Popups::MessageDialog("Укажите имя");
		message->ShowAsync();
		return;
	}

	if (emailAndPhone->Text == nullptr)
	{
		message = ref new Windows::UI::Popups::MessageDialog("Укажите e-mail или телефон");
		message->ShowAsync();
		return;
	}

	if (passwordBox->Password == nullptr && passwordBox->Password->Length() < 4)
	{
		message = ref new Windows::UI::Popups::MessageDialog("Укажите пароль.\nПароль должен быть не меньше 5 символов.");
		message->ShowAsync();
		return;
	}

	AuthType valueType = AuthType::Email;
	if (Helpers::IsNumberToString(emailAndPhone->Text))
	{
		valueType = AuthType::Mobile;
	}
	else
	{
		valueType = AuthType::Email;
	}

	auto userCreateCommand = ref new UserCreateCommands(14974, valueType, 
		emailAndPhone->Text, firstNameBox->Text, 
		lastNameBox->Text, passwordBox->Password);
	auto operation = userCreateCommand->UserCreateAsync();
	concurrency::create_task(operation).then([this](UserCreateModels^ userContent)
	{
		if (userContent != nullptr)
		{
			AutorizationStorage::Current->Token = userContent->Token;
			this->OnGoStateVisual(false);
		}
		else
		{
			this->OnGoStateVisual(true);
		}
	});
}


void AccountNewFlyout::OnLoaded(Object^ sender, RoutedEventArgs^ e)
{
	auto token = AutorizationStorage::Current->Token;
	if (token == nullptr)
	{
		OnGoStateVisual(true);
	}
	else
	{
		OnGoStateVisual(false);
	}
}


void AccountNewFlyout::OnRecoveryClick(Object^ sender, RoutedEventArgs^ e)
{
	AutorizationStorage::Current->Token = nullptr;
	OnGoStateVisual(true);
}
