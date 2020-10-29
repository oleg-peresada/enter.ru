#pragma once

#include <string>
#include <collection.h>

#include "Helpers.h"
#include "HttpCommand.h"
#include "Models\CitiesModels.h"

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
		public ref class CitiesCommands sealed
		{
		public:
			CitiesCommands();
			IAsyncOperationWithProgress<IObservableVector<CitiesModels^>^, HttpProgress>^ MenuCitiesAsync();
			IAsyncOperationWithProgress<IObservableVector<AutoCityModels^>^, HttpProgress>^ AutoCompleteCities(String^ letters);
		};
	}
}