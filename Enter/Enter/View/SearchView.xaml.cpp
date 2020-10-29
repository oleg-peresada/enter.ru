//
// SearchView.xaml.cpp
// Реализация класса SearchView
//

#include "pch.h"
#include "SearchView.xaml.h"

using namespace Enter;
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

SearchView::SearchView()
{
	InitializeComponent();

	searchView = ref new SearchViewModels(this);
	this->DataContext = searchView;
}

void SearchView::OnNavigatedTo(NavigationEventArgs^ e)
{
	searchView->OnNavigatedTo(e);
}

void SearchView::OnNavigatedFrom(NavigationEventArgs^ e)
{
	searchView->OnNavigatedFrom(e);
	searchView = nullptr;
}

void SearchView::OnItemClickProduct(Object^ sender, ItemClickEventArgs^ e)
{
	if (e->ClickedItem != nullptr)
	{
		searchView->OnItemProductClick(e->ClickedItem);
	}
}

void SearchView::OnSuggestionsRequested(SearchBox^ sender, SearchBoxSuggestionsRequestedEventArgs^ args)
{
	searchView->SearchRequest(sender, args);
}

void SearchView::OnQuerySubmitted(SearchBox^ sender, SearchBoxQuerySubmittedEventArgs^ args)
{
	searchView->OnSearchQuerySubmittedView(sender, args);
}

void SearchView::OnResultSuggestionChosen(SearchBox^ sender, SearchBoxResultSuggestionChosenEventArgs^ args)
{
	searchView->SearchSuggestionChosen(sender, args);
}