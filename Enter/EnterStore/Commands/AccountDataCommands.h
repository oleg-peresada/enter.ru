#pragma once

#include <string>
#include <collection.h>

#include "Helpers.h"
#include "HttpCommand.h"

#include "Models\AccountDataModels.h"

using namespace EnterStore;
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
		public ref class ProductListOrder sealed
		{
		public:
			ProductListOrder();
			ProductListOrder(int id, int quantity);

			property int Id
			{
				int get();
			}

			property int Quantity
			{
				int get();
			}
		private:
			int source_id;
			int source_quantity;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class OrderCalcCommands sealed
		{
		public:
			OrderCalcCommands(int geoId, IVector<ProductListOrder^>^ val);

			IAsyncOperationWithProgress<Object^, HttpProgress>^ OrderCalcAsync();

			property int GeoId
			{
				int get();
			}

			property IVector<ProductListOrder^>^ ProductList
			{
				IVector<ProductListOrder^>^ get();
			}
		private:
			OrderCalcModels^ FromOrderCalc(String^ content);
			int source_geoId;
			IVector<ProductListOrder^>^ source_ProductList;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class UserContentCommands sealed
		{
		public:
			UserContentCommands(String^ token);
			IAsyncOperationWithProgress<UserContentModels^, HttpProgress>^ CurrentUserAsync();

			property String^ Token
			{
				String^ get();
			}
		private:
			String^ source_token;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PersonalDataUpdateCommands sealed
		{
		public:
			PersonalDataUpdateCommands(String^ token);
			IAsyncOperation<bool>^ UpdateAsync(PersonalDataUpdateModels^ dataValue);

			property String^ Token
			{
				String^ get();
			}
		private:
			String^ Stringify(PersonalDataUpdateModels^ dataValue);
			String^ source_token;
		};
	}
}