#include "pch.h"
#include "Helpers.h"

using namespace Enter;
using namespace Enter::View;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::Storage::Streams;
using namespace Microsoft::ApplicationInsights::Telemetry::WindowsStore;

bool Helpers::IsNumberToString(String^ valueNumber)
{
	for (const char &item : valueNumber)
	{
		if (!isdigit(item))
		{
			return false;
		}
	}

	return true;
}

void Helpers::SearchSubmitted(SearchBox^ sender, SearchBoxQuerySubmittedEventArgs^ args)
{
	auto queryText = args->QueryText;
	if (queryText == nullptr || queryText->Length() < 2) return;

	Frame^ currentFrame = dynamic_cast<Frame^>(Window::Current->Content);
	if (currentFrame != nullptr)
	{
		currentFrame->Navigate(SearchView::typeid, queryText);
	}
}

void Helpers::SearchSuggestionChosen(SearchBox^ sender, SearchBoxResultSuggestionChosenEventArgs^ args)
{
	auto tag = args->Tag;
	if (tag == nullptr) return;

	Frame^ currentFrame = dynamic_cast<Frame^>(Window::Current->Content);
	if (currentFrame != nullptr)
	{
		std::string tag_str(begin(tag), end(tag));
		int result_id = 0;

		std::istringstream stream(tag_str);
		stream >> result_id;

		currentFrame->Navigate(ProductExtensionsView::typeid, result_id);
	}
}

DateTime Helpers::StringToDateTime(String^ dateTime)
{
	std::string strDate(begin(dateTime), end(dateTime));
	std::istringstream dateStream(strDate);

	auto calendar = ref new Windows::Globalization::Calendar();

	int year = 0;
	dateStream >> year;
	calendar->Year = year;
	dateStream.ignore(1, '-');

	int month = 0;
	dateStream >> month;
	calendar->Month = month;
	dateStream.ignore(1, '-');

	int day = 0;
	dateStream >> day;
	calendar->Day = day;

	return calendar->GetDateTime();
}

double Helpers::ToStringNumber(String^ val)
{
	std::string conversation(begin(val), end(val));
	double result = 0.0;
	std::istringstream(conversation) >> result;
	return result;
}

void Helpers::LogPage(String^ pathPage)
{
	try
	{
		ClientAnalyticsChannel::Default->LogPageView(pathPage);
	}
	catch (Exception^)
	{
	}
	catch (std::exception&)
	{
	}
}

void Helpers::LogEvent(String^ eventName)
{
	try
	{
		ClientAnalyticsChannel::Default->LogEvent(eventName);
	}
	catch (Exception^)
	{
	}
	catch (std::exception&)
	{
	}
}