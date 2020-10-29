#include "pch.h"
#include "CategoryTreeCommands.h"

using namespace EnterStore;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Data::Json;

const std::wstring interface_name = L"category";
const std::wstring category_name = L"tree";

CategoryTreeCommands::CategoryTreeCommands(unsigned int rootId, unsigned int maxLevel, unsigned int regionId, bool loadParents)
	: tree_rootId(rootId), tree_maxLevel(maxLevel), tree_regionId(regionId), tree_loadParents(loadParents)
{
}

unsigned int CategoryTreeCommands::RootId::get()
{
	return tree_rootId;
}

unsigned int CategoryTreeCommands::MaxLevel::get()
{
	return tree_maxLevel;
}

unsigned int CategoryTreeCommands::RegionId::get()
{
	return tree_regionId;
}

bool CategoryTreeCommands::IsLoadParents::get()
{
	return tree_loadParents;
}

IAsyncOperationWithProgress<IVector<CategoryTreeModels^>^, HttpProgress>^ CategoryTreeCommands::CategoryTreeCommandAsync()
{
	return this->CategoryTreeCommandAsync(false);
}

IAsyncOperationWithProgress<IVector<CategoryTreeModels^>^, HttpProgress>^ CategoryTreeCommands::CategoryTreeCommandAsync(bool isCached)
{
	using namespace concurrency;

	std::map<String^, String^> parameter_query;
	parameter_query["root_id"] = RootId.ToString();
	parameter_query["max_level"] = MaxLevel.ToString();
	parameter_query["region_id"] = RegionId.ToString();
	parameter_query["is_load_parents"] = IsLoadParents.ToString();

	return create_async([&](progress_reporter<HttpProgress> reporter, cancellation_token token) -> task<IVector<CategoryTreeModels^>^>
	{
		auto command = ref new HttpCommand(Helpers::standartQueryCommand, parameter_query);
		command->CacheReadBehavior = isCached == false ? Windows::Web::Http::Filters::HttpCacheReadBehavior::Default : Windows::Web::Http::Filters::HttpCacheReadBehavior::MostRecent;
		auto operationCommand = command->ToCommandOperationAsync(interface_name, category_name);

		return create_task(operationCommand, token).then([](String^ content) -> IVector<CategoryTreeModels^> ^
		{
			auto vect = ref new Vector<CategoryTreeModels^>();
			auto jsonObject = JsonObject::Parse(content);
			
			if (jsonObject->HasKey("result") && jsonObject->GetNamedValue("result")->ValueType == JsonValueType::Array)
			{
				auto resultArray = jsonObject->GetNamedArray("result");
				for (const auto &itemResult : resultArray)
				{
					auto resultValue = itemResult->GetObject();
					auto resultModel = ref new CategoryTreeModels(resultValue->HasKey("id") ? Helpers::ToNumber(resultValue->GetNamedValue("id")) : 0.0,
						resultValue->HasKey("parent_id") ? Helpers::ToString(resultValue->GetNamedValue("parent_id")) : "",
						resultValue->HasKey("is_furniture") ? Helpers::ToBool(resultValue->GetNamedValue("is_furniture")) : false,
						resultValue->HasKey("name") ? Helpers::ToString(resultValue->GetNamedValue("name")) : "",
						resultValue->HasKey("token") ? Helpers::ToString(resultValue->GetNamedValue("token")) : "",
						resultValue->HasKey("media_image") ? Helpers::ToString(resultValue->GetNamedValue("media_image")) : "",
						resultValue->HasKey("level") ? Helpers::ToNumber(resultValue->GetNamedValue("level")) : 0.0,
						resultValue->HasKey("seo_header") ? Helpers::ToString(resultValue->GetNamedValue("seo_header")) : "",
						resultValue->HasKey("product_count") ? Helpers::ToString(resultValue->GetNamedValue("product_count")) : "",
						resultValue->HasKey("product_count_global") ? Helpers::ToString(resultValue->GetNamedValue("product_count_global")) : "",
						resultValue->HasKey("has_children") ? Helpers::ToBool(resultValue->GetNamedValue("has_children")) : false);

					auto vectChildren = ref new Vector<CategoryTreeModels^>();
					if (resultValue->HasKey("children") && resultValue->GetNamedValue("children")->ValueType == JsonValueType::Array)
					{
						auto childrenArray = resultValue->GetNamedArray("children");
						for (const auto &itemChildren : childrenArray)
						{
							auto childrenValue = itemChildren->GetObject();
							auto categoryModel = ref new CategoryTreeModels(childrenValue->HasKey("id") ? Helpers::ToNumber(childrenValue->GetNamedValue("id")) : 0.0,
								childrenValue->HasKey("parent_id") ? Helpers::ToString(childrenValue->GetNamedValue("parent_id")) : "",
								childrenValue->HasKey("is_furniture") ? Helpers::ToBool(childrenValue->GetNamedValue("is_furniture")) : false,
								childrenValue->HasKey("name") ? Helpers::ToString(childrenValue->GetNamedValue("name")) : "",
								childrenValue->HasKey("token") ? Helpers::ToString(childrenValue->GetNamedValue("token")) : "",
								childrenValue->HasKey("media_image") ? Helpers::ToString(childrenValue->GetNamedValue("media_image")) : "",
								childrenValue->HasKey("level") ? Helpers::ToNumber(childrenValue->GetNamedValue("level")) : 0.0,
								childrenValue->HasKey("seo_header") ? Helpers::ToString(childrenValue->GetNamedValue("seo_header")) : "",
								childrenValue->HasKey("product_count") ? Helpers::ToString(childrenValue->GetNamedValue("product_count")) : "",
								childrenValue->HasKey("product_count_global") ? Helpers::ToString(childrenValue->GetNamedValue("product_count_global")) : "",
								childrenValue->HasKey("has_children") ? Helpers::ToBool(childrenValue->GetNamedValue("has_children")) : false);

							auto vectCategoryChildren = ref new Vector<CategoryTreeModels^>();
							if (childrenValue->HasKey("children") && childrenValue->GetNamedValue("children")->ValueType == JsonValueType::Array)
							{
								auto childrenJsonArray = childrenValue->GetNamedArray("children");
								for (const auto &itemJsonChildren : childrenJsonArray)
								{
									auto childrenJsonValue = itemJsonChildren->GetObject();
									auto categoryChildrenModel = ref new CategoryTreeModels(childrenJsonValue->HasKey("id") ? Helpers::ToNumber(childrenJsonValue->GetNamedValue("id")) : 0.0,
										childrenJsonValue->HasKey("parent_id") ? Helpers::ToString(childrenJsonValue->GetNamedValue("parent_id")) : "",
										childrenJsonValue->HasKey("is_furniture") ? Helpers::ToBool(childrenJsonValue->GetNamedValue("is_furniture")) : false,
										childrenJsonValue->HasKey("name") ? Helpers::ToString(childrenJsonValue->GetNamedValue("name")) : "",
										childrenJsonValue->HasKey("token") ? Helpers::ToString(childrenJsonValue->GetNamedValue("token")) : "",
										childrenJsonValue->HasKey("media_image") ? Helpers::ToString(childrenJsonValue->GetNamedValue("media_image")) : "",
										childrenJsonValue->HasKey("level") ? Helpers::ToNumber(childrenJsonValue->GetNamedValue("level")) : 0.0,
										childrenJsonValue->HasKey("seo_header") ? Helpers::ToString(childrenJsonValue->GetNamedValue("seo_header")) : "",
										childrenJsonValue->HasKey("product_count") ? Helpers::ToString(childrenJsonValue->GetNamedValue("product_count")) : "",
										childrenJsonValue->HasKey("product_count_global") ? Helpers::ToString(childrenJsonValue->GetNamedValue("product_count_global")) : "",
										childrenJsonValue->HasKey("has_children") ? Helpers::ToBool(childrenJsonValue->GetNamedValue("has_children")) : false);
									vectCategoryChildren->Append(categoryChildrenModel);
								}
							}

							categoryModel->Children = vectCategoryChildren;
							vectChildren->Append(categoryModel);
						}
					}

					resultModel->Children = vectChildren;
					vect->Append(resultModel);
				}
			}

			return vect;
		}, task_continuation_context::use_current());
	});
}