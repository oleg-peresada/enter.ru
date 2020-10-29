#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <ios>

namespace EnterStore
{
	class Helpers sealed
	{
	public:
		static std::wstring ForQuery(const std::map<Platform::String^, Platform::String^>& parameter);
		const static std::wstring standartQueryCommand;
		const static std::wstring reviewsQueryCommand;
		const static std::wstring standartClientId;

		static Platform::Object^ ToValue(Windows::Data::Json::IJsonValue^ jsonValue);
		static bool ToBool(Windows::Data::Json::IJsonValue^ jsonValue);
		static double ToNumber(Windows::Data::Json::IJsonValue^ jsonValue);
		static Platform::String^ ToString(Windows::Data::Json::IJsonValue^ jsonValue);
	};
}
