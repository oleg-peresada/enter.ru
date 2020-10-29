#pragma once

using namespace Platform;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Data;

namespace Enter
{
	namespace Converters
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class VisibilityNullValueConverter sealed : IValueConverter
		{
		public:
			virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
			virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class VisibilityDeliveryIdConverter sealed : IValueConverter
		{
		public:
			virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
			virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PriceDeliveryConverter sealed : IValueConverter
		{
		public:
			virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
			virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class DeliveryIdTypeConverter sealed : IValueConverter
		{
		public:
			virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
			virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class OrderConfirmedConverter sealed : IValueConverter
		{
		public:
			virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
			virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		};
	}
}