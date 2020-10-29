#include "pch.h"
#include "ProductExtensionsListCommands.h"

using namespace EnterStore;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Filters;
using namespace Windows::Data::Json;

const std::wstring interface_name = L"product";
const std::wstring category_name = L"get";

std::map<String^, String^> parameterQuery;

ProductExtensionsListCommands::ProductExtensionsListCommands(String^ parameter, int geoId, ProductExtensionsType parameterType)
	: source_parameter(parameter), source_geoId(geoId), source_parameterType(parameterType)
{
	parameterQuery["client_id"] = StringReference(Helpers::standartClientId.c_str());
	parameterQuery["geo_id"] = geoId.ToString();

	switch (parameterType)
	{
	case ProductExtensionsType::Id:
		parameterQuery["id[]"] = parameter;
		break;
	case ProductExtensionsType::Slug:
		parameterQuery["slug[]"] = parameter;
		break;
	case ProductExtensionsType::BarCode:
		parameterQuery["bar_code[]"] = parameter;
		break;
	case ProductExtensionsType::Article:
		parameterQuery["article[]"] = parameter;
		break;
	case ProductExtensionsType::Ean:
		parameterQuery["ean[]"] = parameter;
		break;
	}
}

IAsyncOperationWithProgress<ProductExtensionsCardModels^, HttpProgress>^ ProductExtensionsListCommands::ProductExtensionsAsync(bool isCached)
{
	using namespace concurrency;

	return create_async([&](progress_reporter<HttpProgress> reporter, cancellation_token token)-> task<ProductExtensionsCardModels^>
	{
		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, parameterQuery);
		httpCommand->CacheReadBehavior = isCached == false ? HttpCacheReadBehavior::Default : HttpCacheReadBehavior::MostRecent;
		auto operation = httpCommand->ToCommandOperationAsync(interface_name, category_name);

		operation->Progress = ref new AsyncOperationProgressHandler<String^, HttpProgress>([=](
			IAsyncOperationWithProgress<String^, HttpProgress>^ asyncInfo, HttpProgress progress)
		{
			reporter.report(progress);
		});

		return create_task(operation, token).then([&](String^ content) -> ProductExtensionsCardModels^
		{
			auto jsonContent = JsonObject::Parse(content);
			
			if (jsonContent->HasKey("result") && jsonContent->GetNamedValue("result")->ValueType == JsonValueType::Array)
			{
				auto jsonResult = jsonContent->GetNamedArray("result");
				if (jsonResult->Size == 0) return nullptr;

				auto resultValue = jsonResult->GetAt(0)->GetObject();

				auto productModel = ref new ProductExtensionsCardModels(resultValue->HasKey("id") ? Helpers::ToNumber(resultValue->GetNamedValue("id")) : 0,
					resultValue->HasKey("type_id") ? Helpers::ToNumber(resultValue->GetNamedValue("type_id")) : 0,
					resultValue->HasKey("name") ? Helpers::ToString(resultValue->GetNamedValue("name")) : "",
					resultValue->HasKey("token") ? Helpers::ToString(resultValue->GetNamedValue("token")) : "",
					resultValue->HasKey("article") ? Helpers::ToString(resultValue->GetNamedValue("article")) : "",
					resultValue->HasKey("description") ? Helpers::ToString(resultValue->GetNamedValue("description")) : "",
					resultValue->HasKey("price") ? Helpers::ToNumber(resultValue->GetNamedValue("price")) : 0,
					resultValue->HasKey("price_old") ? Helpers::ToNumber(resultValue->GetNamedValue("price_old")) : 0,
					resultValue->HasKey("media_image") ? Helpers::ToString(resultValue->GetNamedValue("media_image")) : "");

				auto accessories = ref new Vector<int>();
				if (resultValue->HasKey("accessories"))
				{
					if (resultValue->GetNamedValue("accessories")->ValueType == JsonValueType::Array)
					{
						auto accessoriesValue = resultValue->GetNamedArray("accessories");

						unsigned int size_a = accessoriesValue->Size;
						for (unsigned int i = 0; i < size_a; i++)
						{
							int num = Helpers::ToNumber(accessoriesValue->GetAt(i));
							accessories->Append(num);
						}
					}
				}
				productModel->Accessories = accessories;

				auto vectProperty = ref new Vector<PropertyExtensionsCardModels^>();
				if (resultValue->HasKey("property"))
				{
					if (resultValue->GetNamedValue("property")->ValueType == JsonValueType::Array)
					{
						auto propertyArray = resultValue->GetNamedArray("property");
						for (const auto &itemProperty : propertyArray)
						{
							auto propertyValue = itemProperty->GetObject();
							auto propertyModel = ref new PropertyExtensionsCardModels(propertyValue->HasKey("id") ? Helpers::ToNumber(propertyValue->GetNamedValue("id")) : 0,
								propertyValue->HasKey("group_id") ? Helpers::ToNumber(propertyValue->GetNamedValue("group_id")) : 0,
								propertyValue->HasKey("type_id") ? Helpers::ToNumber(propertyValue->GetNamedValue("type_id")) : 0,
								propertyValue->HasKey("name") ? Helpers::ToString(propertyValue->GetNamedValue("name")) : "",
								propertyValue->HasKey("hint") ? Helpers::ToString(propertyValue->GetNamedValue("hint")) : "",
								propertyValue->HasKey("value") ? Helpers::ToString(propertyValue->GetNamedValue("value")) : "",
								propertyValue->HasKey("value_hint") ? Helpers::ToString(propertyValue->GetNamedValue("value_hint")) : "",
								propertyValue->HasKey("unit") ? Helpers::ToString(propertyValue->GetNamedValue("unit")) : "");

							if (propertyValue->HasKey("option"))
							{
								if (propertyValue->GetNamedValue("option")->ValueType == JsonValueType::Array)
								{
									auto vectOption = ref new Vector<OptionExtensionsCardModels^>();
									auto optionArray = propertyValue->GetNamedArray("option");
									for (const auto &itemOption : optionArray)
									{
										auto optionValue = itemOption->GetObject();
										auto optionModel = ref new OptionExtensionsCardModels(optionValue->HasKey("id") ? Helpers::ToNumber(optionValue->GetNamedValue("id")) : 0,
											optionValue->HasKey("value") ? Helpers::ToString(optionValue->GetNamedValue("value")) : "",
											optionValue->HasKey("hint") ? Helpers::ToString(optionValue->GetNamedValue("hint")) : "");
										vectOption->Append(optionModel);
									}

									propertyModel->Option = vectOption;
								}
							}
							else
							{
								propertyModel->Option = ref new Vector<OptionExtensionsCardModels^>();
							}

							vectProperty->Append(propertyModel);
						}
					}
				}

				auto vectPropertyGroup = ref new Vector<PropertyGroupExetensionsModels^>();
				if (resultValue->HasKey("property_group"))
				{
					if (resultValue->GetNamedValue("property_group")->ValueType == JsonValueType::Array)
					{
						auto propertyGroupArray = resultValue->GetNamedArray("property_group");
						for (const auto &itemGroup : propertyGroupArray)
						{
							auto propertyItem = itemGroup->GetObject();

							auto propertyGroupModel = ref new PropertyGroupExetensionsModels(propertyItem->HasKey("id") ? Helpers::ToNumber(propertyItem->GetNamedValue("id")) : 0,
								propertyItem->HasKey("name") ? Helpers::ToString(propertyItem->GetNamedValue("name")) : "",
								propertyItem->HasKey("position") ? Helpers::ToNumber(propertyItem->GetNamedValue("position")) : 0);
							vectPropertyGroup->Append(propertyGroupModel);
						}
					}
				}

				auto vectPromoLabel = ref new Vector<PromoLabel^>();
				if (resultValue->HasKey("label"))
				{
					if (resultValue->GetNamedValue("label")->ValueType == JsonValueType::Array)
					{
						auto labelArray = resultValue->GetNamedArray("label");
						for (const auto &item : labelArray)
						{
							auto itemLabel = item->GetObject();

							auto promoLabelModel = ref new PromoLabel(itemLabel->HasKey("id") ? Helpers::ToNumber(itemLabel->GetNamedValue("id")) : 0,
								itemLabel->HasKey("media_image") ? Helpers::ToString(itemLabel->GetNamedValue("media_image")) : "",
								itemLabel->HasKey("name") ? Helpers::ToString(itemLabel->GetNamedValue("name")) : "");
							vectPromoLabel->Append(promoLabelModel);
						}
					}
				}

				auto vectMedia = ref new Vector<MediaExtensionsCardModels^>();
				if (resultValue->HasKey("media"))
				{
					if (resultValue->GetNamedValue("media")->ValueType == JsonValueType::Array)
					{
						auto mediaArray = resultValue->GetNamedArray("media");
						for (const auto &itemMedia : mediaArray)
						{
							auto mediaValue = itemMedia->GetObject();

							auto mediaModel = ref new MediaExtensionsCardModels(mediaValue->HasKey("id") ? Helpers::ToNumber(mediaValue->GetNamedValue("id")) : 0,
								mediaValue->HasKey("source") ? Helpers::ToString(mediaValue->GetNamedValue("source")) : "");
							vectMedia->Append(mediaModel);
						}
					}
				}

				auto vectModelProperty = ref new Vector<PropertyViewTypeModel^>();
				if (resultValue->HasKey("model"))
				{
					if (resultValue->GetNamedValue("model")->ValueType == JsonValueType::Object)
					{
						auto modelResult = resultValue->GetNamedObject("model");
						if (modelResult->HasKey("property"))
						{
							if (modelResult->GetNamedValue("property")->ValueType == JsonValueType::Array)
							{
								auto propertyModel = modelResult->GetNamedArray("property");
								for (const auto &item : propertyModel)
								{
									auto itemProperty = item->GetObject();

									auto vectOption = ref new Vector<OptionViewTypeModel^>();
									if (itemProperty->HasKey("option"))
									{
										if (itemProperty->GetNamedValue("option")->ValueType == JsonValueType::Array)
										{
											auto optionResult = itemProperty->GetNamedArray("option");
											for (const auto &itemOption : optionResult)
											{
												auto elementOption = itemOption->GetObject();

												if (elementOption->HasKey("product"))
												{
													if (elementOption->GetNamedValue("product")->ValueType == JsonValueType::Object)
													{
														auto productItem = elementOption->GetNamedObject("product");

														auto productView = ref new ProductViewTypeModel(productItem->HasKey("id") ? Helpers::ToNumber(productItem->GetNamedValue("id")) : 0,
															productItem->HasKey("name") ? Helpers::ToString(productItem->GetNamedValue("name")) : "",
															productItem->HasKey("token") ? Helpers::ToString(productItem->GetNamedValue("token")) : "",
															productItem->HasKey("media_image") ? Helpers::ToString(productItem->GetNamedValue("media_image")) : "");

														auto optionModel = ref new OptionViewTypeModel(elementOption->HasKey("value") ? Helpers::ToString(elementOption->GetNamedValue("value")) : "", productView);
														vectOption->InsertAt(0, optionModel);
													}
												}
											}
										}
									}

									vectModelProperty->Append(ref new PropertyViewTypeModel(itemProperty->HasKey("id") ? Helpers::ToNumber(itemProperty->GetNamedValue("id")) : 0,
										itemProperty->HasKey("type_id") ? Helpers::ToNumber(itemProperty->GetNamedValue("type_id")) : 0,
										itemProperty->HasKey("name") ? Helpers::ToString(itemProperty->GetNamedValue("name")) : "",
										itemProperty->HasKey("unit") ? Helpers::ToString(itemProperty->GetNamedValue("unit")) : "",
										itemProperty->HasKey("is_multiple") ? Helpers::ToBool(itemProperty->GetNamedValue("is_multiple")) : true,
										vectOption));
								}
							}
						}
					}
				}

				if (resultValue->HasKey("state"))
				{
					if (resultValue->GetNamedValue("state")->ValueType == JsonValueType::Object)
					{
						auto stateValue = resultValue->GetNamedObject("state");
						auto stateModel = ref new StateCardModels(stateValue->HasKey("is_shop") ? Helpers::ToBool(stateValue->GetNamedValue("is_shop")) : false,
							stateValue->HasKey("is_shop") ? Helpers::ToBool(stateValue->GetNamedValue("is_shop")) : false,
							stateValue->HasKey("is_buyable") ? Helpers::ToBool(stateValue->GetNamedValue("is_buyable")) : false);
						productModel->State = stateModel;
					}
				}
				else
				{
					productModel->State = ref new StateCardModels(false, false, false);
				}

				if (resultValue->HasKey("stock"))
				{
					if (resultValue->GetNamedValue("stock")->ValueType == JsonValueType::Array)
					{
						auto stockArray = resultValue->GetNamedArray("stock");
						if (stockArray->Size != 0)
						{
							auto stockValue = stockArray->GetObjectAt(0);
							auto stockModel = ref new StockCardModels(stockValue->HasKey("store_id") ? Helpers::ToNumber(stockValue->GetNamedValue("store_id")) : 0,
								stockValue->HasKey("shop_id") ? Helpers::ToNumber(stockValue->GetNamedValue("shop_id")) : 0,
								stockValue->HasKey("quantity") ? Helpers::ToNumber(stockValue->GetNamedValue("quantity")) : 0);
							productModel->Stock = stockModel;
						}
						else
						{
							productModel->Stock = ref new StockCardModels(0, 0, 0);
						}
					}
					else if (resultValue->GetNamedValue("stock")->ValueType == JsonValueType::Object)
					{
						auto stockValue = resultValue->GetNamedObject("stock");
						if (stockValue->Size > 0)
						{
							auto stockModel = ref new StockCardModels(stockValue->HasKey("store_id") ? Helpers::ToNumber(stockValue->GetNamedValue("store_id")) : 0,
								stockValue->HasKey("shop_id") ? Helpers::ToNumber(stockValue->GetNamedValue("shop_id")) : 0,
								stockValue->HasKey("quantity") ? Helpers::ToNumber(stockValue->GetNamedValue("quantity")) : 0);
							productModel->Stock = stockModel;
						}
						else
						{
							productModel->Stock = ref new StockCardModels(0, 0, 0);
						}
					}
				}
				else
				{
					productModel->Stock = ref new StockCardModels(0, 0, 0);
				}

				productModel->Property = vectProperty;
				productModel->Label = vectPromoLabel;
				productModel->Media = vectMedia;
				productModel->ModelProperty = vectModelProperty;
				productModel->PropertyGroup = vectPropertyGroup;

				return productModel;
			}
			else
			{
				return nullptr;
			}

		}, task_continuation_context::use_current())
			.then(TaskExceptionExtensions<ProductExtensionsCardModels^>(), 
			task_continuation_context::use_current());
	});
}

String^ ProductExtensionsListCommands::Parameter::get()
{
	return source_parameter;
}

int ProductExtensionsListCommands::GeoId::get()
{
	return source_geoId;
}

ProductExtensionsType ProductExtensionsListCommands::ParameterType::get()
{
	return source_parameterType;
}