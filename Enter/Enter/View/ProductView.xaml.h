//
// ProductView.xaml.h
// Объявление класса ProductView
//

#pragma once

#include "View\ProductView.g.h"
#include "ViewModels\ProductViewModels.h"

namespace Enter
{
	namespace View
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductView sealed
		{
		public:
			ProductView();
		private:
			Enter::ViewModels::ProductViewModels^ productView;
			void OnItemProductClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
			void OnSuggestionsRequested(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxSuggestionsRequestedEventArgs^ args);
			void OnQuerySubmitted(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxQuerySubmittedEventArgs^ args);
			void OnResultSuggestionChosen(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxResultSuggestionChosenEventArgs^ args);
		protected:
			virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
			virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		};
	}
}
