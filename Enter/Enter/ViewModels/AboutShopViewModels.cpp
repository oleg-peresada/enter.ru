#include "pch.h"
#include "AboutShopViewModels.h"

using namespace Enter;
using namespace Enter::ViewModels;
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
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Media::Animation;

AboutShopViewModels::AboutShopViewModels(Page^ page)
	: ViewModelsBase(page)
{
}

AboutShopViewModels::~AboutShopViewModels()
{
	if (popupShop != nullptr)
	{
		popupShop->Closed -= popupShopToken;
	}
}

void AboutShopViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	Helpers::LogPage("MainPageView/AboutShopView");
	LoadedTask(false);
}

void AboutShopViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
}

void AboutShopViewModels::LoadedTask(bool isCached)
{
	OnActiveState(true);
	Rect windowRect = Window::Current->Bounds;
	WidthAbout = windowRect.Width * 0.8;

	auto shopCommand = ref new ShopListCommands(ShopListType::None, nullptr);
	concurrency::create_task(shopCommand->ToShopCommandAsync(isCached)).then([&](IVector<ShopListModels^>^ shopVect)
	{
		ShopCollection = shopVect;
		int id = Customizations::Current->CurrentStore;
		if (id == -1)
		{
			OnElementShop(shopVect->GetAt(0));
			OnActiveState(false);
			return;
		}
		else
		{
			for (const auto &item : ShopCollection)
			{
				if (id == item->Id)
				{
					OnElementShop(item);
					OnActiveState(false);
					return;
				}
			}

			OnElementShop(shopVect->GetAt(0));
			OnActiveState(false);
		}
	}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
}

void AboutShopViewModels::OnElementShop(ShopListModels^ element)
{
	Shop = element;
	CountImages = element->Images->Size;
}

void AboutShopViewModels::OnTappedImage()
{
	auto rectWindow = Window::Current->Bounds;
	auto width = (rectWindow.Width * 0.80);
	auto height = (rectWindow.Height * 0.75);

	auto imageViewControl = ref new ImageShopControl();
	imageViewControl->Width = width;
	imageViewControl->Height = height;

	double w_margin = (rectWindow.Width - width) / 2;
	double h_margin = (rectWindow.Height - height) / 2;

	imageViewControl->Margin = Thickness(w_margin, h_margin, w_margin, h_margin);
	imageViewControl->Tag = Shop;

	auto popup = ref new Popup();
	popup->ChildTransitions = ref new TransitionCollection();
	popup->ChildTransitions->Append(ref new PopupThemeTransition());
	popup->Child = imageViewControl;
	popup->IsLightDismissEnabled = true;
	popup->IsOpen = true;
}

void AboutShopViewModels::OnShopPopup()
{
	auto rectWindow = Window::Current->Bounds;

	auto width = rectWindow.Width;
	auto height = rectWindow.Height;

	shopControlMenu = ref new ShopMenuControl();

	eventTappedCity = shopControlMenu->TappedCity += ref new TappedCityHandler(this, &AboutShopViewModels::OnTappedCityPopup);
	windowActivatedToken = Window::Current->Activated += ref new WindowActivatedEventHandler(this, &AboutShopViewModels::OnWindowsActivated);

	shopControlMenu->Width = width;
	shopControlMenu->Height = height;

	auto groupShop = ref new ShopGroupDataModel();
	shopControlMenu->Tag = groupShop->ToViewShop(ShopCollection);

	popupShop = ref new Popup();
	popupShopToken = popupShop->Closed += ref new EventHandler<Object ^>(this, &AboutShopViewModels::OnClosePopupCity);

	popupShop->ChildTransitions = ref new TransitionCollection();
	popupShop->ChildTransitions->Append(ref new PopupThemeTransition());
	popupShop->Child = shopControlMenu;
	popupShop->IsLightDismissEnabled = false;
	popupShop->IsOpen = true;
}

void AboutShopViewModels::OnClosePopupCity(Object ^sender, Object ^args)
{
	if (shopControlMenu != nullptr)
	{
		shopControlMenu->TappedCity -= eventTappedCity;
		Window::Current->Activated -= windowActivatedToken;
	}
}

void AboutShopViewModels::OnWindowsActivated(Object ^sender, Windows::UI::Core::WindowActivatedEventArgs ^e)
{
	if (e->WindowActivationState == Windows::UI::Core::CoreWindowActivationState::Deactivated)
	{
		if (popupShop != nullptr)
		{
			popupShop->IsOpen = false;
		}
	}
}

void AboutShopViewModels::OnTappedCityPopup(Object ^sender, CityResultEventArgs ^args)
{
	OnElementShop(args->Item);
	auto settings = ref new Customizations();
	settings->CurrentStore = args->Item->Id;
	settings->Save();
}

IVector<ShopListModels^>^ AboutShopViewModels::ShopCollection::get()
{
	return about_shopCollection;
}

void AboutShopViewModels::ShopCollection::set(IVector<ShopListModels^>^ val)
{
	about_shopCollection = val;
	OnPropertyChanged("ShopCollection");
}

unsigned int AboutShopViewModels::CountImages::get()
{
	return about_countImages;
}

void AboutShopViewModels::CountImages::set(unsigned int val)
{
	about_countImages = val;
	OnPropertyChanged("CountImages");
}

ShopListModels^ AboutShopViewModels::Shop::get()
{
	return about_Shop;
}

void AboutShopViewModels::Shop::set(ShopListModels^ val)
{
	about_Shop = val;
	OnPropertyChanged("Shop");
}

double AboutShopViewModels::WidthAbout::get()
{
	return m_widthAbout;
}

void AboutShopViewModels::WidthAbout::set(double value)
{
	m_widthAbout = value;
	OnPropertyChanged("WidthAbout");
}

RelayCommand^ AboutShopViewModels::ImageCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		this->OnTappedImage();
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ AboutShopViewModels::MoreShopCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		this->OnShopPopup();
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ AboutShopViewModels::RefreshCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		LoadedTask(true);
	}, [this](Object^)
	{
		return true;
	});
}