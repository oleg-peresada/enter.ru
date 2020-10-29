#include "pch.h"
#include "AutorizationCommands.h"

using namespace EnterStore;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Data::Json;
using namespace Windows::Storage::Streams;

/*
Авторизация клиента в Enter.ru
*/
#pragma region Auth client

const std::wstring authUserInterface = L"user";
const std::wstring authUserCategory = L"auth";

AutorizationCommands::AutorizationCommands(Object^ parameter, AuthType authType, String^ password)
	: source_parameterAuth(parameter), source_authType(authType), source_Password(password)
{
}

IAsyncOperation<String^>^ AutorizationCommands::AutorizationToResultTokenAsync()
{
	using namespace concurrency;

	std::map<String^, String^> queryParameter;
	queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());
	if (TypeAuth == AuthType::Mobile)
	{
		queryParameter["mobile"] = Parameter->ToString();
	}
	else if (TypeAuth == AuthType::Email)
	{
		queryParameter["email"] = Parameter->ToString();
	}
	queryParameter["password"] = Password;

	return create_async([&, queryParameter](cancellation_token token) -> task<String^>
	{
		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter);
		httpCommand->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto operation = httpCommand->ToCommandOperationAsync(authUserInterface, authUserCategory);

		return create_task(operation).then([&](String^ content) -> String^
		{
			auto jsonObject = JsonObject::Parse(content);

			if (jsonObject->HasKey("result") && jsonObject->GetNamedValue("result")->ValueType == JsonValueType::Object)
			{
				auto resultObject = jsonObject->GetNamedObject("result");
				return resultObject->HasKey("token") ? Helpers::ToString(resultObject->GetNamedValue("token")) : "";
			}

			return nullptr;
		});
	});
}

AuthType AutorizationCommands::TypeAuth::get()
{
	return source_authType;
}

String^ AutorizationCommands::Password::get()
{
	return source_Password;
}

Object^ AutorizationCommands::Parameter::get()
{
	return source_parameterAuth;
}

#pragma endregion

/*
Создание нового аккаунта Enter.ru
*/
#pragma region Create user

const std::wstring userCreateInterface = L"user";
const std::wstring userCreateCategory = L"create";

UserCreateCommands::UserCreateCommands(int geoId, AuthType type,
	Object^ parameter, String^ firstName, String^ lastName, String^ password)
	: source_geoId(geoId), source_Type(type), source_parameter(parameter),
	source_firstName(firstName), source_lastName(lastName), source_password(password)
{
}

IAsyncOperation<UserCreateModels^>^ UserCreateCommands::UserCreateAsync()
{
	using namespace concurrency;

	std::map<String^, String^> queryParameter;
	queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());

	return create_async([&](cancellation_token token) -> task<UserCreateModels^>
	{
		auto json = ref new JsonObject();
		json->SetNamedValue("geo_id", JsonValue::CreateNumberValue(GeoId));

		if (this->Type == AuthType::Email)
		{
			json->SetNamedValue("email", JsonValue::CreateStringValue(safe_cast<String^>(Parameter)));
		}
		else if (this->Type == AuthType::Mobile)
		{
			json->SetNamedValue("mobile", JsonValue::CreateStringValue(safe_cast<String^>(Parameter)));
		}
		json->SetNamedValue("password", JsonValue::CreateStringValue(Password));
		json->SetNamedValue("first_name", JsonValue::CreateStringValue(FirstName));
		json->SetNamedValue("last_name", JsonValue::CreateStringValue(LastName));

		auto contentString = ref new HttpStringContent(json->Stringify(), UnicodeEncoding::Utf8, "application/json");
		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter, HttpMethod::Post, contentString, nullptr);
		httpCommand->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto operation = httpCommand->ToCommandOperationAsync(userCreateInterface, userCreateCategory);

		return create_task(operation).then([&](String^ content) -> UserCreateModels ^
		{
			auto json = JsonObject::Parse(content);
			if (json->HasKey("result") && json->GetNamedValue("result")->ValueType == JsonValueType::Object)
			{
				auto resultJson = json->GetNamedObject("result");

				auto userModel = ref new UserCreateModels(Helpers::ToString(resultJson->GetNamedValue("id")),
					Helpers::ToString(resultJson->GetNamedValue("password")),
					Helpers::ToString(resultJson->GetNamedValue("token")));
				return userModel;
			}

			return nullptr;
		});
	});
}

int UserCreateCommands::GeoId::get()
{
	return source_geoId;
}

AuthType UserCreateCommands::Type::get()
{
	return source_Type;
}

Object^ UserCreateCommands::Parameter::get()
{
	return source_parameter;
}

String^ UserCreateCommands::FirstName::get()
{
	return source_firstName;
}

String^ UserCreateCommands::LastName::get()
{
	return source_lastName;
}

String^ UserCreateCommands::Password::get()
{
	return source_password;
}

#pragma endregion

/*
Восстановление пароля in Enter.ru
*/
#pragma region user reset-password

std::wstring userResetInterface = L"user";
std::wstring userResetCategory = L"reset-password";

ResetPasswordUserCommands::ResetPasswordUserCommands(Object^ parameter, AuthType type)
	: source_parameter(parameter), source_type(type)
{
}

IAsyncOperation<bool>^ ResetPasswordUserCommands::ResetPasswordAsync()
{
	using namespace concurrency;

	return create_async([&](cancellation_token token) -> task<bool>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());
		
		if (this->Type == AuthType::Email)
		{
			queryParameter["email"] = this->Parameter->ToString();
		}
		else if (this->Type == AuthType::Mobile)
		{
			queryParameter["mobile"] = this->Parameter->ToString();
		}

		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter);
		httpCommand->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto operationCommand = httpCommand->ToCommandOperationAsync(userResetInterface, userResetCategory);

		return create_task(operationCommand, token).then([&](String^ content) -> bool
		{
			auto jsonContent = JsonObject::Parse(content);
			if (jsonContent->HasKey("result") && jsonContent->GetNamedValue("result")->ValueType == JsonValueType::Object)
			{
				auto resultContent = jsonContent->GetNamedObject("result");
				return resultContent->HasKey("confirmed") ? Helpers::ToBool(resultContent->GetNamedValue("confirmed")) : false;
			}

			return false;
		});
	});
}

Object^ ResetPasswordUserCommands::Parameter::get()
{
	return source_parameter;
}

AuthType ResetPasswordUserCommands::Type::get()
{
	return source_type;
}

#pragma endregion

/*
Изменение пароля Enter.ru
*/
#pragma region user change password

std::wstring userChangeInterface = L"user";
std::wstring userChangedCategory = L"change-password";

ChangePasswordUserCommands::ChangePasswordUserCommands(String^ token, String^ password, String^ newPassword)
	: source_Token(token), source_Password(password), source_newPassword(newPassword)
{
}

IAsyncOperation<bool>^ ChangePasswordUserCommands::ChangePasswordAsync()
{
	using namespace concurrency;

	return create_async([&](cancellation_token token) -> task<bool>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["client_id"] = StringReference(Helpers::standartClientId.c_str());
		queryParameter["token"] = this->Token;
		queryParameter["password"] = this->Password;
		queryParameter["new_password"] = this->NewPassword;

		auto httpCommand = ref new HttpCommand(Helpers::standartQueryCommand, queryParameter);
		httpCommand->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto operation = httpCommand->ToCommandOperationAsync(userChangeInterface, userChangedCategory);

		return create_task(operation, token).then([&](String^ content) -> bool
		{
			auto jsonContent = JsonObject::Parse(content);
			if (jsonContent->HasKey("result") && jsonContent->GetNamedValue("result")->ValueType == JsonValueType::Object)
			{
				auto resultContent = jsonContent->GetNamedObject("result");
				return resultContent->HasKey("confirmed") ? Helpers::ToBool(resultContent->GetNamedValue("confirmed")) : false;
			}

			return false;
		});
	});
}

String^ ChangePasswordUserCommands::Token::get()
{
	return source_Token;
}

String^ ChangePasswordUserCommands::Password::get()
{
	return source_Password;
}

String^ ChangePasswordUserCommands::NewPassword::get()
{
	return source_newPassword;
}

#pragma endregion