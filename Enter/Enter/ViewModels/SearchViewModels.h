#pragma once

#include "ViewModelsBase.h"
#include "LoadStateEventArgs.h"
#include "DataModel\Storage\AutorizationStorage.h"
#include "View\ProductExtensionsView.xaml.h"

using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Controls;

namespace Enter
{
	namespace ViewModels
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class SearchViewModels sealed : public ViewModelsBase
		{
		public:
			SearchViewModels(Windows::UI::Xaml::Controls::Page^ page);

			property String^ QueryHeader
			{
				String^ get();
				void set(String^ val);
			}

			property IVector<ProductCardModels^>^ QueryProduct
			{
				IVector<ProductCardModels^>^ get();
				void set(IVector<ProductCardModels^>^ val);
			}

			property IVector<SearchIsCategory^>^ CategoryView
			{
				IVector<SearchIsCategory^>^ get();
				void set(IVector<SearchIsCategory^>^ val);
			}

			property SearchIsCategory^ CategoryItem
			{
				SearchIsCategory^ get();
				void set(SearchIsCategory^ val);
			}

			property IVector<String^>^ SearchSortView
			{
				IVector<String^>^ get();
			}

			property String^ SearchSortItem
			{
				String^ get();
				void set(String^ val);
			}
		internal:
			void SearchBegin(String^ queryText);
			void OnItemProductClick(Object^ parameter);
			void OnSearchCategoryProduct(int idCategory, String^ queryName, String^ sortValue);
			void OnSearchQuerySubmittedView(SearchBox^ sender, SearchBoxQuerySubmittedEventArgs^ args);
		private:
			String^ source_QueryHeader;
			IVector<ProductCardModels^>^ source_QueryProduct;
			IVector<SearchIsCategory^>^ source_categoryView;
			SearchIsCategory^ source_categoryItem;
			bool isCategory;
			bool isSort;
			String^ source_searchSortItem;
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
		};
	}
}