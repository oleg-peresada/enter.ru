#include "pch.h"
#include "ToastNotificationCore.h"

using namespace Enter;
using namespace Enter::Template;

using namespace Platform;
using namespace Windows::Data::Xml;
using namespace Windows::Data::Xml::Dom;

XmlDocument^ ToastNotificationCore::ToastText02(String^ message_one, String^ message_two)
{
	auto xml = ref new XmlDocument();
	auto element = xml->CreateElementNS(nullptr, "toast");
	auto visualElement = xml->CreateElement("visual");

	auto bindingElement = xml->CreateElement("binding");
	bindingElement->SetAttribute("template", "ToastText02");

	auto textOneElement = xml->CreateElement("text");
	textOneElement->SetAttribute("id", "1");
	textOneElement->InnerText = message_one;

	auto textTwoElement = xml->CreateElement("text");
	textTwoElement->SetAttribute("id", "2");
	textTwoElement->InnerText = message_two;

	bindingElement->AppendChild(textOneElement);
	bindingElement->AppendChild(textTwoElement);

	visualElement->AppendChild(bindingElement);
	element->AppendChild(visualElement);
	xml->AppendChild(element);

	return xml;
}