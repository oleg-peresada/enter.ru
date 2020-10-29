#include "pch.h"
#include "VisibilityNullValueConverter.h"

using namespace Enter::Converters;

using namespace Platform;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Controls;

Object^ VisibilityNullValueConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	auto propVect = dynamic_cast<IVector<EnterStore::Models::PropertyExtensionsCardModels^>^>(value);
	if (value != nullptr)
	{
		if (propVect != nullptr && propVect->Size == 0)
		{
			return Visibility::Collapsed;
		}
		else
		{
			return Visibility::Visible;
		}

		return Visibility::Visible;
	}

	return Visibility::Collapsed;
}

Object^ VisibilityNullValueConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}

//VisibilityDeliveryIdConverter

Object^ VisibilityDeliveryIdConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	int id = static_cast<int>(value);
	if (id == 1)
	{
		return Visibility::Collapsed;
	}
	else if (id == 3)
	{
		return Visibility::Visible;
	}
	else if (id == 4)
	{
		return Visibility::Visible;
	}

	return Visibility::Collapsed;
}

Object^ VisibilityDeliveryIdConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}

//PriceDeliveryConverter

Object^ PriceDeliveryConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	float64 priceDelivery = static_cast<float64>(value);
	if (value != nullptr)
	{
		if (priceDelivery == 0.0) return "Бесплатно";

		auto currency = ref new Windows::Globalization::NumberFormatting::CurrencyFormatter("RUB");
		return currency->FormatDouble(priceDelivery);
	}

	return nullptr;
}

Object^ PriceDeliveryConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}

//DeliveryIdTypeConverter

Object^ DeliveryIdTypeConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	int id = static_cast<int>(value);
	if (value != nullptr)
	{
		if (id == 1) return "Доставка курьером";
		if (id == 3) return "Самостоятельно забрать из магазина";
		if (id == 4) return "Забрать сейчас из магазина";
	}

	return nullptr;
}

Object^ DeliveryIdTypeConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}

//OrderConfirmedConverter
Object^ OrderConfirmedConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	try
	{
		if (value != nullptr)
		{
			if (value->ToString() == true.ToString()) return "Успешно создан";
			if (!(value->ToString() == true.ToString())) return "Не был создан";
		}
	}
	catch (Exception^)
	{
		return "Не был создан";
	}

	return "Не был создан";
}

Object^ OrderConfirmedConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}