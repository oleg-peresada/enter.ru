#pragma once

#include <string>
#include <iostream>

using namespace Platform;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Data;

namespace Enter
{
	namespace Converters
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class TrackerStatusConverter sealed : IValueConverter
		{
		public:
			virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
			virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class TrackerPaymentConverter sealed : IValueConverter
		{
		public:
			virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
			virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class TrackerDateConverter sealed : IValueConverter
		{
		public:
			virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
			virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		};
	}
}