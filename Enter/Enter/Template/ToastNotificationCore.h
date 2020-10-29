#pragma once

using namespace Platform;
using namespace Windows::Data::Xml;
using namespace Windows::Data::Xml::Dom;

namespace Enter
{
	namespace Template
	{
		class ToastNotificationCore
		{
		public:
			static XmlDocument^ ToastText02(String^ message_one, String^ message_two);
		};
	}
}