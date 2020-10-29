#include "pch.h"
#include "BannerSerializer.h"

using namespace EnterTask;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::Data::Json;

concurrency::task<IVector<PromoBannerModels^>^> BannerSerializer::Open()
{
	auto localFolder = ApplicationData::Current->LocalFolder;
	auto file = localFolder->CreateFileAsync("promoBannerStorage.json", CreationCollisionOption::OpenIfExists);

	return concurrency::create_task(file).then([this](StorageFile^ storageFile) -> concurrency::task<IVector<PromoBannerModels^>^>
	{
		auto textFile = FileIO::ReadTextAsync(storageFile, UnicodeEncoding::Utf8);
		return concurrency::create_task(textFile).then([this](String^ content) -> IVector<PromoBannerModels^>^
		{
			auto vect = ref new Vector<PromoBannerModels^>();

			if (content != nullptr)
			{
				auto json = JsonObject::Parse(content);
				auto arrayPromo = json->GetNamedArray("promo");
				for (const auto &item : arrayPromo)
				{
					auto element = item->GetObject();

					auto promoModel = ref new PromoBannerModels(element->GetNamedString("id"),
						element->GetNamedString("type_id"),
						element->GetNamedString("name"),
						element->GetNamedString("media_image"), nullptr, nullptr);
					vect->Append(promoModel);
				}
			}

			return vect;
		}).then(TaskException<IVector<PromoBannerModels^>^>());
	}).then(TaskException<IVector<PromoBannerModels^>^>());
}

concurrency::task<void> BannerSerializer::Save(IVector<PromoBannerModels^>^ value)
{
	auto localFolder = ApplicationData::Current->LocalFolder;
	auto file = localFolder->CreateFileAsync("promoBannerStorage.json", CreationCollisionOption::ReplaceExisting);

	return concurrency::create_task(file).then([this, value](StorageFile^ storageFile) -> void
	{
		if (value != nullptr && value->Size != 0)
		{
			auto arrayJson = ref new JsonArray();
			for (const auto &item : value)
			{
				auto element = ref new JsonObject();
				element->SetNamedValue("id", JsonValue::CreateStringValue(item->Id));
				element->SetNamedValue("name", JsonValue::CreateStringValue(item->Name));
				element->SetNamedValue("media_image", JsonValue::CreateStringValue(item->MediaImage));
				element->SetNamedValue("type_id", JsonValue::CreateStringValue(item->TypeId));
				arrayJson->Append(element);
			}

			auto promo = ref new JsonObject();
			promo->SetNamedValue("promo", arrayJson);
			auto stringify = promo->Stringify();

			FileIO::WriteTextAsync(storageFile, stringify);
		}
	}).then(TaskException<void>());
}