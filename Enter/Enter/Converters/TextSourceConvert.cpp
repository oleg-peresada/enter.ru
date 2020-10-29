#include "pch.h"
#include "TextSourceConvert.h"

using namespace Enter::Converters;

using namespace Platform;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::Data::Html;

Object^ TextSourceConvert::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	if (value != nullptr)
	{
		auto result = HtmlUtilities::ConvertToText(safe_cast<String^>(value));
		return result;
	}

	return nullptr;
}

Object^ TextSourceConvert::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}