#pragma once

#include <string>

using namespace Platform;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Data;

namespace Enter
{
	namespace Converters
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class MediaImageConverter sealed : public IValueConverter
		{
		public:
			virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
			virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class MediaLabelPromoConverter sealed : public IValueConverter
		{
		public:
			virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
			virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PromoBannerImageConverter sealed : public IValueConverter
		{
		public:
			virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
			virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		};
	}
}