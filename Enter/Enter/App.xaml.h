//
// App.xaml.h
// Объявление класса приложения.
//

#pragma once

#include "App.g.h"
#include "View\Settings\AccountNewFlyout.xaml.h"
#include "View\Settings\AutorizationFlyout.xaml.h"
#include "View\SplashScreenView.xaml.h"
#include "Controls\UI\SliderRange.h"

namespace Enter
{
	/// <summary>
	/// Обеспечивает зависящее от конкретного приложения поведение, дополняющее класс Application по умолчанию.
	/// </summary>
	ref class App sealed
	{
	protected:
		virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e) override;
		virtual void OnWindowCreated(Windows::UI::Xaml::WindowCreatedEventArgs^ e) override;
	internal:
		App();
	private:
		void OnUICommandAutorization(Windows::UI::Popups::IUICommand^ command);
		void OnUICommandAccountNew(Windows::UI::Popups::IUICommand^ command);
		void OnUICommandConditions(Windows::UI::Popups::IUICommand^ command);
		void OnAppCommandRequest(Windows::UI::ApplicationSettings::SettingsPane^ panel, Windows::UI::ApplicationSettings::SettingsPaneCommandsRequestedEventArgs^ args);
		void OnSuspending(Platform::Object^ sender, Windows::ApplicationModel::SuspendingEventArgs^ e);
	};
}
