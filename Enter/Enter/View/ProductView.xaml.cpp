//
// ProductView.xaml.cpp
// Реализация класса ProductView
//

#include "pch.h"
#include "ProductView.xaml.h"

using namespace Enter::View;
using namespace Enter::ViewModels;

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

ProductView::ProductView()
{
	InitializeComponent();

	productView = ref new ProductViewModels(this);
	this->DataContext = productView;
}

void ProductView::OnNavigatedTo(NavigationEventArgs^ e)
{
	productView->OnNavigatedTo(e);
}

void ProductView::OnNavigatedFrom(NavigationEventArgs^ e)
{
	productView->OnNavigatedFrom(e);
	productView = nullptr;
}

void ProductView::OnItemProductClick(Object^ sender, ItemClickEventArgs^ e)
{
	if (e->ClickedItem != nullptr)
	{
		productView->OnProductItemClick(e->ClickedItem);
	}
}

void ProductView::OnSuggestionsRequested(SearchBox^ sender, SearchBoxSuggestionsRequestedEventArgs^ args)
{
	productView->SearchRequest(sender, args);
}

void ProductView::OnQuerySubmitted(SearchBox^ sender, SearchBoxQuerySubmittedEventArgs^ args)
{
	productView->SearchSubmitted(sender, args);
}

void ProductView::OnResultSuggestionChosen(SearchBox^ sender, SearchBoxResultSuggestionChosenEventArgs^ args)
{
	productView->SearchSuggestionChosen(sender, args);
}