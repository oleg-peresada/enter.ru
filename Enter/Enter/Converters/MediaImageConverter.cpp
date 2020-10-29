#include "pch.h"
#include "MediaImageConverter.h"

using namespace Enter::Converters;

using namespace Platform;
using namespace Windows::UI::Xaml::Interop;

Object^ MediaImageConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	if (value != nullptr)
	{
		std::wstring w_append(L"http://fs03.enter.ru/1/1/");
		w_append.append(parameter->ToString()->Data());
		w_append.append(L"/");
		w_append.append(value->ToString()->Data());

		return StringReference(w_append.c_str());
	}
	else
	{
		return "/Assets/MediumGray.png";
	}

	return nullptr;
}

Object^ MediaImageConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}

Object^ MediaLabelPromoConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	if (value != nullptr)
	{
		std::wstring w_append(L"http://fs05.enter.ru/7/1/124x38/");
		w_append.append(value->ToString()->Data());

		return StringReference(w_append.c_str());
	}

	return nullptr;
}

Object^ MediaLabelPromoConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}

Object^ PromoBannerImageConverter::Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	if (value != nullptr)
	{
		std::wstring w_append(L"http://fs03.enter.ru/4/1/");
		w_append.append(parameter->ToString()->Data());
		w_append.append(L"/");
		w_append.append(value->ToString()->Data());

		return StringReference(w_append.c_str());
	}

	return nullptr;
}

Object^ PromoBannerImageConverter::ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language)
{
	return nullptr;
}