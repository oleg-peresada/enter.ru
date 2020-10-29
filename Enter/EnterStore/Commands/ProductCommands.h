#pragma once

#include <collection.h>
#include <string>

#include "Models\TrackerCardModels.h"

using namespace EnterStore;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;

namespace EnterStore
{
	namespace Commands
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductCommands sealed
		{
		public:
			ProductCommands(IVector<int>^ id_product, int geo_id);
			IAsyncOperationWithProgress<IObservableVector<ProductCardModels^>^, HttpProgress>^ ProductsAsync();
			IAsyncOperationWithProgress<IObservableVector<ProductCardModels^>^, HttpProgress>^ ProductsAsync(bool isCached);

			property IVector<int>^ Product
			{
				IVector<int>^ get();
			}

			property int GeoId
			{
				int get();
			}
		private:
			IVector<int>^ m_product;
			int m_geoId;
		};
	}
}