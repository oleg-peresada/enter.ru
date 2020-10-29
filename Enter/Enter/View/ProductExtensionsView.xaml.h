//
// ProductExtensionsView.xaml.h
// Объявление класса ProductExtensionsView
//

#pragma once

#include "View\ProductExtensionsView.g.h"
#include "ViewModels\ProductExtensionsViewModels.h"

namespace Enter
{
	namespace View
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductExtensionsView sealed
		{
		public:
			ProductExtensionsView();
		private:
			Enter::ViewModels::ProductExtensionsViewModels^ productExtensionsView;
			void OnHubSectionHeaderClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::HubSectionHeaderClickEventArgs^ e);
			void OnSuggestionsRequested(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxSuggestionsRequestedEventArgs^ args);
			void OnQuerySubmitted(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxQuerySubmittedEventArgs^ args);
			void OnResultSuggestionChosen(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxResultSuggestionChosenEventArgs^ args);
			void OnOptionSelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
			void OnPropertySelectionChanged(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
		protected:
			virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
			virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		};
	}
}
