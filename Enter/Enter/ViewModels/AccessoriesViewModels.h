#pragma once

#include "ViewModelsBase.h"
#include "LoadStateEventArgs.h"
#include "RelayCommand.h"

#include "DataModel\Storage\AutorizationStorage.h"
#include "View\ProductExtensionsView.xaml.h"

using namespace Enter;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;

namespace Enter
{
	namespace ViewModels
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class AccessoriesViewModels sealed : public ViewModelsBase
		{
		public:
			property IObservableVector<ProductCardModels^>^ ProductCards
			{
				IObservableVector<ProductCardModels^>^ get();
				void set(IObservableVector<ProductCardModels^>^ value);
			}

			property String^ Header
			{
				String^ get();
				void set(String^ value);
			}

			property double HorizontalOffset
			{
				double get();
				void set(double value);
			}

			property RelayCommand^ RefreshCommand
			{
				RelayCommand^ get();
			}
		internal:
			AccessoriesViewModels(Windows::UI::Xaml::Controls::Page^ page);
			void LoadedTask(Object^ parameter, bool isCached);
			concurrency::task<void> ProductsLoaded(IVector<int>^ products, bool isCached);
			void OnItemClick(Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
		private:
			IObservableVector<ProductCardModels^>^ m_productCards;
			String^ m_header;
			Object^ m_parameter;
			double m_horizontalOffset;
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
		};
	}
}