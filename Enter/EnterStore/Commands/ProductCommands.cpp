#include "pch.h"
#include "ProductCommands.h"

using namespace EnterStore;
using namespace EnterStore::Commands;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Data::Json;

const std::wstring interface_name = L"product";
const std::wstring category_name = L"get";

ProductCommands::ProductCommands(IVector<int>^ id_product, int geo_id) : m_product(id_product), m_geoId(geo_id)
{
}

IAsyncOperationWithProgress<IObservableVector<ProductCardModels^>^, HttpProgress>^ ProductCommands::ProductsAsync()
{
	return this->ProductsAsync(false);
}

IAsyncOperationWithProgress<IObservableVector<ProductCardModels^>^, HttpProgress>^ ProductCommands::ProductsAsync(bool isCached)
{
	using namespace concurrency;

	return create_async([this, isCached](progress_reporter<HttpProgress> reporter, cancellation_token token) -> task<IObservableVector<ProductCardModels^>^>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());
		queryParameter["geo_id"] = m_geoId.ToString();

		std::wstring id_concat;
		for (unsigned int i = 0; i < Product->Size; i++)
		{
			int element = Product->GetAt(i);
			if (i > 0)
			{
				id_concat.append(L"id[]=");
			}

			id_concat.append(element.ToString()->Data());
			id_concat.append(L"&");
		}

		queryParameter["id[]"] = StringReference(id_concat.c_str());

		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter);
		httpCommand->CacheReadBehavior = isCached == false ? HttpCacheReadBehavior::Default : HttpCacheReadBehavior::MostRecent;
		auto operation = httpCommand->ToCommandOperationAsync(interface_name, category_name);

		operation->Progress = ref new AsyncOperationProgressHandler<String^, HttpProgress>([=](
			IAsyncOperationWithProgress<String^, HttpProgress>^ asyncInfo, HttpProgress progress)
		{
			reporter.report(progress);
		});

		return create_task(operation, token).then([&](String^ content) -> IObservableVector<ProductCardModels^>^
		{
			auto vect = ref new Vector<ProductCardModels^>();
			auto contentJson = JsonObject::Parse(content);
			if (contentJson->HasKey("result") && contentJson->GetNamedValue("result")->ValueType == JsonValueType::Array)
			{
				auto arrayResult = contentJson->GetNamedArray("result");
				for (const auto &item : arrayResult)
				{
					auto element = item->GetObject();
					auto productCard = ref new ProductCardModels(element->HasKey("id") ? Helpers::ToNumber(element->GetNamedValue("id")) : 0,
						element->HasKey("name") ? Helpers::ToString(element->GetNamedValue("name")) : "",
						element->HasKey("token") ? Helpers::ToString(element->GetNamedValue("token")) : "",
						element->HasKey("article") ? Helpers::ToString(element->GetNamedValue("article")) : "",
						element->HasKey("bar_code") ? Helpers::ToString(element->GetNamedValue("bar_code")) : "",
						element->HasKey("announce") ? Helpers::ToString(element->GetNamedValue("announce")) : "",
						element->HasKey("rating") ? Helpers::ToString(element->GetNamedValue("rating")) : "",
						element->HasKey("price") ? Helpers::ToNumber(element->GetNamedValue("price")) : 0.0,
						element->HasKey("media_image") ? Helpers::ToString(element->GetNamedValue("media_image")) : "");

					auto vectPromo = ref new Vector<PromoCard^>();
					if (element->HasKey("label"))
					{
						if (element->GetNamedValue("label")->ValueType == JsonValueType::Array)
						{
							auto promoArray = element->GetNamedArray("label");
							unsigned int size = promoArray->Size;

							for (unsigned int i = 0; i < size; i++)
							{
								auto elementPromo = promoArray->GetAt(i)->GetObject();

								auto promoLabel = ref new PromoCard(elementPromo->HasKey("id") ? Helpers::ToNumber(elementPromo->GetNamedValue("id")) : 0,
									elementPromo->HasKey("name") ? Helpers::ToString(elementPromo->GetNamedValue("name")) : "",
									elementPromo->HasKey("media_image") ? Helpers::ToString(elementPromo->GetNamedValue("media_image")) : "");
								vectPromo->Append(promoLabel);
							}
						}
					}

					if (element->HasKey("state"))
					{
						if (element->GetNamedObject("state")->ValueType == JsonValueType::Object)
						{
							auto stateElement = element->GetNamedObject("state");
							auto stateCard = ref new StateCard(stateElement->HasKey("is_buyable") ? Helpers::ToBool(stateElement->GetNamedValue("is_buyable")) : false);

							productCard->State = stateCard;
						}
					}
					else
					{
						productCard->State = ref new StateCard(false);
					}

					productCard->LabelCard = vectPromo;
					vect->Append(productCard);
				}
			}

			return vect;
		}, task_continuation_context::use_current()).then(TaskExceptionExtensions<IObservableVector<ProductCardModels^>^>());
	});
}

IVector<int>^ ProductCommands::Product::get()
{
	return m_product;
}

int ProductCommands::GeoId::get()
{
	return m_geoId;
}