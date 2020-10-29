//
// MainPage.xaml.h
// Объявление класса MainPage.
//

#pragma once

#include "MainPage.g.h"
#include "ViewModels\MainViewModels.h"

namespace Enter
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class MainPage sealed
	{
	public:
		MainPage();
	private:
		Enter::ViewModels::MainViewModels^ mainView;
		void OnHubItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
		void OnItemCategoryClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
		void OnSearchRequested(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxSuggestionsRequestedEventArgs^ args);
		void OnSearchSubmitted(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxQuerySubmittedEventArgs^ args);
		void OnResultSuggestionChosen(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxResultSuggestionChosenEventArgs^ args);
	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	};
}
