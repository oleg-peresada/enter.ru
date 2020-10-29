//
// CategoryTreeView.xaml.cpp
// Реализация класса CategoryTreeView
//

#include "pch.h"
#include "CategoryTreeView.xaml.h"

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

CategoryTreeView::CategoryTreeView()
{
	InitializeComponent();

	this->categoryView = ref new CategoryTreeViewModels(this);
	this->DataContext = categoryView;
}

void CategoryTreeView::OnNavigatedTo(NavigationEventArgs^ e)
{
	categoryView->OnNavigatedTo(e);
}

void CategoryTreeView::OnNavigatedFrom(NavigationEventArgs^ e)
{
	categoryView->OnNavigatedFrom(e);
	categoryView = nullptr;
}

void CategoryTreeView::OnVariableCategoryClick(Object^ sender, ItemClickEventArgs^ e)
{
	if (e->ClickedItem != nullptr)
	{
		categoryView->VariableCategoryItemClick(e->ClickedItem);
	}
}

void CategoryTreeView::OnQuerySubmitted(SearchBox^ sender, SearchBoxQuerySubmittedEventArgs^ args)
{
	categoryView->SearchSubmitted(sender, args);
}

void CategoryTreeView::OnResultSuggestionChosen(SearchBox^ sender, SearchBoxResultSuggestionChosenEventArgs^ args)
{
	categoryView->SearchSuggestionChosen(sender, args);
}

void CategoryTreeView::OnSuggestionsRequested(SearchBox^ sender, SearchBoxSuggestionsRequestedEventArgs^ args)
{
	categoryView->SearchRequest(sender, args);
}