#pragma once

#include <collection.h>
#include <string>

#include "Helpers.h"
#include "HttpCommand.h"
#include "Models\ShopListModels.h"

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
		public enum class ShopListType : unsigned int
		{
			Id = 1,
			Slug,
			GeoId,
			None,
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ShopListCommands sealed
		{
		public:
			ShopListCommands(ShopListType type, String^ parameter);

			property ShopListType Type
			{
				ShopListType get();
			}

			property String^ Parameter
			{
				String^ get();
			}

			IAsyncOperationWithProgress<IVector<ShopListModels^>^, HttpProgress>^ ToShopCommandAsync();
			IAsyncOperationWithProgress<IVector<ShopListModels^>^, HttpProgress>^ ToShopCommandAsync(bool isCached);
		private:
			ShopListType shop_type;
			String^ shop_parameter;
		};
	}
}