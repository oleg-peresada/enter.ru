#include "pch.h"
#include "BuyableConverter.h"

using namespace Enter::Converters;

using namespace Platform;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::Foundation;

Object^ BuyableConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	auto content = safe_cast<bool>(value);

	if (content == true)
	{
		return "Товар есть в наличии";
	}
	else if (content == false)
	{
		return "Товара нет в наличии";
	}

	return nullptr;
}

Object^ BuyableConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}

Object^ SexConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	auto sexValue = dynamic_cast<String^>(value);
	if (sexValue != nullptr)
	{
		if (sexValue == "0") return "Не выбрано";
		if (sexValue == "1") return "Мужской";
		if (sexValue == "2") return "Женский";
	}

	return nullptr;
}

Object^ SexConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}