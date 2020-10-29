#pragma once

#include <string>
#include <collection.h>

#include "Helpers.h"
#include "HttpCommand.h"
#include "Commands\AutorizationCommands.h"
#include "Models\UserCreateModels.h"

using namespace EnterStore::Models;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;

namespace EnterStore
{
	namespace Commands
	{
		[Platform::Metadata::Flags]
		public enum class AuthType : unsigned int
		{
			Mobile = 0,
			Email,
		};

		/*
		Авторизация клиента в Enter.ru
		*/

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class AutorizationCommands sealed
		{
		public:
			AutorizationCommands(Object^ parameter, AuthType authType, String^ password);

			IAsyncOperation<String^>^ AutorizationToResultTokenAsync();

			property String^ Password
			{
				String^ get();
			}

			property Object^ Parameter
			{
				Object^ get();
			}

			property AuthType TypeAuth
			{
				AuthType get();
			}
		private:
			AuthType source_authType;
			Object^ source_parameterAuth;
			String^ source_Password;
		};

		/*
		Создание нового аккаунта Enter.ru
		*/

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class UserCreateCommands sealed
		{
		public:
			UserCreateCommands(int geoId, AuthType type, Object^ parameter,
				String^ firstName, String^ lastName, String^ password);
			IAsyncOperation<UserCreateModels^>^ UserCreateAsync();

			property AuthType Type
			{
				AuthType get();
			}

			property Object^ Parameter
			{
				Object^ get();
			}

			property String^ FirstName
			{
				String^ get();
			}

			property String^ LastName
			{
				String^ get();
			}

			property int GeoId
			{
				int get();
			}

			property String^ Password
			{
				String^ get();
			}
		private:
			AuthType source_Type;
			Object^ source_parameter;
			String^ source_firstName;
			String^ source_lastName;
			String^ source_password;
			int source_geoId;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ResetPasswordUserCommands sealed
		{
		public:
			ResetPasswordUserCommands(Object^ parameter, AuthType type);
			IAsyncOperation<bool>^ ResetPasswordAsync();

			property Object^ Parameter
			{
				Object^ get();
			}

			property AuthType Type
			{
				AuthType get();
			}
		private:
			Object^ source_parameter;
			AuthType source_type;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ChangePasswordUserCommands sealed
		{
		public:
			ChangePasswordUserCommands(String^ token, String^ password, String^ newPassword);
			IAsyncOperation<bool>^ ChangePasswordAsync();

			property String^ Token
			{
				String^ get();
			}

			property String^ Password
			{
				String^ get();
			}

			property String^ NewPassword
			{
				String^ get();
			}
		private:
			String^ source_Token;
			String^ source_Password;
			String^ source_newPassword;
		};
	}
}