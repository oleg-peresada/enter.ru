//
// CitiesMenuControl.xaml.h
// Объявление класса CitiesMenuControl
//

#pragma once

#include "Controls\CitiesMenuControl.g.h"
#include "DataModel\Storage\AutorizationStorage.h"

using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Search;

namespace Enter
{
	namespace Controls
	{
		public delegate void CityInfoHandler(Object^ sender, String^ name);

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class CitiesMenuControl sealed
		{
		public:
			CitiesMenuControl();
			event CityInfoHandler^ CityInfo;

			event CityInfoHandler^ OnEventCityInfoHandler
			{
				EventRegistrationToken add(CityInfoHandler^ info)
				{
					return CityInfo += info;
				}

				void remove(EventRegistrationToken token)
				{
					CityInfo -= token;
				}

				void raise(Object^ sender, String^ name)
				{
					CityInfo(sender, name);
				}
			}
		private:
			std::vector<AutoCityModels^> ContentCity;

			void OnSaveClick(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
			void OnCityInfo(String^ name);
			void OnQuerySubmitted(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxQuerySubmittedEventArgs^ args);
			void OnResultSuggestionChosen(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxResultSuggestionChosenEventArgs^ args);
			void OnSuggestionsRequested(Windows::UI::Xaml::Controls::SearchBox^ sender, Windows::UI::Xaml::Controls::SearchBoxSuggestionsRequestedEventArgs^ args);
		};
	}
}
