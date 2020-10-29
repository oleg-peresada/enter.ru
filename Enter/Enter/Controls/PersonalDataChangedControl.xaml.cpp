//
// PersonalDataChangedControl.xaml.cpp
// Реализация класса PersonalDataChangedControl
//

#include "pch.h"
#include "PersonalDataChangedControl.xaml.h"

using namespace Enter;
using namespace Enter::Controls;
using namespace EnterStore::Models;
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

PersonalDataChangedControl::PersonalDataChangedControl()
{
	InitializeComponent();

	tokenLoaded = this->Loaded += ref new RoutedEventHandler(this, &PersonalDataChangedControl::OnLoaded);
	this->Unloaded += ref new RoutedEventHandler(this, &PersonalDataChangedControl::OnUnloaded);
}

DateTime PersonalDataChangedControl::ParseTime(String^ time)
{
	std::string strDate(begin(time), end(time));
	std::istringstream dateStream(strDate);

	auto calendar = ref new Windows::Globalization::Calendar();

	int year = 0;
	dateStream >> year;
	calendar->Year = year;
	dateStream.ignore(1, '-');

	int month = 0;
	dateStream >> month;
	calendar->Month = month;
	dateStream.ignore(1, '-');

	int day = 0;
	dateStream >> day;
	calendar->Day = day;

	return calendar->GetDateTime();
}

void PersonalDataChangedControl::OnUpdateElement(EnterStore::Models::UserContentModels^ data)
{
	if (data->Email != nullptr) textEmail->Text = data->Email;
	if (data->FirstName != nullptr) textFirstName->Text = data->FirstName;
	if (data->LastName != nullptr) textLastName->Text = data->LastName;
	if (data->MiddleName != nullptr) textMiddleName->Text = data->MiddleName;
	if (data->MobilePhone != nullptr) textMobilePhone->Text = data->MobilePhone;
	if (data->Occupation != nullptr) textOccupation->Text = data->Occupation;
	if (data->Phone != nullptr) textPhone->Text = data->Phone;
	if (data->Skype != nullptr) textSkype->Text = data->Skype;
	if (data->Sex != nullptr) comboSex->SelectedItem = data->Sex;

	if (data->Birtday != nullptr)
		date->Date = ParseTime(data->Birtday);
}

void PersonalDataChangedControl::OnLoaded(Object^ sender, RoutedEventArgs^ e)
{
	auto vect = ref new Vector<String^>();
	vect->Append("0");
	vect->Append("1");
	vect->Append("2");

	comboSex->ItemsSource = vect;

	auto tag = dynamic_cast<EnterStore::Models::UserContentModels^>(this->Tag);
	if (tag != nullptr)
	{
		this->OnUpdateElement(tag);
	}
}

void PersonalDataChangedControl::OnUnloaded(Object ^sender, RoutedEventArgs ^e)
{
	this->Loaded -= tokenLoaded;
}

void PersonalDataChangedControl::OnStateSaveTransition(bool isTransitions)
{
	if (isTransitions)
	{
		VisualStateManager::GoToState(this, "SaveSuccess", isTransitions);
	}
	else
	{
		VisualStateManager::GoToState(this, "SaveError", isTransitions);
	}
}

void PersonalDataChangedControl::OnSaveClick(Object^ sender, RoutedEventArgs^ e)
{
	auto calendar = ref new Windows::Globalization::Calendar();
	calendar->SetDateTime(date->Date);
	
	String^ customDate = calendar->Year + "-" + calendar->Month + "-" + calendar->Day;

	auto personalData = ref new PersonalDataUpdateModels(textFirstName->Text != nullptr ? textFirstName->Text : "",
		textLastName->Text != nullptr ? textLastName->Text : "",
		textMiddleName->Text != nullptr ? textMiddleName->Text : "",
		comboSex->SelectedItem == nullptr ? "0" : safe_cast<String^>(comboSex->SelectedItem),
		textOccupation->Text != nullptr ? textOccupation->Text : "",
		textEmail->Text != nullptr ? textEmail->Text : "",
		textPhone->Text != nullptr ? textPhone->Text : "",
		textMobilePhone->Text != nullptr ? textMobilePhone->Text : "",
		customDate,
		textSkype->Text != nullptr ? textSkype->Text : "");

	auto commandUpdate = ref new PersonalDataUpdateCommands(Enter::DataModel::Storage::AutorizationStorage::Current->Token);
	auto operation = commandUpdate->UpdateAsync(personalData);

	concurrency::create_task(operation).then([this](bool confirmed)
	{
		this->OnStateSaveTransition(confirmed);
	});
}