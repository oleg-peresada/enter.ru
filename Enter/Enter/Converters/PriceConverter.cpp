#include "pch.h"
#include "PriceConverter.h"

using namespace Enter::Converters;

using namespace Platform;
using namespace Windows::UI::Xaml::Interop;

Object^ PriceConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	float64 priceValue = static_cast<float64>(value);
	if (value != nullptr)
	{
		auto currency = ref new Windows::Globalization::NumberFormatting::CurrencyFormatter("RUB");
		return currency->FormatDouble(priceValue);
	}
	
	return nullptr;
}

Object^ PriceConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}