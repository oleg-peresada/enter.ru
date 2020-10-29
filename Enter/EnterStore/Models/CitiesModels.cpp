#include "pch.h"
#include "CitiesModels.h"

using namespace EnterStore::Models;
using namespace Platform;

CitiesModels::CitiesModels(int id,
	int parent_id,
	String^ name,
	String^ token,
	bool is_main,
	bool has_shop,
	bool has_delivery,
	bool has_subway,
	double coordLong,
	double coordLat,
	bool tk_available)
	: source_id(id), source_parentId(parent_id), source_name(name),
	source_token(token), source_isMain(is_main), source_hasShop(has_shop),
	source_hasDelivery(has_delivery), source_hasSubway(has_subway),
	source_coordLong(coordLong), source_coordLat(coordLat),
	source_tkAvailable(tk_available)
{
}

int CitiesModels::Id::get()
{
	return source_id;
}

int CitiesModels::ParentId::get()
{
	return source_parentId;
}

String^ CitiesModels::Name::get()
{
	return source_name;
}

String^ CitiesModels::Token::get()
{
	return source_token;
}

bool CitiesModels::IsMain::get()
{
	return source_isMain;
}

bool CitiesModels::HasShop::get()
{
	return source_hasShop;
}

bool CitiesModels::HasDelivery::get()
{
	return source_hasDelivery;
}

bool CitiesModels::HasSubway::get()
{
	return source_hasSubway;
}

double CitiesModels::CoordLong::get()
{
	return source_coordLong;
}

double CitiesModels::CoordLat::get()
{
	return source_coordLat;
}

bool CitiesModels::TkAvailable::get()
{
	return source_tkAvailable;
}

/*

AutoRegionModels

*/
AutoRegionModels::AutoRegionModels(int id, String^ name) : m_id(id), m_name(name)
{
}

int AutoRegionModels::Id::get()
{
	return m_id;
}

String^ AutoRegionModels::Name::get()
{
	return m_name;
}

/*

AutoCityModels

*/
AutoCityModels::AutoCityModels(int id, String^ name, AutoRegionModels^ region) : m_id(id), m_name(name), m_region(region)
{
}

int AutoCityModels::Id::get()
{
	return m_id;
}

String^ AutoCityModels::Name::get()
{
	return m_name;
}

AutoRegionModels^ AutoCityModels::Region::get()
{
	return m_region;
}