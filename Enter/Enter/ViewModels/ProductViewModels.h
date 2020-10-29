#pragma once

#include <sstream>
#include <vector>

#include "LoadStateEventArgs.h"
#include "ViewModelsBase.h"
#include "RelayCommand.h"
#include "View\ProductExtensionsView.xaml.h"
#include "View\SplashFilterView.xaml.h"
#include "View\BasketView.xaml.h"
#include "DataModel\IncrementFilterLoading.h"
#include "DataModel\Storage\AutorizationStorage.h"

using namespace Enter;
using namespace Enter::View;
using namespace EnterStore::Models;
using namespace EnterStore::Commands;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls::Primitives;

namespace Enter
{
	namespace ViewModels
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductViewModels sealed : public ViewModelsBase
		{
		public:
			virtual ~ProductViewModels();

			property String^ Header
			{
				String^ get();
				void set(String^ val);
			}

			property IObservableVector<ProductCardModels^>^ ProductCollection
			{
				IObservableVector<ProductCardModels^>^ get();
				void set(IObservableVector<ProductCardModels^>^ val);
			}

			property Enter::DataModel::IncrementFilterLoading^ FilterProductIncrement
			{
				Enter::DataModel::IncrementFilterLoading^ get();
				void set(Enter::DataModel::IncrementFilterLoading^ val);
			}

			property bool BottomIsOpen
			{
				bool get();
				void set(bool value);
			}

			property bool BottomIsSticky
			{
				bool get();
				void set(bool value);
			}

			property DataTemplate^ ViewTemplate
			{
				DataTemplate^ get();
				void set(DataTemplate^ value);
			}

			property double HorizontalOffset
			{
				double get();
				void set(double value);
			}

			property RelayCommand^ FilterCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ TableViewCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ SketchCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ BasketCommand
			{
				RelayCommand^ get();
			}
		internal:
			ProductViewModels(Windows::UI::Xaml::Controls::Page^ page);
			void OnIncrementFilter(int id, String^ header);
			void OnProductItemClick(Object^ parameter);
			void OnFilterPopup();
			void OnSplashFilterChanged(Platform::Object ^sender, Enter::View::SplashFilterChangedEventArgs ^args);
			void OnFilterClosed(Platform::Object ^sender, Platform::Object ^args);
			void OnFilterActivated(Platform::Object ^sender, Windows::UI::Core::WindowActivatedEventArgs ^e);
		private:
			Popup^ popupFilter;
			String^ source_header;
			IObservableVector<ProductCardModels^>^ source_productCollection;
			Enter::DataModel::IncrementFilterLoading^ source_FilterProductIncrement;

			bool source_bottomIsOpen;
			bool source_bottomIsSticky;
			DataTemplate^ source_viewTemplate;
			SplashFilterView^ filterControl;
			double m_horizontalOffset;

			EventRegistrationToken source_popupFilterCloseToken;
			EventRegistrationToken source_WindowFilterActivateToken;
			EventRegistrationToken splashFilterToken;
			EventRegistrationToken _incrementLoadingToken;
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
			void OnIncrementLoadingProgress(Platform::Object ^sender, bool isProgress);
		};
	}
}