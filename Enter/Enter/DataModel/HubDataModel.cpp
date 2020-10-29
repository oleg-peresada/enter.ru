#include "pch.h"
#include "HubDataModel.h"

using namespace Enter::DataModel;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

HubDataModel::HubDataModel(String^ name, String^ description)
	: hub_name(name), hub_description(description)
{
}

String^ HubDataModel::Name::get()
{
	return hub_name;
}

String^ HubDataModel::Description::get()
{
	return hub_description;
}

TrackerNewDataModel::TrackerNewDataModel(TrackerProductOrderModels^ trackerOrder, ProductCardModels^ orderCard)
: m_trackerOrder(trackerOrder), m_orderCard(orderCard)
{
}

TrackerProductOrderModels^ TrackerNewDataModel::TrackerOrder::get()
{
	return m_trackerOrder;
}

ProductCardModels^ TrackerNewDataModel::OrderCard::get()
{
	return m_orderCard;
}