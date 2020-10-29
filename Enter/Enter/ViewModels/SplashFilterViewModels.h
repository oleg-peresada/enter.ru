#pragma once

#include "ViewModelsBase.h"
#include "LoadStateEventArgs.h"
#include "RelayCommand.h"
#include "DataModel\GroupCategorySource.h"

using namespace Enter;
using namespace Enter::DataModel;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;

namespace Enter
{
	namespace ViewModels
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class SplashFilterViewModels sealed : public ViewModelsBase
		{
		public:
			property int RegionId
			{
				int get();
				void set(int value);
			}

			property int CategoryId
			{
				int get();
				void set(int value);
			}

			property IObservableVector<FilterProductDataModel^>^ Filters
			{
				IObservableVector<FilterProductDataModel^>^ get();
				void set(IObservableVector<FilterProductDataModel^>^ value);
			}

			property IVector<Object^>^ SelectedFilters
			{
				IVector<Object^>^ get();
			}

			property FilterProductDataModel^ MultipleDataContext
			{
				FilterProductDataModel^ get();
			}

			property Object^ SelectedItem
			{
				Object^ get();
				void set(Object^ value);
			}

			property IVector<String^>^ AllSorting
			{
				IVector<String^>^ get();
			}

			property String^ SelectedSortingItem
			{
				String^ get();
				void set(String^ value);
			}

			property RelayCommand^ YesTemplateCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ NoTemplateCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ RangeSliderCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ MultipleCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ ResetFilterCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ CloseWindowCommand
			{
				RelayCommand^ get();
			}
		internal:
			SplashFilterViewModels(Windows::UI::Xaml::Controls::Page^ page);
			void OnLoadedFilterView(Object ^sender, RoutedEventArgs ^e);
			void OnMultipleDataContextChanged(Windows::UI::Xaml::FrameworkElement^ sender, Windows::UI::Xaml::DataContextChangedEventArgs^ args);
		private:
			int source_categoryId;
			int source_regionId;
			FilterProductDataModel^ source_multiple;
			Object^ source_selectedItem;
			String^ source_selectedSorting;

			int HasFilter(String^ filterId);
			void OnCheckedTemplateCommand(Object^ element, bool isChecked);
			void OnMultipleCommand(Object^ parameter);
			void OnRangeCommand(Object^ parameter);
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
		};
	}
}