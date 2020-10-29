//
// MainPage.xaml.cpp
// Реализация класса MainPage.
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Enter;
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

MainPage::MainPage()
{
	InitializeComponent();

	this->mainView = ref new MainViewModels(this);
	this->DataContext = mainView;
}

void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	mainView->OnNavigatedTo(e);
}

void MainPage::OnNavigatedFrom(NavigationEventArgs^ e)
{
	mainView->OnNavigatedFrom(e);
	mainView = nullptr;
}

void MainPage::OnHubItemClick(Object^ sender, ItemClickEventArgs^ e)
{
	mainView->OnMainHubClick(e->ClickedItem);
}

void MainPage::OnItemCategoryClick(Object^ sender, ItemClickEventArgs^ e)
{
	mainView->OnCategoryHubClick(e->ClickedItem);
}

void MainPage::OnSearchRequested(SearchBox^ sender, SearchBoxSuggestionsRequestedEventArgs^ args)
{
	mainView->SearchRequest(sender, args);
}

void MainPage::OnSearchSubmitted(SearchBox^ sender, SearchBoxQuerySubmittedEventArgs^ args)
{
	mainView->SearchSubmitted(sender, args);
}

void MainPage::OnResultSuggestionChosen(SearchBox^ sender, SearchBoxResultSuggestionChosenEventArgs^ args)
{
	mainView->SearchSuggestionChosen(sender, args);
}