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
		return "����� ���� � �������";
	}
	else if (content == false)
	{
		return "������ ��� � �������";
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
		if (sexValue == "0") return "�� �������";
		if (sexValue == "1") return "�������";
		if (sexValue == "2") return "�������";
	}

	return nullptr;
}

Object^ SexConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}