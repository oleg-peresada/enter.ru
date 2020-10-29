#include "pch.h"
#include "AccessoriesViewModels.h"

using namespace Enter;
using namespace Enter::View;
using namespace Enter::ViewModels;
using namespace Enter::DataModel::Storage;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

AccessoriesViewModels::AccessoriesViewModels(Page^ page) : ViewModelsBase(page)
{
}

void AccessoriesViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	Helpers::LogPage("MainPageView/AccessoriesView");

	if (state->PageState != nullptr)
	{
		HorizontalOffset = safe_cast<double>(state->PageState->Lookup("accessoriesViewHorizontalOffset"));
	}

	m_parameter = args->Parameter;
	LoadedTask(args->Parameter, false);
}

void AccessoriesViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
	state->PageState->Insert("accessoriesViewHorizontalOffset", HorizontalOffset);
}

void AccessoriesViewModels::LoadedTask(Object^ parameter, bool isCached)
{
	OnActiveState(true);

	auto element = dynamic_cast<ProductExtensionsCardModels^>(parameter);
	if (element != nullptr)
	{
		Header = "Аксессуары";
		ProductsLoaded(element->Accessories, isCached);
		return;
	}

	auto promo = dynamic_cast<PromoBannerModels^>(parameter);
	if (promo != nullptr)
	{
		auto vect = ref new Vector<int>();
		unsigned int size = promo->PromoItems->Size;
		for (unsigned int index = 0; index < size; index++)
		{
			vect->Append(promo->PromoItems->GetAt(index)->Id);
		}

		Header = promo->Name;
		ProductsLoaded(vect, isCached);
		return;
	}
}

concurrency::task<void> AccessoriesViewModels::ProductsLoaded(IVector<int>^ products, bool isCached)
{
	int geo_id = CityTokenStorage::Current->Id != 0 ? CityTokenStorage::Current->Id : 14974;
	auto commandProduct = ref new ProductCommands(products, geo_id);
	return concurrency::create_task(commandProduct->ProductsAsync(isCached)).then([this](IObservableVector<ProductCardModels^>^ vectProduct) -> void
	{
		ProductCards = vectProduct;
		OnActiveState(false);
	}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
}

void AccessoriesViewModels::OnItemClick(Object^ sender, ItemClickEventArgs^ e)
{
	if (e->ClickedItem != nullptr)
	{
		ViewFrame->Navigate(ProductExtensionsView::typeid, e->ClickedItem);
	}
}

IObservableVector<ProductCardModels^>^ AccessoriesViewModels::ProductCards::get()
{
	return m_productCards;
}

void AccessoriesViewModels::ProductCards::set(IObservableVector<ProductCardModels^>^ value)
{
	m_productCards = value;
	OnPropertyChanged("ProductCards");
}

String^ AccessoriesViewModels::Header::get()
{
	return m_header;
}

void AccessoriesViewModels::Header::set(String^ value)
{
	m_header = value;
	OnPropertyChanged("Header");
}

double AccessoriesViewModels::HorizontalOffset::get()
{
	return m_horizontalOffset;
}

void AccessoriesViewModels::HorizontalOffset::set(double value)
{
	m_horizontalOffset = value;
	OnPropertyChanged("HorizontalOffset");
}

RelayCommand^ AccessoriesViewModels::RefreshCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		if (m_parameter == nullptr) return;

		LoadedTask(m_parameter, true);
	}, [this](Object^)
	{
		return true;
	});
}