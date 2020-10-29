#pragma once

#include "ViewModelsBase.h"
#include "LoadStateEventArgs.h"

#include "DataModel\GroupCategorySource.h"
#include "DataModel\Storage\AutorizationStorage.h"

#include "View\ProductView.xaml.h"
#include "View\CategoryTreeView.xaml.h"
#include "View\AboutShopView.xaml.h"

using namespace Enter::DataModel;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace ViewModels
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class CategoryTreeViewModels sealed : public Enter::ViewModelsBase
		{
		public:
			property String^ HeaderTree
			{
				String^ get();
				void set(String^ val);
			}

			property IObservableVector<GroupCategoryModel^>^ CategoryTreeCollection
			{
				IObservableVector<GroupCategoryModel^>^ get();
				void set(IObservableVector<GroupCategoryModel^>^ val);
			}

			property double HorizontalOffset
			{
				double get();
				void set(double value);
			}

			property RelayCommand^ ShopCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ RefreshCommand
			{
				RelayCommand^ get();
			}
		internal:
			CategoryTreeViewModels(Windows::UI::Xaml::Controls::Page^ page);
			void LoadedTask(Object^ parameter, bool isCached);
			void VariableCategoryItemClick(Object^ parameter);
		private:
			String^ category_header;
			IObservableVector<GroupCategoryModel^>^ category_TreeCollection;
			void GridParseContent(Object^ parameter);
			Object^ m_treeParameter;
			double m_horizontalOffset;
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
		};
	}
}