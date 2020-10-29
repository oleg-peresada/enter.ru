//
// App.xaml.cpp
// Реализация класса приложения.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "App.xaml.h"

using namespace Enter;
using namespace Enter::View;
using namespace Enter::View::Settings;

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::ApplicationSettings;
using namespace Windows::UI::Popups;
using namespace Microsoft::ApplicationInsights::Telemetry::WindowsStore;

/// <summary>
/// Инициализирует одноэлементный объект приложения.  Это первая выполняемая строка разрабатываемого
/// кода; поэтому она является логическим эквивалентом main() или WinMain().
/// </summary>
App::App()
{
	InitializeComponent();

	TimeSpan timeAnalitics;
	timeAnalitics.Duration = 100000000;
	ClientAnalyticsSession::Default->ResumeAppRestartTimeout = timeAnalitics;
	ClientAnalyticsSession::Default->Start("key session");

	Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
}

/// <summary>
/// Invoked when the application is launched normally by the end user.	Other entry points
/// will be used such as when the application is launched to open a specific file.
/// </summary>
/// <param name="e">Сведения о запросе и обработке запуска.</param>
void App::OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ e)
{

#if _DEBUG
		// Show graphics profiling information while debugging.
		if (IsDebuggerPresent())
		{
			// Display the current frame rate counters
			 DebugSettings->EnableFrameRateCounter = true;
		}
#endif


	if (e->PreviousExecutionState != ApplicationExecutionState::Running)
	{
		bool loadState = (e->PreviousExecutionState == ApplicationExecutionState::Terminated);
		SplashScreenView^ splashScreen = ref new SplashScreenView(e->SplashScreen, loadState);
		Window::Current->Content = splashScreen;
	}

	Window::Current->Activate();
}

/// <summary>
/// Invoked when application execution is being suspended.	Application state is saved
/// без учета информации о том, будет ли оно завершено или возобновлено с неизменным
/// содержимым памяти.
/// </summary>
/// <param name="sender">Источник запроса приостановки.</param>
/// <param name="e">Сведения о запросе приостановки.</param>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
	(void) sender;	// Неиспользуемый параметр
	(void) e;	// Неиспользуемый параметр

	//TODO: Сохранить состояние приложения и остановить все фоновые операции
}

void App::OnWindowCreated(WindowCreatedEventArgs^ e)
{
	(void) e;

	SettingsPane::GetForCurrentView()->CommandsRequested += 
		ref new TypedEventHandler<SettingsPane^, SettingsPaneCommandsRequestedEventArgs^>(this, &App::OnAppCommandRequest);
}

void App::OnUICommandAutorization(Windows::UI::Popups::IUICommand^ command)
{
	auto autorizationFlyout = ref new AutorizationFlyout();
	autorizationFlyout->Width = 500;
	autorizationFlyout->Show();
}

void App::OnUICommandAccountNew(Windows::UI::Popups::IUICommand^ command)
{
	auto accountFlyout = ref new AccountNewFlyout();
	accountFlyout->Width = 500;
	accountFlyout->Show();
}

void App::OnUICommandConditions(Windows::UI::Popups::IUICommand^ command)
{
	Windows::System::Launcher::LaunchUriAsync(ref new Uri("http://wenteronline.wix.com/privacy"));
}

void App::OnAppCommandRequest(SettingsPane^ panel, SettingsPaneCommandsRequestedEventArgs^ args)
{
	auto autorizationHandler = ref new UICommandInvokedHandler(this, &App::OnUICommandAutorization);
	auto autorizationSettings = ref new SettingsCommand(1, "Авторизация", autorizationHandler);
	args->Request->ApplicationCommands->Append(autorizationSettings);

	auto accountNewHandler = ref new UICommandInvokedHandler(this, &App::OnUICommandAccountNew);
	auto accountNewSettings = ref new SettingsCommand(2, "Регистрация", accountNewHandler);
	args->Request->ApplicationCommands->Append(accountNewSettings);

	auto conditionHandler = ref new UICommandInvokedHandler(this, &App::OnUICommandConditions);
	auto conditionSettings = ref new SettingsCommand(3, "Условия использования", conditionHandler);
	args->Request->ApplicationCommands->Append(conditionSettings);
}