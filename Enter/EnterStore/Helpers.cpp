#include "pch.h"
#include "Helpers.h"

using namespace EnterStore;

using namespace Platform;

const std::wstring Helpers::standartQueryCommand = L"api.enter.ru";
const std::wstring Helpers::reviewsQueryCommand = L"reviews.enter.ru";
const std::wstring Helpers::standartClientId = L"client id";

std::wstring Helpers::ForQuery(const std::map<Platform::String^, Platform::String^>& parameter)
{
	std::wstring queryAppend;
	bool flag = true;

	if (parameter.size() > 0)
	{
		for (const auto &item : parameter)
		{
			if (flag)
			{
				flag = false;
			}
			else
			{
				queryAppend.append(L"&");
			}

			queryAppend.append(item.first->Data());
			queryAppend.append(L"=");
			queryAppend.append(item.second->Data());
		}
	}

	return queryAppend;
}

Platform::Object^ Helpers::ToValue(Windows::Data::Json::IJsonValue^ jsonValue)
{
	switch (jsonValue->ValueType)
	{
	case Windows::Data::Json::JsonValueType::Array:
		return jsonValue->GetArray();
		break;
	case Windows::Data::Json::JsonValueType::Boolean:
		return jsonValue->GetBoolean();
		break;
	case Windows::Data::Json::JsonValueType::Null:
		return nullptr;
		break;
	case Windows::Data::Json::JsonValueType::Number:
		return jsonValue->GetNumber();
		break;
	case Windows::Data::Json::JsonValueType::Object:
		return jsonValue->GetObject();
		break;
	case Windows::Data::Json::JsonValueType::String:
		return jsonValue->GetString();
		break;
	default:
		throw ref new Platform::InvalidArgumentException("jsonValue invalid argument exception");
		break;
	}
}

bool Helpers::ToBool(Windows::Data::Json::IJsonValue^ jsonValue)
{
	Platform::String^ stringValue = Helpers::ToValue(jsonValue)->ToString();

	bool value = false;
	std::string conversation(begin(stringValue), end(stringValue));
	std::istringstream isStream(conversation);
	isStream >> std::boolalpha >> value;

	return value;
}

double Helpers::ToNumber(Windows::Data::Json::IJsonValue^ jsonValue)
{
	auto stringValue = Helpers::ToValue(jsonValue)->ToString();
	std::string conversation(Platform::begin(stringValue), Platform::end(stringValue));
	double result = 0.0;
	std::istringstream(conversation) >> result;
	return result;
}

Platform::String^ Helpers::ToString(Windows::Data::Json::IJsonValue^ jsonValue)
{
	return Helpers::ToValue(jsonValue)->ToString();
}