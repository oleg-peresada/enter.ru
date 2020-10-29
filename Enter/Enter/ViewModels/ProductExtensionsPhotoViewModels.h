#pragma once

#include "ViewModelsBase.h"
#include "LoadStateEventArgs.h"

using namespace Enter;
using namespace EnterStore::Models;
using namespace EnterStore::Commands;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace ViewModels
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductExtensionsPhotoViewModels sealed : public Enter::ViewModelsBase
		{
		public:
			property ProductExtensionsCardModels^ CardProduct
			{
				ProductExtensionsCardModels^ get();
				void set(ProductExtensionsCardModels^ val);
			}
		internal:
			ProductExtensionsPhotoViewModels(Windows::UI::Xaml::Controls::Page^ page);
		private:
			ProductExtensionsCardModels^ source_cardModel;
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
		};
	}
}