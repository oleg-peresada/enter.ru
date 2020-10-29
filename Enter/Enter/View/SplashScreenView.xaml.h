//
// SplashScreenView.xaml.h
// Объявление класса SplashScreenView
//

#pragma once

#include "View\SplashScreenView.g.h"
#include "MainPage.xaml.h"
#include "DataModel\Storage\AutorizationStorage.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace View
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class SplashScreenView sealed
		{
		public:
			SplashScreenView();
			SplashScreenView(Windows::ApplicationModel::Activation::SplashScreen^ splashScreen, bool loadState);
			virtual ~SplashScreenView();
		private:
			Windows::ApplicationModel::Activation::SplashScreen^ _splashScreen;
			Windows::Foundation::Rect splashImageRect;
			bool dismissed;
			DispatcherTimer^ timerDispatcher;

			EventRegistrationToken _tickToken;
			EventRegistrationToken _dismissedToken;
			EventRegistrationToken _sizeChangedToken;

			void PositionImage();
			void OnRootNavigate(Object^ parameter);
			void OnVisualState(bool isTransition);
			void OnDismissed(Windows::ApplicationModel::Activation::SplashScreen ^sender, Platform::Object ^args);
			void OnSizeChanged(Platform::Object ^sender, Windows::UI::Core::WindowSizeChangedEventArgs ^e);
			void OnTick(Platform::Object ^sender, Platform::Object ^args);
		};
	}
}
