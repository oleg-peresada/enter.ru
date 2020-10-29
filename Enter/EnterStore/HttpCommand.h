#pragma once

#include <collection.h>
#include <string>

#include "Helpers.h"

using namespace Platform;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Filters;
using namespace Windows::Web::Http::Headers;
using namespace Windows::Foundation;

namespace EnterStore
{
	template<typename T>
	struct TaskExceptionExtensions
	{
	public:
		TaskExceptionExtensions() : m_message("Error Http")
		{
		}

		TaskExceptionExtensions(String^ message) : m_message(message)
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
				throw ref new FailureException(m_message);
			}
			catch (Platform::Exception^ ex)
			{
				throw ref new FailureException(ex->Message);
			}

			return antecedent;
		}
	private:
		String^ m_message;
	};

	template<>
	concurrency::task<void> TaskExceptionExtensions<void>::operator() (concurrency::task<void> antecedent) const
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
			throw ref new FailureException("");
		}
		catch (Platform::Exception^ ex)
		{
			throw ref new FailureException(ex->Message);
		}

		return antecedent;
	}

	[Windows::Foundation::Metadata::WebHostHidden]
	ref class HttpCommand sealed
	{
	public:
		virtual ~HttpCommand();
	internal:
		HttpCommand(const std::wstring& path,
			const std::map<String^, String^>& parameter, 
			HttpMethod^ method = nullptr, 
			IHttpContent^ content = nullptr, 
			IHttpFilter^ filter = nullptr);

		property std::wstring Path
		{
			std::wstring get();
		}

		property std::map<String^, String^> Parameter
		{
			std::map<String^, String^> get();
		}

		property HttpMethod^ Method
		{
			HttpMethod^ get();
		}

		property IHttpContent^ Content
		{
			IHttpContent^ get();
		}

		property HttpCacheReadBehavior CacheReadBehavior
		{
			HttpCacheReadBehavior get();
			void set(HttpCacheReadBehavior httpValue);
		}

		property HttpCacheWriteBehavior CacheWriterBehavior
		{
			HttpCacheWriteBehavior get();
			void set(HttpCacheWriteBehavior httpValue);
		}

		property IHttpFilter^ Filter
		{
			IHttpFilter^ get();
		}

		IAsyncOperationWithProgress<HttpResponseMessage^, HttpProgress>^ SendHttpAsync(HttpRequestMessage^ requestMessage);
		IAsyncOperationWithProgress<String^, HttpProgress>^ ToCommandOperationAsync(const std::wstring& interface_name, const std::wstring& category_name);
		IAsyncOperationWithProgress<HttpResponseMessage^, HttpProgress>^ ToResponseOperationAsync(const std::wstring& interface_name, const std::wstring& category_name);
		IAsyncOperationWithProgress<String^, HttpProgress>^ ToReviewsHttpAsync(const std::wstring& interface_name, const std::wstring& category_name);
	private:
		std::wstring http_path;
		std::map<String^, String^> http_parameter;
		HttpClient^ httpClient;
		HttpMethod^ http_method;
		IHttpContent^ http_content;
		IHttpFilter^ http_filter;
		HttpCacheReadBehavior http_CacheReadBehavior;
		HttpCacheWriteBehavior http_CacheWriterBehavior;
	};
}