//
// SplashFilterView.xaml.h
// Объявление класса SplashFilterView
//

#pragma once

#include "View\SplashFilterView.g.h"
#include "ViewModels\SplashFilterViewModels.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;

namespace Enter
{
	namespace View
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class SplashFilterChangedEventArgs sealed
		{
		public:
			property IVector<Object^>^ NewValue
			{
				IVector<Object^>^ get();
			}

			property EnterStore::Commands::SortProduct^ NewSort
			{
				EnterStore::Commands::SortProduct^ get();
			}
		internal:
			SplashFilterChangedEventArgs(IVector<Object^>^ newValue, EnterStore::Commands::SortProduct^ newSort);
		private:
			IVector<Object^>^ source_newValue;
			EnterStore::Commands::SortProduct^ source_newSort;
		};

		public delegate void SplashFilterChangedHandler(Object^ sender, SplashFilterChangedEventArgs^ args);

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class SplashFilterView sealed
		{
		public:
			SplashFilterView();

			property DependencyProperty^ RegionIdProperty
			{
				DependencyProperty^ get();
			}

			property int RegionId
			{
				int get();
				void set(int value);
			}

			property DependencyProperty^ CategoryIdProperty
			{
				DependencyProperty^ get();
			}

			property int CategoryId
			{
				int get();
				void set(int value);
			}

			event SplashFilterChangedHandler^ SplashFilterChanged;
		private:
			static DependencyProperty^ _RegionIdProperty;
			static DependencyProperty^ _CategoryIdProperty;
			SplashFilterViewModels^ splashFilterView;

			EventRegistrationToken loadedToken;
			EventRegistrationToken unloadedToken;

			static void OnRegionPropertyChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args);
			static void OnCategoryPropertyChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args);

			void OnLoaded(Platform::Object ^sender, Windows::UI::Xaml::RoutedEventArgs ^e);
			void OnUnloaded(Platform::Object ^sender, Windows::UI::Xaml::RoutedEventArgs ^e);
			void MultipleDataContextChanged(Windows::UI::Xaml::FrameworkElement^ sender, Windows::UI::Xaml::DataContextChangedEventArgs^ args);
			void OnPickClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
			void OnResetFilter(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

			event SplashFilterChangedHandler^ OnShpashFilterChangedHandler
			{
				EventRegistrationToken add(SplashFilterChangedHandler^ handler)
				{
					return SplashFilterChanged += handler;
				}

				void remove(EventRegistrationToken token)
				{
					SplashFilterChanged -= token;
				}

				void raise(Object^ sender, SplashFilterChangedEventArgs^ args)
				{
					SplashFilterChanged(sender, args);
				}
			}
		protected:
			virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
			virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		};
	}
}