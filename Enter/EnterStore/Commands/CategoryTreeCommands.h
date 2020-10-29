#pragma once

#include <collection.h>
#include <string>

#include "HttpCommand.h"
#include "Helpers.h"
#include "Models\CategoryTreeModels.h"

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
		public ref class CategoryTreeCommands sealed
		{
		public:
			CategoryTreeCommands(unsigned int rootId, unsigned int maxLevel, unsigned int regionId, bool loadParents);

			IAsyncOperationWithProgress<IVector<CategoryTreeModels^>^, HttpProgress>^ CategoryTreeCommandAsync();
			IAsyncOperationWithProgress<IVector<CategoryTreeModels^>^, HttpProgress>^ CategoryTreeCommandAsync(bool isCached);

			property unsigned int RootId
			{
				unsigned int get();
			}

			property unsigned int MaxLevel
			{
				unsigned int get();
			}

			property unsigned int RegionId
			{
				unsigned int get();
			}

			property bool IsLoadParents
			{
				bool get();
			}
		private:
			unsigned int tree_rootId;
			unsigned int tree_maxLevel;
			unsigned int tree_regionId;
			bool tree_loadParents;
		};
	}
}