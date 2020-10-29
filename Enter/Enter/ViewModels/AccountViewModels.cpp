#include "pch.h"
#include "AccountViewModels.h"
#include "View\TrackerView.xaml.h"

using namespace Enter;
using namespace Enter::View;
using namespace Enter::ViewModels;
using namespace Enter::View::Settings;
using namespace Enter::Controls;
using namespace Enter::DataModel;
using namespace Enter::DataModel::Storage;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Media::Animation;

AccountViewModels::AccountViewModels(Page^ page)
	: ViewModelsBase(page)
{
}

AccountViewModels::~AccountViewModels()
{
	if (regionPopup != nullptr)
	{
		regionPopup->Closed -= _regionCloseToken;
	}
}

void AccountViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	Helpers::LogPage("MainPageView/AccountView");
	tokenStorage = AutorizationStorage::Current->Token;
	if (CityTokenStorage::Current->IsCityToken)
	{
		RegionText = CityTokenStorage::Current->Name;
	}
}

void AccountViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
}

void AccountViewModels::OnAutorization()
{
	auto autorization = ref new AutorizationFlyout();
	autorization->Width = 500;
	autorization->ShowIndependent();
}

void AccountViewModels::OnRegistration()
{
	auto registration = ref new AccountNewFlyout();
	registration->Width = 500;
	registration->ShowIndependent();
}

void AccountViewModels::PersonalOrderData()
{
	tokenStorage = AutorizationStorage::Current->Token;
	if (tokenStorage == nullptr)
	{
		this->OnAutorization();
		return;
	}

	ViewFrame->Navigate(TrackerView::typeid);
}

void AccountViewModels::PersonalDataChanged()
{
	tokenStorage = AutorizationStorage::Current->Token;
	if (tokenStorage == nullptr)
	{
		this->OnAutorization();
		return;
	}

	auto userCommand = ref new UserContentCommands(tokenStorage);
	auto operationComamnd = userCommand->CurrentUserAsync();

	concurrency::create_task(operationComamnd).then([&](UserContentModels^ contentValue)
	{
		auto rectWindow = Window::Current->Bounds;
		auto width = 650;
		auto height = rectWindow.Height;

		auto personalData = ref new PersonalDataChangedControl();
		personalData->Width = width;
		personalData->Height = height;
		personalData->Tag = contentValue;

		auto popupPersonal = ref new Popup();
		popupPersonal->ChildTransitions = ref new TransitionCollection();
		auto transition = ref new EdgeUIThemeTransition();
		transition->Edge = EdgeTransitionLocation::Left;
		popupPersonal->ChildTransitions->Append(transition);
		popupPersonal->Child = personalData;
		popupPersonal->IsLightDismissEnabled = true;
		popupPersonal->IsOpen = true;

	}).then(TaskException<void>());
}

void AccountViewModels::RegionChanged()
{
	auto promoCommand = ref new CitiesCommands();
	auto operationPromo = promoCommand->MenuCitiesAsync();
	concurrency::create_task(operationPromo).then([this](IObservableVector<CitiesModels^>^ valueModel)
	{
		auto rectWindow = Window::Current->Bounds;
		auto width = rectWindow.Width - 200;
		auto height = rectWindow.Height - 100;

		auto citiesControl = ref new CitiesMenuControl();
		citiesControl->Width = width;
		citiesControl->Height = height;
		citiesControl->Margin = Thickness(100, 50, 100, 50);
		citiesControl->DataContext = valueModel;

		regionPopup = ref new Popup();
		_regionActivateToken = Window::Current->Activated += ref new WindowActivatedEventHandler(this, &AccountViewModels::OnActivatedRegion);
		_regionCloseToken = regionPopup->Closed += ref new EventHandler<Platform::Object ^>(this, &AccountViewModels::OnClosedRegion);

		regionPopup->ChildTransitions = ref new TransitionCollection();
		regionPopup->ChildTransitions->Append(ref new PopupThemeTransition());
		regionPopup->Child = citiesControl;
		regionPopup->IsLightDismissEnabled = true;
		regionPopup->IsOpen = true;

	}).then(TaskException<void>());
}

void AccountViewModels::OnActivatedRegion(Object ^sender, Windows::UI::Core::WindowActivatedEventArgs ^e)
{
	if (e->WindowActivationState == Windows::UI::Core::CoreWindowActivationState::Deactivated)
	{
		if (regionPopup != nullptr)
		{
			regionPopup->IsOpen = false;
		}
	}
}

void AccountViewModels::OnClosedRegion(Object ^sender, Object ^args)
{
	RegionText = CityTokenStorage::Current->Name;
	Window::Current->Activated -= _regionActivateToken;
}

String^ AccountViewModels::ResetEmail::get()
{
	return source_resetEmail;
}

void AccountViewModels::ResetEmail::set(String^ val)
{
	source_resetEmail = val;
	OnPropertyChanged("ResetEmail");
}

String^ AccountViewModels::ResetPhone::get()
{
	return source_resetPhone;
}

void AccountViewModels::ResetPhone::set(String^ val)
{
	source_resetPhone = val;
	OnPropertyChanged("ResetPhone");
}

String^ AccountViewModels::MessageReset::get()
{
	return source_messageReset;
}

void AccountViewModels::MessageReset::set(String^ val)
{
	source_messageReset = val;
	OnPropertyChanged("MessageReset");
}

String^ AccountViewModels::RegionText::get()
{
	return source_regionText;
}

void AccountViewModels::RegionText::set(String^ value)
{
	source_regionText = value;
	OnPropertyChanged("RegionText");
}

RelayCommand^ AccountViewModels::ResetPasswordCommand::get()
{
	return ref new RelayCommand([this](Object^ obj)
	{
		AuthType autorizationType = AuthType::Email;
		String^ parameter = nullptr;
		auto a = ResetEmail;
		if (ResetEmail != nullptr)
		{
			autorizationType = AuthType::Email;
			parameter = ResetEmail;
		}

		if (ResetPhone != nullptr)
		{
			autorizationType = AuthType::Mobile;
			parameter = ResetPhone;
		}

		if (parameter == nullptr) return;

		auto commandReset = ref new ResetPasswordUserCommands(parameter, autorizationType);
		auto operationHttp = commandReset->ResetPasswordAsync();
		concurrency::create_task(operationHttp).then([&](bool confirmed)
		{
			if (confirmed)
			{
				MessageReset = "Вам успешно отправлено сообщение на телефон или email для восстановления пароля.";
			}
			else
			{
				MessageReset = "Ошибка при восстановлении пароля.";
			}

		}).then(TaskException<void>());

	}, [this](Object^ obj)
	{
		return true;
	});
}

RelayCommand^ AccountViewModels::AutorizationCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		this->OnAutorization();
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ AccountViewModels::RegistrationCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		this->OnRegistration();
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ AccountViewModels::ChangedPersonalDataCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		this->PersonalDataChanged();
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ AccountViewModels::PersonalOrderCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		this->PersonalOrderData();
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ AccountViewModels::RegionChangedCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		this->RegionChanged();
	}, [this](Object^)
	{
		return true;
	});
}