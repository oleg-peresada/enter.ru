//
// CitiesMenuControl.xaml.cpp
// Реализация класса CitiesMenuControl
//

#include "pch.h"
#include "CitiesMenuControl.xaml.h"

using namespace Enter;
using namespace Enter::Controls;
using namespace Enter::DataModel::Storage;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

CitiesMenuControl::CitiesMenuControl()
{
	InitializeComponent();
}

void CitiesMenuControl::OnSaveClick(Object^ sender, RoutedEventArgs^ e)
{
	auto popup = dynamic_cast<Popup^>(this->Parent);
	if (popup != nullptr)
	{
		auto item = dynamic_cast<CitiesModels^>(listCities->SelectedItem);
		if (item != nullptr)
		{
			auto cityStorage = ref new CityTokenStorage(item->Id, item->ParentId, item->Name);
			cityStorage->Save();
			OnCityInfo(item->Name);

			popup->IsOpen = false;
		}
	}
}

void CitiesMenuControl::OnCityInfo(String^ name)
{
	CityInfo(this, name);
}

void CitiesMenuControl::OnQuerySubmitted(SearchBox^ sender, SearchBoxQuerySubmittedEventArgs^ args)
{
	if (args == nullptr && args->QueryText == nullptr) return;

	if (ContentCity.size() > 0)
	{
		for (const auto &item : ContentCity)
		{
			if (item->Name == args->QueryText)
			{
				auto cityStorage = ref new CityTokenStorage(item->Id, item->Region->Id, item->Name);
				cityStorage->Save();
				OnCityInfo(item->Name);

				auto popup = dynamic_cast<Popup^>(this->Parent);
				if (popup != nullptr)
				{
					popup->IsOpen = false;
				}
			}
		}
	}
}

void CitiesMenuControl::OnResultSuggestionChosen(SearchBox^ sender, SearchBoxResultSuggestionChosenEventArgs^ args)
{
}

void CitiesMenuControl::OnSuggestionsRequested(SearchBox^ sender, SearchBoxSuggestionsRequestedEventArgs^ args)
{
	if ((args == nullptr && args->QueryText == nullptr) && args->QueryText->Length() < 2) return;

	auto requestSearch = args->Request;
	auto defferal = requestSearch->GetDeferral();

	auto commandCity = ref new CitiesCommands();
	auto commandOperator = commandCity->AutoCompleteCities(args->QueryText);

	concurrency::create_task(commandOperator).then([=](IObservableVector<AutoCityModels^>^ vectCity)
	{
		if (vectCity != nullptr && vectCity->Size > 0)
		{
			ContentCity = to_vector<AutoCityModels^>(vectCity);
			auto requestCollection = requestSearch->SearchSuggestionCollection;
			requestCollection->AppendSearchSeparator("Результаты поиска");

			unsigned int size = vectCity->Size;
			for (unsigned int index = 0; index < size; index++)
			{
				requestCollection->AppendQuerySuggestion(vectCity->GetAt(index)->Name);
			}

			Finally f([&]
			{
				defferal->Complete();
			});
		}
	}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
}