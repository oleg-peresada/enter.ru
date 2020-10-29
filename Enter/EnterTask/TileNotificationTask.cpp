#include "pch.h"
#include "TileNotificationTask.h"

using namespace EnterTask;

using namespace Platform;
using namespace Windows::Data::Xml::Dom;

XmlDocument^ TileNotificationTask::TileSquareText02(String^ textOne, String^ textTwo)
{
	auto xml = ref new XmlDocument();
	auto tile = xml->CreateElementNS(nullptr, "tile");
	auto visual = xml->CreateElement("visual");

	auto binding = xml->CreateElement("binding");
	binding->SetAttribute("template", "TileSquareText02");

	auto field_one = xml->CreateElement("text");
	field_one->SetAttribute("id", "1");
	field_one->InnerText = textOne;

	auto field_two = xml->CreateElement("text");
	field_two->SetAttribute("id", "2");
	field_two->InnerText = textTwo;

	binding->AppendChild(field_one);
	binding->AppendChild(field_two);
	visual->AppendChild(binding);
	tile->AppendChild(visual);
	xml->AppendChild(tile);

	return xml;
}

XmlDocument^ TileNotificationTask::TileWideText09(String^ textOne, String^ textTwo)
{
	auto xml = ref new XmlDocument();
	auto tile = xml->CreateElementNS(nullptr, "tile");
	auto visual = xml->CreateElement("visual");

	auto binding = xml->CreateElement("binding");
	binding->SetAttribute("template", "TileWideText09");

	auto field_one = xml->CreateElement("text");
	field_one->SetAttribute("id", "1");
	field_one->InnerText = textOne;

	auto field_two = xml->CreateElement("text");
	field_two->SetAttribute("id", "2");
	field_two->InnerText = textTwo;

	binding->AppendChild(field_one);
	binding->AppendChild(field_two);
	visual->AppendChild(binding);
	tile->AppendChild(visual);
	xml->AppendChild(tile);

	return xml;
}

XmlDocument^ TileNotificationTask::TileWide310x150PeekImage03(String^ image, String^ text)
{
	auto xml = ref new XmlDocument();
	auto tile = xml->CreateElementNS(nullptr, "tile");
	auto visual = xml->CreateElement("visual");
	visual->SetAttribute("version", "2");

	auto binding = xml->CreateElement("binding");
	binding->SetAttribute("template", "TileWide310x150PeekImage03");
	binding->SetAttribute("fallback", "TileWidePeekImage03");

	auto imageXml = xml->CreateElement("image");
	imageXml->SetAttribute("id", "1");
	imageXml->SetAttribute("src", image);
	imageXml->SetAttribute("alt", image);

	auto textXml = xml->CreateElement("text");
	textXml->SetAttribute("id", "1");
	textXml->InnerText = text;

	binding->AppendChild(imageXml);
	binding->AppendChild(textXml);

	visual->AppendChild(binding);
	tile->AppendChild(visual);
	xml->AppendChild(tile);

	return xml;
}

XmlDocument^ ToastNotificationTask::ToastText02(String^ header, String^ body)
{
	auto xml = ref new XmlDocument();
	auto toast = xml->CreateElementNS(nullptr, "toast");
	auto visual = xml->CreateElement("visual");

	auto binding = xml->CreateElement("binding");
	binding->SetAttribute("template", "ToastText02");
	
	auto textHeader = xml->CreateElement("text");
	textHeader->SetAttribute("id", "1");
	textHeader->InnerText = header;

	auto textBody = xml->CreateElement("text");
	textBody->SetAttribute("id", "2");
	textBody->InnerText = body;

	binding->AppendChild(textHeader);
	binding->AppendChild(textBody);
	visual->AppendChild(binding);
	toast->AppendChild(visual);
	xml->AppendChild(toast);

	return xml;
}