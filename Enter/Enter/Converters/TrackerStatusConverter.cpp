#include "pch.h"
#include "TrackerStatusConverter.h"

using namespace Enter;
using namespace Enter::Converters;

using namespace Platform;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml;

Object^ TrackerStatusConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	int num = StringToNumber(value->ToString());
	if (StringToNumber(parameter->ToString()) == 1)
	{
		if (value != nullptr)
		{
			if (num == 1) return "Заказ оплачен";
			if (num == 100) return "Заказ отменен";
			if (num == 4 || num == 20) return "Заказ оплачен";
		}
	}
	else
	{
		if (num == 1 || num == 100 || num == 4 || num == 20)
			return Visibility::Visible;
		else
			return Visibility::Collapsed;
	}

	return nullptr;
}

Object^ TrackerStatusConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}

Object^ TrackerPaymentConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	if (value != nullptr)
	{
		int num = StringToNumber(value->ToString());
		if (num == 1) return "Оплата наличными";
		if (num == 2) return "Оплата банковской картой";
	}

	return "Оплата электронными деньгами";
}

Object^ TrackerPaymentConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}

Object^ TrackerDateConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	if (value != nullptr)
	{
		std::string strDate(begin(value->ToString()), end(value->ToString()));
		std::istringstream dateStream(strDate);

		int year = 0;
		dateStream >> year;

		if (year == 0)
		{
			return Visibility::Collapsed;
		}
		else
		{
			return Visibility::Visible;
		}
	}

	return nullptr;
}

Object^ TrackerDateConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}