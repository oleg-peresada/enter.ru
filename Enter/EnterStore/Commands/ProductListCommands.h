#pragma once

#include "HttpCommand.h"
#include "Helpers.h"
#include "Filters\ProductListFilters.h"
#include "Models\TrackerCardModels.h"

#include <string>
#include <collection.h>

using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;

namespace EnterStore
{
	namespace Commands
	{
		[Platform::Metadata::Flags]
		public enum class SortCommon : unsigned int
		{
			asc = 0,
			desc,
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class SortProduct sealed
		{
		public:
			SortProduct(String^ id, SortCommon sortType);

			property String^ Id
			{
				String^ get();
			}

			property SortCommon SortType
			{
				SortCommon get();
			}
		private:
			SortCommon source_sortType;
			String^ source_Id;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class RangeSelectedFilter sealed
		{
		public:
			RangeSelectedFilter();
			RangeSelectedFilter(String^ filterId, double min, double max);

			property String^ FilterId
			{
				String^ get();
			}

			property double Min
			{
				double get();
			}

			property double Max
			{
				double get();
			}
		private:
			String^ source_filterId;
			double source_min;
			double source_max;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class MultipleSelectedFilter sealed
		{
		public:
			MultipleSelectedFilter();
			MultipleSelectedFilter(String^ filterId);

			property String^ FilterId
			{
				String^ get();
			}

			property IVector<int>^ SelectedType
			{
				IVector<int>^ get();
				void set(IVector<int>^ val);
			}
		private:
			String^ source_filterId;
			IVector<int>^ source_SelectedType;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class BooleanSelectedFilter sealed
		{
		public:
			BooleanSelectedFilter();
			BooleanSelectedFilter(String^ filterId, bool checked);

			property String^ FilterId
			{
				String^ get();
			}

			property bool Checked
			{
				bool get();
			}
		private:
			String^ source_filterId;
			bool source_checked;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class FilterProductQuery sealed
		{
		public:
			FilterProductQuery(int category_id, unsigned int limit, unsigned int offset, SortProduct^ sortType);

			property unsigned int Offset
			{
				unsigned int get();
			}

			property unsigned int Limit
			{
				unsigned int get();
			}

			property int CategoryId
			{
				int get();
			}

			property SortProduct^ SortType
			{
				SortProduct^ get();
			}

			property IVector<Object^>^ Filters
			{
				IVector<Object^>^ get();
				void set(IVector<Object^>^ value);
			}
		internal:
			String^ Stringify();
		private:
			unsigned int source_offset;
			unsigned int source_limit;
			int source_categoryId;
			SortProduct^ source_sortType;
			IVector<Object^>^ source_filters;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductListCommands sealed
		{
		public:
			ProductListCommands(int regionId, FilterProductQuery^ filter_query);
			IAsyncOperationWithProgress<IObservableVector<ProductCardModels^>^, HttpProgress>^ ProductOperationAsync();

			property int RegionId
			{
				int get();
			}

			property FilterProductQuery^ FilterSource
			{
				FilterProductQuery^ get();
			}
		private:
			int source_regionId;
			FilterProductQuery^ source_filterQuery;
		};
	}
}