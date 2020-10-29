#include "pch.h"
#include "ProductExtensionsPhotoViewModels.h"

using namespace Enter;
using namespace Enter::ViewModels;
using namespace EnterStore::Models;
using namespace EnterStore::Commands;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

ProductExtensionsPhotoViewModels::ProductExtensionsPhotoViewModels(Page^ page)
	: ViewModelsBase(page)
{
}

void ProductExtensionsPhotoViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	Helpers::LogPage("MainPageView/ProductExtensionsCardView");
	auto product = dynamic_cast<ProductExtensionsCardModels^>(args->Parameter);
	if (product != nullptr)
	{
		CardProduct = product;
	}
}

void ProductExtensionsPhotoViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
}

ProductExtensionsCardModels^ ProductExtensionsPhotoViewModels::CardProduct::get()
{
	return source_cardModel;
}

void ProductExtensionsPhotoViewModels::CardProduct::set(ProductExtensionsCardModels^ val)
{
	source_cardModel = val;
	OnPropertyChanged("CardProduct");
}