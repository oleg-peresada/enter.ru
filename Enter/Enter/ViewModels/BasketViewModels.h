#pragma once

#include <vector>

#include "ViewModelsBase.h"
#include "LoadStateEventArgs.h"
#include "RelayCommand.h"

#include "DataModel\BasketProductSerialize.h"
#include "DataModel\Storage\AutorizationStorage.h"

#include "View\ProductExtensionsView.xaml.h"
#include "View\AboutShopView.xaml.h"
#include "View\OrderView.xaml.h"
#include "View\Settings\AutorizationFlyout.xaml.h"

using namespace Enter;
using namespace Enter::ViewModels;
using namespace Enter::DataModel;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace ViewModels
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class BasketViewModels sealed : public ViewModelsBase
		{
		public:
			property IObservableVector<BasketProductDataModel^>^ VectorProduct
			{
				IObservableVector<BasketProductDataModel^>^ get();
				void set(IObservableVector<BasketProductDataModel^>^ val);
			}

			property double Amount
			{
				double get();
				void set(double val);
			}

			property Windows::UI::Xaml::Visibility VisibilityEdit
			{
				Windows::UI::Xaml::Visibility get();
				void set(Windows::UI::Xaml::Visibility val);
			}

			property Windows::UI::Xaml::Visibility VisibilitySelectedButton
			{
				Windows::UI::Xaml::Visibility get();
				void set(Windows::UI::Xaml::Visibility val);
			}

			property int SelectionIndex
			{
				int get();
				void set(int index);
			}

			property RelayCommand^ RemoveCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ AddCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ EditCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ OrderCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ RefreshCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ ClearCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ DeleteCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ ShopCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ ClearSelectionCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ WithOrderCommand
			{
				RelayCommand^ get();
			}

			property bool IsStiskyBottom
			{
				bool get();
				void set(bool val);
			}

			property bool IsOpenBottom
			{
				bool get();
				void set(bool val);
			}

			property bool IsStiskyTop
			{
				bool get();
				void set(bool val);
			}

			property bool IsOpenTop
			{
				bool get();
				void set(bool val);
			}
		internal:
			BasketViewModels(Windows::UI::Xaml::Controls::Page^ page);
			void OnLoadedView();
			void OnAmountSum();
			void OnSaveSerialize();
			void OnSelectionProduct(Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ parameter);
			void OnItemClickView(Object^ parameter);
		private:
			IObservableVector<BasketProductDataModel^>^ source_VectorProduct;
			double source_Amount;
			int source_selectionIndex;
			Windows::UI::Xaml::Visibility source_editVisibility;
			Windows::UI::Xaml::Visibility source_SelectedAppBarBottom;
			bool source_isBottomStisky;
			bool source_isBottomOpen;
			bool source_isTopStisky;
			bool source_isTopOpen;
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
		};
	}
}