#include "pch.h"
#include "ProductViewModels.h"

using namespace Enter;
using namespace Enter::ViewModels;
using namespace Enter::View;
using namespace Enter::DataModel;
using namespace Enter::DataModel::Storage;
using namespace EnterStore::Models;
using namespace EnterStore::Commands;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Media::Animation;

IncrementFilterLoading^ incLoading = nullptr;
int currentRegionId = 0;
int currentCategoryId = 0;
bool _progressIncrement = true;

ProductViewModels::ProductViewModels(Page^ page) : ViewModelsBase(page)
{
}

ProductViewModels::~ProductViewModels()
{
	if (popupFilter != nullptr)
	{
		popupFilter->Closed -= source_popupFilterCloseToken;
	}

	if (filterControl != nullptr)
	{
		filterControl->SplashFilterChanged -= splashFilterToken;
	}

	if (incLoading != nullptr)
	{
		incLoading->IncrementLoadingProgress -= _incrementLoadingToken;
	}
}

void ProductViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	Helpers::LogPage("MainPageView/ProductView");
	this->OnActiveState(true);

	if (state->PageState != nullptr)
	{
		HorizontalOffset = (double)state->PageState->Lookup("productHorizaontalOffset");
	}
	
	auto customization = Customizations::Current;
	String^ productTemplate = customization->ResourceProductTemplate != nullptr 
		? customization->ResourceProductTemplate 
		: "TableTemplate";

	auto resourceTemplate = dynamic_cast<DataTemplate^>(ViewPage->Resources->Lookup(productTemplate));
	if (resourceTemplate != nullptr)
	{
		ViewTemplate = resourceTemplate;
	}

	auto modelTree = dynamic_cast<CategoryTreeModels^>(args->Parameter);
	if (modelTree != nullptr)
	{
		OnIncrementFilter(modelTree->Id, modelTree->Name);
		return;
	}

	auto promo = dynamic_cast<PromoBannerModels^>(args->Parameter);
	if (promo != nullptr)
	{
		OnIncrementFilter(promo->PromoItems->GetAt(0)->Id, promo->Name != nullptr ? promo->Name : "...");
		return;
	}
}

void ProductViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
	state->PageState->Insert("productHorizaontalOffset", HorizontalOffset);

	if (ProductCollection != nullptr) ProductCollection = nullptr;
}

void ProductViewModels::OnIncrementFilter(int id, String^ header)
{
	Header = header;
	if (currentCategoryId != id)
	{
		_progressIncrement = true;
		currentRegionId = CityTokenStorage::Current->Id != 0 ? CityTokenStorage::Current->Id : 14974;
		currentCategoryId = id;

		incLoading = ref new IncrementFilterLoading(currentRegionId, currentCategoryId, 20, 0);
		_incrementLoadingToken = incLoading->IncrementLoadingProgress += ref new IncrementLoadingProgressHandler(this, &ProductViewModels::OnIncrementLoadingProgress);
		FilterProductIncrement = incLoading;
	}
	else
	{
		FilterProductIncrement = incLoading;
		_incrementLoadingToken = incLoading->IncrementLoadingProgress += ref new IncrementLoadingProgressHandler(this, &ProductViewModels::OnIncrementLoadingProgress);
	}
}

void ProductViewModels::OnProductItemClick(Object^ parameter)
{
	ViewFrame->Navigate(ProductExtensionsView::typeid, parameter);
}

void ProductViewModels::OnFilterPopup()
{
	auto rectWindow = Window::Current->Bounds;
	auto width = rectWindow.Width;
	auto height = rectWindow.Height;

	filterControl = ref new SplashFilterView();
	splashFilterToken = filterControl->SplashFilterChanged += ref new SplashFilterChangedHandler(this, &ProductViewModels::OnSplashFilterChanged);
	filterControl->CategoryId = currentCategoryId;
	filterControl->RegionId = currentRegionId;
	filterControl->Width = width;
	filterControl->Height = height / 1.2;

	popupFilter = ref new Popup();
	source_WindowFilterActivateToken = Window::Current->Activated += ref new WindowActivatedEventHandler(this, &ProductViewModels::OnFilterActivated);
	source_popupFilterCloseToken = popupFilter->Closed += ref new EventHandler<Object ^>(this, &ProductViewModels::OnFilterClosed);

	popupFilter->ChildTransitions = ref new TransitionCollection();
	auto transition = ref new Windows::UI::Xaml::Media::Animation::EdgeUIThemeTransition();
	transition->Edge = EdgeTransitionLocation::Top;
	popupFilter->ChildTransitions->Append(transition);
	popupFilter->Child = filterControl;
	popupFilter->IsLightDismissEnabled = true;
	popupFilter->IsOpen = true;

	BottomIsOpen = false;
	BottomIsSticky = false;
}

void ProductViewModels::OnSplashFilterChanged(Object ^sender, SplashFilterChangedEventArgs ^args)
{
	if (incLoading != nullptr)
	{
		incLoading->IncrementLoadingProgress -= _incrementLoadingToken;

		incLoading->Clear();
		incLoading = nullptr;
	}

	_progressIncrement = true;
	incLoading = ref new IncrementFilterLoading(currentRegionId, currentCategoryId, 20, 0);
	_incrementLoadingToken = incLoading->IncrementLoadingProgress += ref new IncrementLoadingProgressHandler(this, &ProductViewModels::OnIncrementLoadingProgress);
	incLoading->Filters = args->NewValue;
	incLoading->SortParameter = args->NewSort;
	this->FilterProductIncrement = incLoading;
}

void ProductViewModels::OnIncrementLoadingProgress(Object ^sender, bool isProgress)
{
	bool progress = _progressIncrement;
	Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal,
		ref new Windows::UI::Core::DispatchedHandler([this, isProgress, progress]()
	{
		if (progress)
		{
			this->OnActiveState(true);
			_progressIncrement = false;
		}
		else
		{
			this->OnActiveState(false);
		}
	}));
}

void ProductViewModels::OnFilterClosed(Object ^sender, Object ^args)
{
	Window::Current->Activated -= source_WindowFilterActivateToken;

	BottomIsOpen = true;
	BottomIsSticky = false;
}

void ProductViewModels::OnFilterActivated(Object ^sender, Windows::UI::Core::WindowActivatedEventArgs ^e)
{
	if (e->WindowActivationState == Windows::UI::Core::CoreWindowActivationState::Deactivated)
	{
		if (popupFilter != nullptr)
		{
			popupFilter->IsOpen = false;
		}
	}
}

String^ ProductViewModels::Header::get()
{
	return source_header;
}

void ProductViewModels::Header::set(String^ val)
{
	source_header = val;
	OnPropertyChanged("Header");
}

IObservableVector<ProductCardModels^>^ ProductViewModels::ProductCollection::get()
{
	return source_productCollection;
}

void ProductViewModels::ProductCollection::set(IObservableVector<ProductCardModels^>^ val)
{
	source_productCollection = val;
	OnPropertyChanged("ProductCollection");
}

IncrementFilterLoading^ ProductViewModels::FilterProductIncrement::get()
{
	return source_FilterProductIncrement;
}

void ProductViewModels::FilterProductIncrement::set(IncrementFilterLoading^ val)
{
	source_FilterProductIncrement = val;
	OnActiveState(false);
	OnPropertyChanged("FilterProductIncrement");
}

bool ProductViewModels::BottomIsOpen::get()
{
	return source_bottomIsOpen;
}

void ProductViewModels::BottomIsOpen::set(bool value)
{
	source_bottomIsOpen = value;
	OnPropertyChanged("BottomIsOpen");
}

bool ProductViewModels::BottomIsSticky::get()
{
	return source_bottomIsSticky;
}

void ProductViewModels::BottomIsSticky::set(bool value)
{
	source_bottomIsSticky = value;
	OnPropertyChanged("BottomIsSticky");
}

DataTemplate^ ProductViewModels::ViewTemplate::get()
{
	return source_viewTemplate;
}

void ProductViewModels::ViewTemplate::set(DataTemplate^ value)
{
	source_viewTemplate = value;
	OnPropertyChanged("ViewTemplate");
}

double ProductViewModels::HorizontalOffset::get()
{
	return m_horizontalOffset;
}

void ProductViewModels::HorizontalOffset::set(double value)
{
	m_horizontalOffset = value;
	OnPropertyChanged("HorizontalOffset");
}

RelayCommand^ ProductViewModels::FilterCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		this->OnFilterPopup();
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ ProductViewModels::TableViewCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		auto resourceTemplate = dynamic_cast<DataTemplate^>(ViewPage->Resources->Lookup("TableTemplate"));
		if (resourceTemplate != nullptr)
		{
			ViewTemplate = resourceTemplate;

			auto custom = ref new Customizations();
			custom->ResourceProductTemplate = "TableTemplate";
			custom->Save();
		}
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ ProductViewModels::SketchCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		auto resourceTemplate = dynamic_cast<DataTemplate^>(ViewPage->Resources->Lookup("SketchTemplate"));
		if (resourceTemplate != nullptr)
		{
			ViewTemplate = resourceTemplate;

			auto custom = ref new Customizations();
			custom->ResourceProductTemplate = "SketchTemplate";
			custom->Save();
		}
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ ProductViewModels::BasketCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		ViewFrame->Navigate(BasketView::typeid);
	}, [this](Object^)
	{
		return true;
	});
}