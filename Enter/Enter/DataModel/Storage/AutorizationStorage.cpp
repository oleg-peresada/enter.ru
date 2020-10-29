#include "pch.h"
#include "AutorizationStorage.h"

using namespace Enter::DataModel::Storage;

using namespace Platform;
using namespace Windows::Storage;
using namespace Windows::Foundation;

const std::wstring key_settingsAutorization = L"_enterStorageToken";

const std::wstring key_cityId = L"_enterCityId";
const std::wstring key_cityParentId = L"_enterCityParentId";
const std::wstring key_cityName = L"_enterCityName";

AutorizationStorage::AutorizationStorage()
{
}

void AutorizationStorage::CreateSaveToken(String^ token)
{
	auto local = ApplicationData::Current->LocalSettings;
	auto value = local->Values;
	value->Insert(StringReference(key_settingsAutorization.c_str()), dynamic_cast<IPropertyValue^>(PropertyValue::CreateString(token)));
}

AutorizationStorage^ AutorizationStorage::Current::get()
{
	return ref new AutorizationStorage();
}

String^ AutorizationStorage::Token::get()
{
	auto local = ApplicationData::Current->LocalSettings;
	auto value = local->Values;

	if (value->HasKey(StringReference(key_settingsAutorization.c_str())))
	{
		return static_cast<String^>(value->Lookup(StringReference(key_settingsAutorization.c_str())));
	}
	else
	{
		return nullptr;
	}
}

void AutorizationStorage::Token::set(String^ val)
{
	auto local = ApplicationData::Current->LocalSettings;
	auto value = local->Values;
	value->Insert(StringReference(key_settingsAutorization.c_str()), val);
}

CityTokenStorage::CityTokenStorage()
{
}

CityTokenStorage::CityTokenStorage(int id, int parentId, String^ name) : source_id(id), source_parentId(parentId), source_name(name)
{
}

void CityTokenStorage::Save()
{
	auto local = ApplicationData::Current->LocalSettings;
	auto value = local->Values;
	value->Insert(StringReference(key_cityId.c_str()), dynamic_cast<IPropertyValue^>(PropertyValue::CreateInt32(Id)));
	value->Insert(StringReference(key_cityParentId.c_str()), dynamic_cast<IPropertyValue^>(PropertyValue::CreateInt32(ParentId)));
	value->Insert(StringReference(key_cityName.c_str()), dynamic_cast<IPropertyValue^>(PropertyValue::CreateString(Name)));
}

CityTokenStorage^ CityTokenStorage::Open()
{
	auto local = ApplicationData::Current->LocalSettings;
	auto value = local->Values;

	if (value->HasKey(StringReference(key_cityId.c_str())))
	{
		Id = static_cast<int>(value->Lookup(StringReference(key_cityId.c_str())));
	}

	if (value->HasKey(StringReference(key_cityParentId.c_str())))
	{
		ParentId = static_cast<int>(value->Lookup(StringReference(key_cityParentId.c_str())));
	}

	if (value->HasKey(StringReference(key_cityName.c_str())))
	{
		Name = static_cast<String^>(value->Lookup(StringReference(key_cityName.c_str())));
	}

	return ref new CityTokenStorage(Id, ParentId, Name);
}

CityTokenStorage^ CityTokenStorage::Current::get()
{
	auto cityStorage = ref new CityTokenStorage();
	cityStorage->Open();
	return cityStorage;
}

int CityTokenStorage::Id::get()
{
	return source_id;
}

void CityTokenStorage::Id::set(int val)
{
	source_id = val;
}

int CityTokenStorage::ParentId::get()
{
	return source_parentId;
}

void CityTokenStorage::ParentId::set(int val)
{
	source_parentId = val;
}

String^ CityTokenStorage::Name::get()
{
	return source_name;
}

void CityTokenStorage::Name::set(String^ val)
{
	source_name = val;
}

bool CityTokenStorage::IsCityToken::get()
{
	auto cityStorage = ref new CityTokenStorage();
	cityStorage->Open();

	if (cityStorage->Id == 0 && 
		cityStorage->ParentId == 0 && 
		cityStorage->Name == nullptr)
	{
		return false;
	}

	return true;
}

Customizations::Customizations()
{
}

Customizations::Customizations(String^ resourceProductTemplate, int currentSource)
: source_resourceProductTemplate(resourceProductTemplate), source_currentStore(currentSource)
{
}

Customizations^ Customizations::Open()
{
	auto localSettings = ApplicationData::Current->LocalSettings;
	auto localValue = localSettings->Values;

	String^ productTemplate = nullptr;
	if (localValue->HasKey("key_productTemplate"))
	{
		productTemplate = static_cast<String^>(localValue->Lookup("key_productTemplate"));
	}

	int currentStore = -1;
	if (localValue->HasKey("key_currentStoreLast"))
	{
		currentStore = static_cast<int>(localValue->Lookup("key_currentStoreLast"));
	}

	return ref new Customizations(productTemplate, currentStore);
}

void Customizations::Save()
{
	auto localSettings = ApplicationData::Current->LocalSettings;
	auto localValue = localSettings->Values;

	localValue->Insert("key_productTemplate", dynamic_cast<IPropertyValue^>(PropertyValue::CreateString(ResourceProductTemplate)));
	localValue->Insert("key_currentStoreLast", dynamic_cast<IPropertyValue^>(PropertyValue::CreateInt32(CurrentStore)));
}

Customizations^ Customizations::Current::get()
{
	return Open();
}

String^ Customizations::ResourceProductTemplate::get()
{
	return source_resourceProductTemplate;
}

void Customizations::ResourceProductTemplate::set(String^ value)
{
	source_resourceProductTemplate = value;
}

int Customizations::CurrentStore::get()
{
	return source_currentStore;
}

void Customizations::CurrentStore::set(int value)
{
	source_currentStore = value;
}