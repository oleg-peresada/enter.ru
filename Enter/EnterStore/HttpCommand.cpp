#include "pch.h"
#include "HttpCommand.h"

using namespace EnterStore;

using namespace Platform;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Filters;
using namespace Windows::Web::Http::Headers;
using namespace Windows::Foundation;
using namespace Windows::Storage::Streams;
using namespace Windows::Security::Cryptography;

HttpCommand::HttpCommand(const std::wstring& path, 
	const std::map<String^, String^>& parameter, 
	HttpMethod^ method, 
	IHttpContent^ content, 
	IHttpFilter^ filter)
	: http_path(path), 
	http_parameter(parameter), 
	http_method(method), 
	http_content(content), 
	http_filter(filter),
	http_CacheReadBehavior(HttpCacheReadBehavior::Default),
	http_CacheWriterBehavior(HttpCacheWriteBehavior::Default)
{
}

HttpCommand::~HttpCommand()
{
	if (httpClient != nullptr)
	{
		delete httpClient;
	}
}

std::wstring HttpCommand::Path::get()
{
	return http_path;
}

std::map<String^, String^> HttpCommand::Parameter::get()
{
	return http_parameter;
}

HttpMethod^ HttpCommand::Method::get()
{
	if (http_method == nullptr)
	{
		return HttpMethod::Get;
	}

	return http_method;
}

IHttpContent^ HttpCommand::Content::get()
{
	return http_content;
}

HttpCacheReadBehavior HttpCommand::CacheReadBehavior::get()
{
	return http_CacheReadBehavior;
}

void HttpCommand::CacheReadBehavior::set(HttpCacheReadBehavior httpValue)
{
	http_CacheReadBehavior = httpValue;
}

HttpCacheWriteBehavior HttpCommand::CacheWriterBehavior::get()
{
	return http_CacheWriterBehavior;
}

void HttpCommand::CacheWriterBehavior::set(HttpCacheWriteBehavior httpValue)
{
	http_CacheWriterBehavior = httpValue;
}

IHttpFilter^ HttpCommand::Filter::get()
{
	if (http_filter == nullptr)
	{
		auto filter = ref new HttpBaseProtocolFilter();
		filter->AutomaticDecompression = true;

		filter->CacheControl->ReadBehavior = CacheReadBehavior;
		filter->CacheControl->WriteBehavior = CacheWriterBehavior;

		return filter;
	}

	return http_filter;
}

IAsyncOperationWithProgress<HttpResponseMessage^, HttpProgress>^ HttpCommand::SendHttpAsync(HttpRequestMessage^ requestMessage)
{
	using namespace concurrency;

	return create_async([=](progress_reporter<HttpProgress> reporter, cancellation_token token) -> task<HttpResponseMessage^>
	{
		httpClient = ref new HttpClient(this->Filter);
		httpClient->DefaultRequestHeaders->AcceptEncoding->Append(ref new HttpContentCodingWithQualityHeaderValue("gzip"));
		httpClient->DefaultRequestHeaders->AcceptEncoding->Append(ref new HttpContentCodingWithQualityHeaderValue("deflate"));

		auto operationHttp = httpClient->SendRequestAsync(requestMessage, HttpCompletionOption::ResponseContentRead);
		operationHttp->Progress = ref new AsyncOperationProgressHandler<HttpResponseMessage^, HttpProgress>
			([=](IAsyncOperationWithProgress<HttpResponseMessage^, HttpProgress>^ asyncinfo, HttpProgress progress)
		{
			reporter.report(progress);
		});

		return create_task(operationHttp, token).then([=](HttpResponseMessage^ message) -> HttpResponseMessage^
		{
			return message;

		}, task_continuation_context::use_current()).then(TaskExceptionExtensions<HttpResponseMessage^>(), task_continuation_context::use_current());
	});
}

IAsyncOperationWithProgress<String^, HttpProgress>^ HttpCommand::ToCommandOperationAsync(const std::wstring& interface_name, const std::wstring& category_name)
{
	using namespace concurrency;
	return create_async([&](progress_reporter<HttpProgress> progress_reporter, cancellation_token token) -> task<String^>
	{
		std::wstring queryHttpCommand(L"http://");
		queryHttpCommand.append(Path);
		queryHttpCommand.append(L"/v2/");
		queryHttpCommand.append(interface_name);
		queryHttpCommand.append(L"/");
		queryHttpCommand.append(category_name);

		if (Parameter.size() > 0)
		{
			queryHttpCommand.append(L"?");
			queryHttpCommand.append(Helpers::ForQuery(Parameter));
		}
		else
		{
			queryHttpCommand.append(L"/");
		}

		auto request_message = ref new HttpRequestMessage(this->Method, ref new Uri(StringReference(queryHttpCommand.c_str())));
		if (this->Method != HttpMethod::Get && this->Content != nullptr)
		{
			request_message->Content = this->Content;
		}

		auto operation = SendHttpAsync(request_message);
		operation->Progress = ref new AsyncOperationProgressHandler<HttpResponseMessage^, HttpProgress>
			([=](IAsyncOperationWithProgress<HttpResponseMessage^, HttpProgress>^ asyncinfo, HttpProgress progress)
		{
			progress_reporter.report(progress);
		});

		return create_task(operation, token).then([=](HttpResponseMessage^ message) -> task<String^>
		{
			return create_task(message->Content->ReadAsBufferAsync()).then([=](IBuffer^ content) -> String^
			{
				return CryptographicBuffer::ConvertBinaryToString(BinaryStringEncoding::Utf8, content);

			}).then(TaskExceptionExtensions<String^>(), task_continuation_context::use_current());

		}, task_continuation_context::use_current()).then(TaskExceptionExtensions<String^>(), task_continuation_context::use_current());
	});
}

IAsyncOperationWithProgress<HttpResponseMessage^, HttpProgress>^ HttpCommand::ToResponseOperationAsync(const std::wstring& interface_name, const std::wstring& category_name)
{
	using namespace concurrency;
	return create_async([&](progress_reporter<HttpProgress> progress_reporter, cancellation_token token) -> task<HttpResponseMessage^>
	{
		std::wstring queryHttpCommand(L"http://");
		queryHttpCommand.append(Path);
		queryHttpCommand.append(L"/v2/");
		queryHttpCommand.append(interface_name);
		queryHttpCommand.append(L"/");
		queryHttpCommand.append(category_name);

		if (Parameter.size() > 0)
		{
			queryHttpCommand.append(L"?");
			queryHttpCommand.append(Helpers::ForQuery(Parameter));
		}
		else
		{
			queryHttpCommand.append(L"/");
		}

		auto request_message = ref new HttpRequestMessage(this->Method, ref new Uri(StringReference(queryHttpCommand.c_str())));
		if (this->Method != HttpMethod::Get && this->Content != nullptr)
		{
			request_message->Content = this->Content;
		}

		auto operation = SendHttpAsync(request_message);
		operation->Progress = ref new AsyncOperationProgressHandler<HttpResponseMessage^, HttpProgress>
			([=](IAsyncOperationWithProgress<HttpResponseMessage^, HttpProgress>^ asyncinfo, HttpProgress progress)
		{
			progress_reporter.report(progress);
		});

		return create_task(operation, token).then([&](HttpResponseMessage^ message) -> HttpResponseMessage^
		{
			return message;

		}, task_continuation_context::use_current()).then(TaskExceptionExtensions<HttpResponseMessage^>(), task_continuation_context::use_current());
	});
}

IAsyncOperationWithProgress<String^, HttpProgress>^ HttpCommand::ToReviewsHttpAsync(const std::wstring& interface_name, const std::wstring& category_name)
{
	using namespace concurrency;
	return create_async([&](progress_reporter<HttpProgress> progress_reporter, cancellation_token token) -> task<String^>
	{
		std::wstring queryHttpCommand(L"http://");
		queryHttpCommand.append(Path);
		queryHttpCommand.append(L"/");
		queryHttpCommand.append(interface_name);
		queryHttpCommand.append(L"/");
		queryHttpCommand.append(category_name);

		if (Parameter.size() > 0)
		{
			queryHttpCommand.append(L"?");
			queryHttpCommand.append(Helpers::ForQuery(Parameter));
		}
		else
		{
			queryHttpCommand.append(L"/");
		}

		auto request_message = ref new HttpRequestMessage(this->Method, ref new Uri(StringReference(queryHttpCommand.c_str())));
		if (this->Method != HttpMethod::Get && this->Content != nullptr)
		{
			request_message->Content = this->Content;
		}

		auto operation = SendHttpAsync(request_message);
		operation->Progress = ref new AsyncOperationProgressHandler<HttpResponseMessage^, HttpProgress>
			([=](IAsyncOperationWithProgress<HttpResponseMessage^, HttpProgress>^ asyncinfo, HttpProgress progress)
		{
			progress_reporter.report(progress);
		});

		return create_task(operation, token).then([=](HttpResponseMessage^ message) -> task<String^>
		{
			return create_task(message->Content->ReadAsBufferAsync()).then([=](IBuffer^ content) -> String^
			{
				return CryptographicBuffer::ConvertBinaryToString(BinaryStringEncoding::Utf8, content);

			}).then(TaskExceptionExtensions<String^>(), task_continuation_context::use_current());

		}, task_continuation_context::use_current()).then(TaskExceptionExtensions<String^>(), task_continuation_context::use_current());
	});
}