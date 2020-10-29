#pragma once

using namespace Platform;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Data;

namespace Enter
{
	namespace Converters
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class TextSourceConvert sealed : IValueConverter
		{
		public:
			virtual Object^ Convert(Object^ value, TypeName targetType, Object^ parameter, String^ language);
			virtual Object^ ConvertBack(Object^ value, TypeName targetType, Object^ parameter, String^ language);
		};
	}
}