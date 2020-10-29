//
// ChangedPasswordControl.xaml.cpp
// Реализация класса ChangedPasswordControl
//

#include "pch.h"
#include "ChangedPasswordControl.xaml.h"

using namespace Enter;
using namespace Enter::Controls;
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

ChangedPasswordControl::ChangedPasswordControl()
{
	InitializeComponent();
}

void ChangedPasswordControl::VisualStateOldTransitions(bool isTransition)
{
	if (isTransition)
	{
		VisualStateManager::GoToState(this, "PositiveOld", isTransition);
	}
	else
	{
		VisualStateManager::GoToState(this, "NegativeOld", isTransition);
	}
}

void ChangedPasswordControl::VisualStateNewTransitions(bool isTransition)
{
	if (isTransition)
	{
		VisualStateManager::GoToState(this, "PositiveNew", isTransition);
	}
	else
	{
		VisualStateManager::GoToState(this, "NegativeNew", isTransition);
	}
}

void ChangedPasswordControl::VisualStateError(bool isTransition, String^ message)
{
	ErrorText->Text = message;
	if (!isTransition)
	{
		VisualStateManager::GoToState(this, "PositiveError", isTransition);
	}
	else
	{
		VisualStateManager::GoToState(this, "NegativeError", isTransition);
	}
}

void ChangedPasswordControl::ChangedClick(Object^ sender, RoutedEventArgs^ e)
{
	auto token = Enter::DataModel::Storage::AutorizationStorage::Current->Token;
	if (token == nullptr)
	{
		this->VisualStateError(true, "Авторизуйтесь для изменения пароля.");
		return;
	}

	bool isPassword = false;
	if (text_old->Password == nullptr)
	{
		this->VisualStateOldTransitions(false);
		isPassword = true;
	}
	else
	{
		this->VisualStateOldTransitions(true);
	}

	if (text_new->Password == nullptr)
	{
		this->VisualStateNewTransitions(false);
		isPassword = true;
	}
	else
	{
		this->VisualStateNewTransitions(true);
	}

	if (isPassword) return;

	auto changeCommand = ref new ChangePasswordUserCommands(token, text_old->Password, text_new->Password);
	auto operationCommand = changeCommand->ChangePasswordAsync();

	concurrency::create_task(operationCommand).then([this](bool confirmed)
	{
		if (!confirmed) this->VisualStateError(true);

		if (confirmed)
		{
			this->VisualStateError(false);
			auto popup = dynamic_cast<Popup^>(this->Parent);
			if (popup != nullptr)
			{
				popup->IsOpen = false;
			}
		}
	}).then(TaskException<void>());
}