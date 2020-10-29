//
// ProductExtensionsView.xaml.cpp
// Реализация класса ProductExtensionsView
//

#include "pch.h"
#include "ProductExtensionsView.xaml.h"

using namespace Enter::View;
using namespace Enter::ViewModels;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

ProductExtensionsView::ProductExtensionsView()
{
	InitializeComponent();

	productExtensionsView = ref new ProductExtensionsViewModels(this);
	this->DataContext = productExtensionsView;
}

void ProductExtensionsView::OnNavigatedTo(NavigationEventArgs^ e)
{
	auto vect = ref new Vector<Object^>();
	unsigned int size = rootHub->SectionHeaders->Size;
	for (unsigned int index = 0; index < size; index++)
	{
		Object^ element = rootHub->SectionHeaders->GetAt(index);
		if (element != nullptr && element->ToString()->Length() > 1)
		{
			vect->Append(element);
		}
	}

	viewSourceHubSection->Source = vect;

	productExtensionsView->OnNavigatedTo(e);
}

void ProductExtensionsView::OnNavigatedFrom(NavigationEventArgs^ e)
{
	productExtensionsView->OnNavigatedFrom(e);
	productExtensionsView = nullptr;
}

void ProductExtensionsView::OnHubSectionHeaderClick(Object^ sender, HubSectionHeaderClickEventArgs^ e)
{
	productExtensionsView->OnHubSectionHeader(e->Section->Header);
}

void ProductExtensionsView::OnSuggestionsRequested(SearchBox^ sender, SearchBoxSuggestionsRequestedEventArgs^ args)
{
	productExtensionsView->SearchRequest(sender, args);
}

void ProductExtensionsView::OnQuerySubmitted(SearchBox^ sender, SearchBoxQuerySubmittedEventArgs^ args)
{
	productExtensionsView->SearchSubmitted(sender, args);
}

void ProductExtensionsView::OnResultSuggestionChosen(SearchBox^ sender, SearchBoxResultSuggestionChosenEventArgs^ args)
{
	productExtensionsView->SearchSuggestionChosen(sender, args);
}

void ProductExtensionsView::OnOptionSelectionChanged(Object^ sender, SelectionChangedEventArgs^ e)
{
	productExtensionsView->OnOptionSelectedChanged(sender, e);
}

void ProductExtensionsView::OnPropertySelectionChanged(Object^ sender, SelectionChangedEventArgs^ e)
{
	productExtensionsView->OnPropertyChangedSelected(sender, e);
}