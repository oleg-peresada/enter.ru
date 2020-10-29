#include "pch.h"
#include "ProductValueConverter.h"

using namespace Enter::Converters;

using namespace Platform;
using namespace Windows::UI::Xaml::Interop;

Object^ ProductValueConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	auto content = dynamic_cast<String^>(value);
	if (content != nullptr)
	{
		if (content == "true")
		{
			return "Да";
		}
		else if (content == "false")
		{
			return "Нет";
		}
		else
		{
			return value;
		}
	}

	return nullptr;
}

Object^ ProductValueConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}