#pragma once

#include <string>
#include <collection.h>

#include "HttpCommand.h"
#include "Helpers.h"

#include "Filters\ProductListFilters.h"
#include "Models\TrackerCardModels.h"
#include "ProductListCommands.h"

using namespace EnterStore::Models;
using namespace EnterStore::Commands;
using namespace EnterStore::Commands::Filters;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;

namespace EnterStore
{
	namespace Commands
	{
		[Platform::Metadata::Flags]
		public enum struct SearchType : unsigned int
		{
			Product = 1,
			Service = 2,
		};

		[Platform::Metadata::Flags]
		public enum class SearchSortType : unsigned int
		{
			price = 1,
			name,
			brand_name,
			rating,
			added,
			category_id,
			category_name,
			article,
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		[Windows::UI::Xaml::Data::Bindable]
		public ref class SearchIsCategory sealed
		{
		public:
			SearchIsCategory() { }
			SearchIsCategory(int id, int count, String^ name);

			property int Id
			{
				int get();
			}

			property int Count
			{
				int get();
			}

			property String^ Name
			{
				String^ get();
			}
		private:
			unsigned int source_count;
			int source_id;
			String^ source_name;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class SearchProductQuery sealed
		{
		public:
			SearchProductQuery(int categoryId, SearchSortType sortType, SortCommon sort);

			property SearchSortType SearchSort
			{
				SearchSortType get();
			}

			property int CategoryId
			{
				int get();
			}

			property SortCommon Sort
			{
				SortCommon get();
			}
		private:
			int source_categoryId;
			SearchSortType source_sortType;
			SortCommon source_sort;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class SearchCommands sealed
		{
		public:
			SearchCommands(String^ request, int geoId, int shopId, SearchType typeId);
			
			IAsyncOperationWithProgress<IVector<ProductCardModels^>^, HttpProgress>^ SearchAsync();

			property String^ Request
			{
				String^ get();
			}

			property int GeoId
			{
				int get();
			}

			property int ShopId
			{
				int get();
			}

			property SearchType TypeId
			{
				SearchType get();
			}

			property SearchProductQuery^ ProductQuery
			{
				SearchProductQuery^ get();
				void set(SearchProductQuery^ val);
			}

			property IVector<SearchIsCategory^>^ CategoryVector
			{
				IVector<SearchIsCategory^>^ get();
			}
		private:
			void ParseInnerCategory(String^ contentValue);
			String^ source_request;
			int source_geoId;
			int source_shopId;
			SearchType source_typeId;
			SearchProductQuery^ source_productQuery;
			IVector<SearchIsCategory^>^ source_categoryVector;
		};
	}
}