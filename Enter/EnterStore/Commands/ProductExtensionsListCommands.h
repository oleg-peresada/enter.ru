#pragma once

#include <string>

#include "Helpers.h"
#include "HttpCommand.h"

#include "Models\ProductExtensionsCardModels.h"

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
		public enum class ProductExtensionsType : unsigned int
		{
			Id = 0,
			Slug,
			BarCode,
			Article,
			Ean,
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductExtensionsListCommands sealed
		{
		public:
			ProductExtensionsListCommands(String^ parameter, int geoId, ProductExtensionsType parameterType);

			IAsyncOperationWithProgress<ProductExtensionsCardModels^, HttpProgress>^ ProductExtensionsAsync(bool isCached);

			property String^ Parameter
			{
				String^ get();
			}

			property int GeoId
			{
				int get();
			}

			property ProductExtensionsType ParameterType
			{
				ProductExtensionsType get();
			}
		private:
			String^ source_parameter;
			int source_geoId;
			ProductExtensionsType source_parameterType;
		};
	}
}