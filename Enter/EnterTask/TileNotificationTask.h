#pragma once

using namespace Platform;
using namespace Windows::Data::Xml::Dom;

namespace EnterTask
{
	class TileNotificationTask
	{
	public:
		static XmlDocument^ TileSquareText02(String^ textOne, String^ textTwo);
		static XmlDocument^ TileWideText09(String^ textOne, String^ textTwo);
		static XmlDocument^ TileWide310x150PeekImage03(String^ image, String^ text);
	};

	class ToastNotificationTask
	{
	public:
		static XmlDocument^ ToastText02(String^ header, String^ body);
	};
}