//
// CategoryTreeView.xaml.h
// Объявление класса CategoryTreeView
//

#pragma once

#include "View\CategoryTreeView.g.h"
#include "ViewModels\CategoryTreeViewModels.h"

namespace Enter
{
	namespace View
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class CategoryTreeView sealed
		{
		public:
			CategoryTreeView();
		private:
			Enter::ViewModels::CategoryTreeViewModels^ categoryView;
			void OnVariableCategoryClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
			void OnQuerySubmitted(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxQuerySubmittedEventArgs^ args);
			void OnResultSuggestionChosen(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxResultSuggestionChosenEventArgs^ args);
			void OnSuggestionsRequested(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxSuggestionsRequestedEventArgs^ args);
		protected:
			virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
			virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		};
	}
}
