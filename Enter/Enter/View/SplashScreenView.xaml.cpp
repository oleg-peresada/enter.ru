//
// SplashScreenView.xaml.cpp
// Реализация класса SplashScreenView
//

#include "pch.h"
#include "SplashScreenView.xaml.h"

using namespace Enter;
using namespace Enter::View;
using namespace Enter::ViewModels;
using namespace Enter::DataModel::Storage;
using namespace EnterStore::Commands;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::ApplicationModel::Activation;

SplashScreenView::SplashScreenView()
{
	InitializeComponent();
}

SplashScreenView::SplashScreenView(SplashScreen^ splashScreen, bool loadState) : _splashScreen(splashScreen), dismissed(false)
{
	InitializeComponent();

	_sizeChangedToken = Window::Current->SizeChanged += ref new WindowSizeChangedEventHandler(this, &SplashScreenView::OnSizeChanged);

	if (splashScreen != nullptr)
	{
		_dismissedToken = _splashScreen->Dismissed += ref new TypedEventHandler<SplashScreen ^, Object ^>(this, &SplashScreenView::OnDismissed);
		splashImageRect = _splashScreen->ImageLocation;
		PositionImage();
	}

	timerDispatcher = ref new DispatcherTimer();
	_tickToken = timerDispatcher->Tick += ref new EventHandler<Object ^>(this, &SplashScreenView::OnTick);
	
	auto timeInterval = TimeSpan();
	timeInterval.Duration = 22000000;

	timerDispatcher->Interval = timeInterval;
	timerDispatcher->Start();
}

SplashScreenView::~SplashScreenView()
{
	if (timerDispatcher != nullptr)
	{
		timerDispatcher->Tick -= _tickToken;
	}

	if (_splashScreen != nullptr)
	{
		_splashScreen->Dismissed -= _dismissedToken;
	}

	Window::Current->SizeChanged -= _sizeChangedToken;
}

void SplashScreenView::PositionImage()
{
	Canvas::SetTop(extendedSplashScreen, splashImageRect.Y);
	Canvas::SetLeft(extendedSplashScreen, splashImageRect.X);
	extendedSplashScreen->Height = splashImageRect.Height;
	extendedSplashScreen->Width = splashImageRect.Width;
}

void SplashScreenView::OnRootNavigate(Object^ parameter)
{
	auto rootFrame = dynamic_cast<Windows::UI::Xaml::Controls::Frame^>(Window::Current->Content);
	if (rootFrame == nullptr)
	{
		rootFrame = ref new Frame();
		if (rootFrame->Content == nullptr)
		{
			if (!rootFrame->Navigate(TypeName(MainPage::typeid), parameter))
			{
				throw ref new FailureException("Failed to create main page");
			}

			Window::Current->Content = rootFrame;
		}
	}
}

void SplashScreenView::OnVisualState(bool isTransition)
{
	if (isTransition)
	{
		VisualStateManager::GoToState(this, "NetworkOpen", isTransition);
	}
	else
	{
		VisualStateManager::GoToState(this, "NetworkClose", isTransition);
	}
}

void SplashScreenView::OnDismissed(SplashScreen ^sender, Object ^args)
{
}

void SplashScreenView::OnSizeChanged(Object ^sender, Windows::UI::Core::WindowSizeChangedEventArgs ^e)
{
	if (_splashScreen != nullptr)
	{
		splashImageRect = _splashScreen->ImageLocation;
		PositionImage();
	}
}

void SplashScreenView::OnTick(Object ^sender, Object ^args)
{
	using namespace Windows::Networking::Connectivity;

	if (timerDispatcher != nullptr)
	{
		ConnectionProfile^ connectProfile = NetworkInformation::GetInternetConnectionProfile();
		if (connectProfile->GetNetworkConnectivityLevel() == NetworkConnectivityLevel::InternetAccess)
		{
			timerDispatcher->Stop();
			this->OnVisualState(true);

			if (!CityTokenStorage::Current->IsCityToken)
			{
				auto promoCommand = ref new CitiesCommands();
				auto operationPromo = promoCommand->MenuCitiesAsync();
				concurrency::create_task(operationPromo).then([this](IObservableVector<CitiesModels^>^ valueModel)
				{
					this->OnRootNavigate(valueModel);
				});
			}
			else
			{
				this->OnRootNavigate(nullptr);
			}
		}
		else
		{
			this->OnVisualState(false);
		}
	}
}