#include "pch.h"
#include "MainViewModels.h"

using namespace Enter;
using namespace Enter::DataModel;
using namespace Enter::DataModel::Storage;
using namespace Enter::ViewModels;
using namespace Enter::View;
using namespace Enter::Controls;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Media::Animation;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Background;

MainViewModels::MainViewModels(Page^ page)
: ViewModelsBase(page), GeoId(0), m_contentPanel(Visibility::Collapsed), m_progressPanel(Visibility::Collapsed)
{
}

MainViewModels::~MainViewModels()
{
	if (popupCities != nullptr)
	{
		popupCities->Closed -= popupCloseCityToken;
	}
}

void MainViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	Helpers::LogPage("MainPageView");
	GeoId = CityTokenStorage::Current->Id != 0 ? CityTokenStorage::Current->Id : 14974;
	if (!IsBackgroundTask("EnterOnlineTask"))
	{
		auto requestBackground = BackgroundExecutionManager::RequestAccessAsync();
		concurrency::create_task(requestBackground).then([this, args](BackgroundAccessStatus status)
		{
			if (status != BackgroundAccessStatus::Unspecified)
			{
				auto taskBuilder = ref new BackgroundTaskBuilder();
				taskBuilder->Name = "EnterOnlineTask";
				taskBuilder->TaskEntryPoint = "EnterTask.EnterTaskBackground";
				taskBuilder->SetTrigger(ref new TimeTrigger(15, false));
				auto registerTask = taskBuilder->Register();

				TaskLoaded(args->Parameter, false);
			}
		}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
	}
	else
	{
		TaskLoaded(args->Parameter, false);
	}
}

void MainViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
}

concurrency::task<void> MainViewModels::TaskLoaded(Object^ parameter, bool isCached)
{
	ProgressOrContent(true);
	auto promoCommand = ref new PromoBannerCommands(GeoId, BannerType::Standart);
	auto operationPromo = promoCommand->PromoBannerAsync(isCached);

	return concurrency::create_task(operationPromo).then([this, parameter, isCached](IVector<PromoBannerModels^>^ valueModel)
	{
		PromoBanner = valueModel;

		if (!CityTokenStorage::Current->IsCityToken)
		{
			this->OnCitiesPopupFlyout(parameter);
		}

		auto catCommand = ref new CategoryTreeCommands(0, 1, GeoId, false);
		auto catOper = catCommand->CategoryTreeCommandAsync(isCached);
		return concurrency::create_task(catOper).then([this](IVector<CategoryTreeModels^>^ vect)
		{
			CategoryCollection = vect;
			ProgressOrContent(false);

		}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
	}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
}

void MainViewModels::OnMainHubClick(Object^ parameter)
{
	auto hub = dynamic_cast<HubDataModel^>(parameter);
	if (hub != nullptr)
	{
		if (hub->Name == "Магазины")
		{
			ViewFrame->Navigate(AboutShopView::typeid);
		}
		else if (hub->Name == "Мой кабинет")
		{
			ViewFrame->Navigate(AccountView::typeid);
		}
		else if (hub->Name == "Корзина")
		{
			ViewFrame->Navigate(BasketView::typeid);
		}
	}
}

void MainViewModels::OnCategoryHubClick(Object^ parameter)
{
	ViewFrame->Navigate(CategoryTreeView::typeid, parameter);
}

void MainViewModels::OnCitiesPopupFlyout(Object^ parameter)
{
	if (parameter == nullptr) return;

	auto rectWindow = Window::Current->Bounds;
	auto width = rectWindow.Width;
	auto height = rectWindow.Height;

	auto citiesControl = ref new CitiesMenuControl();
	citiesControl->Width = width;
	citiesControl->Height = height;
	citiesControl->Tag = height * 0.90;
	citiesControl->DataContext = parameter;

	popupCities = ref new Popup();

	windowActivatedToken = Window::Current->Activated += 
		ref new Windows::UI::Xaml::WindowActivatedEventHandler(this, &MainViewModels::OnWindowsActivated);
	popupCloseCityToken = popupCities->Closed += ref new Windows::Foundation::EventHandler<Platform::Object ^>(this, &MainViewModels::OnClosedPopup);

	popupCities->ChildTransitions = ref new TransitionCollection();
	popupCities->ChildTransitions->Append(ref new PopupThemeTransition());
	popupCities->Child = citiesControl;
	popupCities->IsLightDismissEnabled = false;
	popupCities->IsOpen = true;
}

void MainViewModels::OnClosedPopup(Object ^sender, Object ^args)
{
	Window::Current->Activated -= windowActivatedToken;
}

void MainViewModels::OnWindowsActivated(Object ^sender, Windows::UI::Core::WindowActivatedEventArgs ^e)
{
	if (e->WindowActivationState == Windows::UI::Core::CoreWindowActivationState::Deactivated)
	{
		if (popupCities != nullptr)
		{
			popupCities->IsOpen = false;
		}
	}
}

bool MainViewModels::IsBackgroundTask(String^ nameTask)
{
	auto taskAll = BackgroundTaskRegistration::AllTasks;
	for (const auto &item : taskAll)
	{
		if (item->Value->Name == nameTask)
		{
			return true;
		}
	}

	return false;
}

void MainViewModels::ProgressOrContent(bool state)
{
	if (state)
	{
		ProgressPanel = Visibility::Visible;
		ContentPanel = Visibility::Collapsed;
	}
	else
	{
		ProgressPanel = Visibility::Collapsed;
		ContentPanel = Visibility::Visible;
	}
}

IObservableVector<HubDataModel^>^ MainViewModels::MainHubDataModel::get()
{
	auto vect = ref new Vector<HubDataModel^>();
	vect->Append(ref new HubDataModel("Мой кабинет", nullptr));
	vect->Append(ref new HubDataModel("Магазины", nullptr));
	vect->Append(ref new HubDataModel("Корзина", nullptr));

	OnPropertyChanged("MainHubDataModel");
	return vect;
}

IVector<CategoryTreeModels^>^ MainViewModels::CategoryCollection::get()
{
	return m_CategoryCollection;
}

void MainViewModels::CategoryCollection::set(IVector<CategoryTreeModels^>^ value)
{
	m_CategoryCollection = value;
	OnPropertyChanged("CategoryCollection");
}

IVector<PromoBannerModels^>^ MainViewModels::PromoBanner::get()
{
	return source_promoBanner;
}

void MainViewModels::PromoBanner::set(IVector<PromoBannerModels^>^ value)
{
	source_promoBanner = value;
	OnPropertyChanged("PromoBanner");
}

Visibility MainViewModels::ProgressPanel::get()
{
	return m_progressPanel;
}

void MainViewModels::ProgressPanel::set(Visibility value)
{
	m_progressPanel = value;
	OnPropertyChanged("ProgressPanel");
}

Visibility MainViewModels::ContentPanel::get()
{
	return m_contentPanel;
}

void MainViewModels::ContentPanel::set(Visibility value)
{
	m_contentPanel = value;
	OnPropertyChanged("ContentPanel");
}

RelayCommand^ MainViewModels::BasketCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		ViewFrame->Navigate(BasketView::typeid);
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ MainViewModels::PromoCommand::get()
{
	return ref new RelayCommand([this](Object^ parameter)
	{
		auto element = dynamic_cast<PromoBannerModels^>(parameter);
		if (element != nullptr)
		{
			if (element->Url != nullptr)
			{
				auto options = ref new Windows::System::LauncherOptions();
				options->DesiredRemainingView = Windows::UI::ViewManagement::ViewSizePreference::UseMinimum;
				Windows::System::Launcher::LaunchUriAsync(ref new Uri(element->Url), options);
			}
			else if (element->PromoItems != nullptr)
			{
				if (element->PromoItems->Size == 0) return;

				auto items = element->PromoItems;
				auto first = items->GetAt(0);

				if (first->TypeId == 1)
				{
					if (items->Size == 1)
					{
						ViewFrame->Navigate(ProductExtensionsView::typeid, first->Id);
					}
					else
					{
						ViewFrame->Navigate(AccessoriesView::typeid, element);
					}
				}
				else if (first->TypeId == 3)
				{
					ViewFrame->Navigate(ProductView::typeid, element);
				}
			}
		}
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ MainViewModels::RefreshCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		this->TaskLoaded(nullptr, true);
	}, [this](Object^)
	{
		return true;
	});
}