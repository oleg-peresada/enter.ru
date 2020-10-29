#include "pch.h"
#include "TrackerViewModels.h"

using namespace Enter;
using namespace Enter::DataModel::Storage;
using namespace Enter::View;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Navigation;

TrackerViewModels::TrackerViewModels(Page^ page)
: ViewModelsBase(page), m_size(0)
{
}

void TrackerViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	LoadedTask(false);
}

void TrackerViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
}

void TrackerViewModels::LoadedTask(bool isCached)
{
	Helpers::LogPage("MainPageView/TrackerView");

	this->OnActiveState(true);
	auto token = AutorizationStorage::Current->Token;
	auto trackerCommand = ref new TrackerCommands(token, -1);
	auto command = trackerCommand->TrackerOrderAsync(isCached);
	concurrency::create_task(command).then([this, token](IVector<TrackerOrderModels^>^ trackerValue)
	{
		this->TrackerVector = trackerValue;
		this->Size = trackerValue->Size;

		this->OnActiveState(false);

	}).then(TaskException<void>());
}

void TrackerViewModels::OnItemClick(Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e)
{
	auto trackerItem = dynamic_cast<TrackerOrderModels^>(e->ClickedItem);
	if (trackerItem != nullptr)
	{
		this->ViewFrame->Navigate(TrackerExtensionsView::typeid, trackerItem);
	}
}

IVector<TrackerOrderModels^>^ TrackerViewModels::TrackerVector::get()
{
	return m_TrackerVector;
}

void TrackerViewModels::TrackerVector::set(IVector<TrackerOrderModels^>^ value)
{
	m_TrackerVector = value;
	OnPropertyChanged("TrackerVector");
}

unsigned int TrackerViewModels::Size::get()
{
	return m_size;
}

void TrackerViewModels::Size::set(unsigned int value)
{
	m_size = value;
	OnPropertyChanged("Size");
}

RelayCommand^ TrackerViewModels::RefreshCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		LoadedTask(true);
	}, [this](Object^)
	{
		return true;
	});
}