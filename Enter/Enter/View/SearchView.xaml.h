﻿//
// SearchView.xaml.h
// Объявление класса SearchView
//

#pragma once

#include "View\SearchView.g.h"
#include "ViewModels\SearchViewModels.h"

namespace Enter
{
	namespace View
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class SearchView sealed
		{
		public:
			SearchView();
		private:
			Enter::ViewModels::SearchViewModels^ searchView;
			void OnItemClickProduct(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
			void OnSuggestionsRequested(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxSuggestionsRequestedEventArgs^ args);
			void OnQuerySubmitted(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxQuerySubmittedEventArgs^ args);
			void OnResultSuggestionChosen(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxResultSuggestionChosenEventArgs^ args);
		protected:
			virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
			virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		};
	}
}
