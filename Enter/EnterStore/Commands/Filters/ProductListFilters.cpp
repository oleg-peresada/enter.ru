#include "pch.h"
#include "ProductListFilters.h"

using namespace EnterStore;
using namespace EnterStore::Commands::Filters;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Filters;
using namespace Windows::Data::Json;

const std::wstring interface_name = L"product";
const std::wstring category_name = L"get";

ProductListFilters::ProductListFilters(IHttpFilter^ innerFilter)
{
	if (innerFilter == nullptr)
	{
		throw ref new Exception(E_INVALIDARG, "innerFilter ProductListFilters null");
	}

	source_innerFilter = innerFilter;
}

ProductListFilters::~ProductListFilters()
{
}

IAsyncOperationWithProgress<HttpResponseMessage^, HttpProgress>^ ProductListFilters::SendRequestAsync(HttpRequestMessage^ request)
{
	using namespace concurrency;

	return create_async([&](progress_reporter<HttpProgress> progress_reporter, cancellation_token token) -> task<HttpResponseMessage^>
	{
		auto operation = source_innerFilter->SendRequestAsync(request);
		return create_task(operation, token).then([&](HttpResponseMessage^ contentResponse) -> task<HttpResponseMessage^>
		{
			return create_task(contentResponse->Content->ReadAsStringAsync()).then([&](String^ content) -> task<HttpResponseMessage^>
			{
				std::map<String^, String^> queryParameter;
				queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());
				queryParameter["geo_id"] = GeoId == 0 ? "14974" : GeoId.ToString();
				bool flag = true;

				auto jsonContent = JsonObject::Parse(content);
				if (jsonContent->HasKey("result"))
				{
					auto jsonResult = jsonContent->GetNamedObject("result");
					if (jsonResult->HasKey("list"))
					{
						auto jsonListArray = jsonResult->GetNamedArray("list");

						std::wstring appendQuery;
						unsigned int size = jsonListArray->Size;
						for (unsigned int i = 0; i < size; i++)
						{
							auto element = jsonListArray->GetAt(i);

							if (!flag)
							{
								appendQuery.append(L"&id[]=");
							}
							else
							{
								flag = false;
							}
							appendQuery.append(element->GetNumber().ToString()->Data());
						}
						queryParameter["id[]"] = StringReference(appendQuery.c_str());
					}
				}

				auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter);
				auto operationHttpCommand = httpCommand->ToResponseOperationAsync(interface_name, category_name);
				return create_task(operationHttpCommand).then([](HttpResponseMessage^ responseMessage) -> HttpResponseMessage^
				{
					return responseMessage;
				}).then(TaskExceptionExtensions<HttpResponseMessage^>(), concurrency::task_continuation_context::use_current());

			}).then(TaskExceptionExtensions<HttpResponseMessage^>(), concurrency::task_continuation_context::use_current());
		}).then(TaskExceptionExtensions<HttpResponseMessage^>(), concurrency::task_continuation_context::use_current());
	});
}

int ProductListFilters::GeoId::get()
{
	return source_geoId;
}

void ProductListFilters::GeoId::set(int val)
{
	source_geoId = val;
}


SearchProductFilter::SearchProductFilter(IHttpFilter^ innerFilter, int geoId, unsigned int typeId) 
	: source_geoId(geoId), source_TypeId(typeId)
{
	if (innerFilter == nullptr)
	{
		throw ref new Exception(E_INVALIDARG, "innerFilter ProductListFilters null");
	}

	source_innerFilter = innerFilter;
}

SearchProductFilter::~SearchProductFilter()
{
}

IAsyncOperationWithProgress<HttpResponseMessage^, HttpProgress>^ SearchProductFilter::SendRequestAsync(HttpRequestMessage^ request)
{
	using namespace concurrency;

	return create_async([&](progress_reporter<HttpProgress> report, cancellation_token token) -> task<HttpResponseMessage^>
	{
		auto operationInner = source_innerFilter->SendRequestAsync(request);
		return create_task(operationInner, token).then([&](HttpResponseMessage^ messageInner) -> task<HttpResponseMessage^>
		{
			return create_task(messageInner->Content->ReadAsStringAsync()).then([&](String^ contentInner) -> task<HttpResponseMessage^>
			{
				auto searchSource = JsonObject::Parse(contentInner);
				if (searchSource->HasKey("result"))
				{
					auto resultValue = searchSource->GetNamedObject("result");
					auto objectValue = resultValue->GetNamedObject(this->TypeId.ToString());
					auto arrayData = objectValue->GetNamedArray("data");

					this->SetInnerCategory(searchSource->Stringify());

					std::map<String^, String^> queryParameter;
					queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());
					queryParameter["geo_id"] = GeoId == 0 ? "14974" : GeoId.ToString();
					bool flag = true;

					std::wstring appendQuery;
					unsigned int size = arrayData->Size;

					for (unsigned int i = 0; i < size; i++)
					{
						auto element = arrayData->GetAt(i);
						
						if (!flag)
						{
							appendQuery.append(L"&id[]=");
						}
						else
						{
							flag = false;
						}

						appendQuery.append(element->GetNumber().ToString()->Data());
					}
					queryParameter["id[]"] = StringReference(appendQuery.c_str());

					auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter);
					httpCommand->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
					auto operationHttpCommand = httpCommand->ToResponseOperationAsync(interface_name, category_name);

					return create_task(operationHttpCommand).then([&](HttpResponseMessage^ messageResponse) -> HttpResponseMessage^
					{
						return messageResponse;
					});
				}
			}, concurrency::task_continuation_context::use_current());
		});
	});
}

int SearchProductFilter::GeoId::get()
{
	return source_geoId;
}

unsigned int SearchProductFilter::TypeId::get()
{
	return source_TypeId;
}

String^ SearchProductFilter::InnerCategory::get()
{
	return source_Innercategory;
}

void SearchProductFilter::SetInnerCategory(String^ valueCategory)
{
	source_Innercategory = valueCategory;
}