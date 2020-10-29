#pragma once

#include <string>
#include <collection.h>

#include "HttpCommand.h"
#include "Helpers.h"

using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Filters;

namespace EnterStore
{
	namespace Commands
	{
		namespace Filters
		{
			[Windows::Foundation::Metadata::WebHostHidden]
			ref class ProductListFilters sealed : public IHttpFilter
			{
			public:
				ProductListFilters(IHttpFilter^ innerFilter);
				virtual ~ProductListFilters();
				virtual IAsyncOperationWithProgress<HttpResponseMessage^, HttpProgress>^ SendRequestAsync(HttpRequestMessage^ request);

				property int GeoId
				{
					int get();
					void set(int val);
				}
			private:
				IHttpFilter^ source_innerFilter;
				int source_geoId;
			};

			[Windows::Foundation::Metadata::WebHostHidden]
			ref class SearchProductFilter sealed : public IHttpFilter
			{
			public:
				SearchProductFilter(IHttpFilter^ innerFilter, int geoId, unsigned int typeId);
				virtual ~SearchProductFilter();
				virtual IAsyncOperationWithProgress<HttpResponseMessage^, HttpProgress>^ SendRequestAsync(HttpRequestMessage^ request);

				property int GeoId
				{
					int get();
				}

				property unsigned int TypeId
				{
					unsigned int get();
				}

				property String^ InnerCategory
				{
					String^ get();
				}
			private:
				void SetInnerCategory(String^ valueCategory);
				IHttpFilter^ source_innerFilter;
				int source_geoId;
				unsigned int source_TypeId;
				String^ source_Innercategory;
			};
		}
	}
}