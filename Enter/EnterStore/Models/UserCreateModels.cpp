#include "pch.h"
#include "UserCreateModels.h"

using namespace EnterStore::Models;

UserCreateModels::UserCreateModels(String^ id, String^ password, String^ token)
	: source_id(id), source_password(password), source_token(token)
{
}

String^ UserCreateModels::Id::get()
{
	return source_id;
}

String^ UserCreateModels::Password::get()
{
	return source_password;
}

String^ UserCreateModels::Token::get()
{
	return source_token;
}