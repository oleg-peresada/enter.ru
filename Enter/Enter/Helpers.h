#pragma once

#include <string>
#include <ctype.h>
#include <sstream>

#include "View\SearchView.xaml.h"
#include "View\ProductExtensionsView.xaml.h"

using namespace Platform;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Media;

namespace Enter
{
	class Finally
	{
	public:
		Finally(std::function<void()> f) : finallyClause(f) {}
		~Finally()
		{
			finallyClause();
		}

	private:
		std::function<void()> finallyClause;
	};

	template<typename T>
	struct TaskException
	{
	public:
		TaskException() : m_platformException(nullptr)
		{
		}

		TaskException(std::function<void(Object^)> platformException) : m_platformException(platformException)
		{
		}

		concurrency::task<T> operator() (concurrency::task<T> antecedent) const
		{
			T result;
			try
			{
				result = antecedent.get();
			}
			catch (const concurrency::task_canceled&)
			{
			}
			catch (const std::exception&)
			{
			}
			catch (Platform::Exception^ ex)
			{
				if (m_platformException != nullptr)
				{
					m_platformException(ex->Message);
				}
			}

			return antecedent;
		}
	private:
		std::function<void(Object^)> m_platformException;
	};

	concurrency::task<void> TaskException<void>::operator() (concurrency::task<void> antecedent) const
	{
		try
		{
			antecedent.get();
		}
		catch (const concurrency::task_canceled&)
		{
		}
		catch (const std::exception&)
		{
		}
		catch (Platform::Exception^ ex)
		{
		}

		return antecedent;
	}

	static class Helpers
	{
	public:
		static bool IsNumberToString(String^ valueNumber);
		static void SearchSubmitted(SearchBox^ sender, SearchBoxQuerySubmittedEventArgs^ args);
		static void SearchSuggestionChosen(SearchBox^ sender, SearchBoxResultSuggestionChosenEventArgs^ args);
		static DateTime StringToDateTime(String^ dateTime);
		static double ToStringNumber(String^ val);

		template<typename T>
		static T GetVisualChild(DependencyObject^ parent)
		{
			if (parent == nullptr) return dynamic_cast<T>(parent);

			auto parentChild = dynamic_cast<T>(parent);
			if (parentChild != nullptr) return parentChild;

			DependencyObject^ element = nullptr;
			int count = VisualTreeHelper::GetChildrenCount(parent);

			for (int i = 0; i < count; i++)
			{
				element = GetVisualChild<T>(VisualTreeHelper::GetChild(parent, i));

				if (element != nullptr) return dynamic_cast<T>(element);
			}
		}

		static void LogPage(String^ pathPage);
		static void LogEvent(String^ nameEvent);
	};
}