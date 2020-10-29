#pragma once

#include "ViewModelsBase.h"
#include "LoadStateEventArgs.h"
#include "RelayCommand.h"
#include "View\TrackerExtensionsView.xaml.h"
#include "DataModel\Storage\AutorizationStorage.h"

using namespace Enter;

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
		public ref class TrackerViewModels sealed : public ViewModelsBase
		{
		public:
			property IVector<TrackerOrderModels^>^ TrackerVector
			{
				IVector<TrackerOrderModels^>^ get();
				void set(IVector<TrackerOrderModels^>^ value);
			}

			property unsigned int Size
			{
				unsigned int get();
				void set(unsigned int value);
			}

			property RelayCommand^ RefreshCommand
			{
				RelayCommand^ get();
			}
		internal:
			TrackerViewModels(Windows::UI::Xaml::Controls::Page^ page);
			void LoadedTask(bool isCached);
			void OnItemClick(Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
		private:
			IVector<TrackerOrderModels^>^ m_TrackerVector;
			unsigned int m_size;
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
		};
	}
}