#pragma once

#include <string>
#include <collection.h>

#include "Helpers.h"
#include "HttpCommand.h"
#include "Models\FilterProductModels.h"

using namespace EnterStore::Models;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;

namespace EnterStore
{
	namespace Commands
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class FilterProductCommands sealed
		{
		public:
			FilterProductCommands(int regionId, int categoryId);
			IAsyncOperationWithProgress<IVector<FilterProductModels^>^, HttpProgress>^ FilterAsync();

			property int RegionId
			{
				int get();
			}

			property int CategoryId
			{
				int get();
			}
		private:
			int source_regionId;
			int source_categoryId;
		};

		[Platform::Metadata::Flags]
		public enum class BannerType : unsigned int
		{
			Standart = 1,
			Cap = 2,
			Exclusive = 3,
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PromoBannerCommands sealed
		{
		public:
			PromoBannerCommands(int geoId, BannerType bannerType);
			IAsyncOperation<IVector<PromoBannerModels^>^>^ PromoBannerAsync(bool isCached);

			property int GeoId
			{
				int get();
			}

			property BannerType TypeBanner
			{
				BannerType get();
			}
		private:
			int source_geoId;
			BannerType source_bannerType;
		};
	}
}