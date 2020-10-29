#pragma once

#include "ViewModelsBase.h"
#include "LoadStateEventArgs.h"
#include "RelayCommand.h"

#include "DataModel\Storage\AutorizationStorage.h"

#include "View\Settings\AccountNewFlyout.xaml.h"
#include "View\Settings\AutorizationFlyout.xaml.h"

#include "Controls\PersonalDataChangedControl.xaml.h"
#include "Controls\CitiesMenuControl.xaml.h"

using namespace Enter;
using namespace Enter::Controls;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Controls::Primitives;

namespace Enter
{
	namespace ViewModels
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class AccountViewModels sealed : public ViewModelsBase
		{
		public:
			virtual ~AccountViewModels();

			property String^ ResetEmail
			{
				String^ get();
				void set(String^ val);
			}

			property String^ ResetPhone
			{
				String^ get();
				void set(String^ val);
			}

			property String^ MessageReset
			{
				String^ get();
				void set(String^ val);
			}

			property String^ RegionText
			{
				String^ get();
				void set(String^ value);
			}

			property RelayCommand^ ResetPasswordCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ RegistrationCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ AutorizationCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ PersonalOrderCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ ChangedPersonalDataCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ RegionChangedCommand
			{
				RelayCommand^ get();
			}
		internal:
			AccountViewModels(Windows::UI::Xaml::Controls::Page^ page);
			void OnAutorization();
			void OnRegistration();
			void PersonalOrderData();
			void PersonalDataChanged();
			void RegionChanged();
		private:
			String^ tokenStorage;
			String^ source_resetEmail;
			String^ source_resetPhone;
			String^ source_messageReset;
			String^ source_regionText;

			Popup^ regionPopup;
			EventRegistrationToken _regionActivateToken;
			EventRegistrationToken _regionCloseToken;
			void OnClosedRegion(Platform::Object ^sender, Platform::Object ^args);
			void OnActivatedRegion(Platform::Object ^sender, Windows::UI::Core::WindowActivatedEventArgs ^e);
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
		};
	}
}