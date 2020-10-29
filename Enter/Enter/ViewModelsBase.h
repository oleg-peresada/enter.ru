#pragma once

#include "RelayCommand.h"
#include "LoadStateEventArgs.h"
#include "SuspensionManager.h";
#include "Helpers.h"
#include "DataModel\Storage\AutorizationStorage.h"

using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::ApplicationModel::Search;

namespace Enter
{
	[Windows::Foundation::Metadata::WebHostHidden]
	[Windows::UI::Xaml::Data::Bindable]
	public ref class ViewModelsBase : public DependencyObject, INotifyPropertyChanged
	{
	public:
		virtual event PropertyChangedEventHandler^ PropertyChanged;

		property RelayCommand^ GoBackCommand
		{
			RelayCommand^ get();
		}

		property RelayCommand^ GoForwardCommand
		{
			RelayCommand^ get();
		}

		property double WidthScreen
		{
			double get();
			void set(double sizeValue);
		}

		property bool IsActive
		{
			bool get();
			void set(bool value);
		}

		property Visibility RootVisibility
		{
			Visibility get();
			void set(Visibility value);
		}
	internal:
		ViewModelsBase(Page^ page, RelayCommand^ goBack = nullptr, RelayCommand^ goForward = nullptr);

		bool CanGoBack();
		void GoBack();
		bool CanGoForward();
		void GoForward();

		void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e);
		void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e);

		event LoadStateEventHandler^ LoadState;
		event SaveStateEventHandler^ SaveState;

		void SearchRequest(SearchBox^ sender, SearchBoxSuggestionsRequestedEventArgs^ args);
		void SearchSubmitted(SearchBox^ sender, SearchBoxQuerySubmittedEventArgs^ args);
		void SearchSuggestionChosen(SearchBox^ sender, SearchBoxResultSuggestionChosenEventArgs^ args);
		void OnActiveState(bool isTransition);

		property Page^ ViewPage
		{
			Page^ get();
		}

		property Frame^ ViewFrame
		{
			Frame^ get();
		}
	private:
		Page^ view_Page;
		RelayCommand^ view_goBackCommand;
		RelayCommand^ view_goForwardCommand;

		double _widthScreen;
		bool _isActive;
		Visibility _rootVisibility;
		bool _navigationShortcutsRegistered;
		Windows::Foundation::EventRegistrationToken _acceleratorKeyEventToken;
		Windows::Foundation::EventRegistrationToken _pointerPressedEventToken;
		Windows::Foundation::EventRegistrationToken _sizeChangedPageToken;
		void CoreDispatcher_AcceleratorKeyActivated(Windows::UI::Core::CoreDispatcher^ sender, Windows::UI::Core::AcceleratorKeyEventArgs^ e);
		void CoreWindow_PointerPressed(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ e);
		void OnSizeChanged(Platform::Object ^sender, Windows::UI::Xaml::SizeChangedEventArgs ^e);

		Platform::String^ _pageKey;
		Windows::Foundation::EventRegistrationToken _loadedEventToken;
		Windows::Foundation::EventRegistrationToken _unloadedEventToken;
		void OnLoaded(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void OnUnloaded(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	protected:
		virtual void OnPropertyChanged(Platform::String^ propertyName);
		virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, LoadStateEventArgs^ state);
		virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, SaveStateEventArgs^ state);
	};
}

