#include "pch.h"
#include "ShopListModels.h"

using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation::Collections;

ImagesModels::ImagesModels(String^ source, String^ position)
	: im_source(source), im_position(position)
{
}

String^ ImagesModels::Source::get()
{
	return im_source;
}

String^ ImagesModels::Position::get()
{
	return im_position;
}

GeoShopModels::GeoShopModels(int id, String^ name, String^ coordLong, String^ coordLat)
	: source_id(id), source_name(name), source_coordLong(coordLong), source_coordLat(coordLat)
{
}

int GeoShopModels::Id::get()
{
	return source_id;
}

String^ GeoShopModels::Name::get()
{
	return source_name;
}

String^ GeoShopModels::CoordLong::get()
{
	return source_coordLong;
}

String^ GeoShopModels::CoordLat::get()
{
	return source_coordLat;
}

ShopListModels::ShopListModels(int id,
	String^ token,
	String^ name,
	String^ description,
	String^ mediaImage,
	String^ workingTime,
	bool is_reconstruction,
	String^ phone,
	String^ address,
	float coordLong,
	float coordLat,
	String^ wayWalk,
	String^ wayAuto)

	: shop_id(id), shop_token(token), shop_name(name), shop_description(description), shop_mediaImage(mediaImage),
	shop_WorkingTime(workingTime), shop_Reconstruction(is_reconstruction), shop_phone(phone), shop_address(address),
	shop_CoordLong(coordLong), shop_CoordLat(coordLat), shop_wayWalk(wayWalk), shop_WayAuto(wayAuto)
{
}

int ShopListModels::Id::get()
{
	return shop_id;
}

String^ ShopListModels::Token::get()
{
	return shop_token;
}

String^ ShopListModels::Name::get()
{
	return shop_name;
}

String^ ShopListModels::Description::get()
{
	return shop_description;
}

String^ ShopListModels::MediaImage::get()
{
	return shop_mediaImage;
}

String^ ShopListModels::WorkingTime::get()
{
	return shop_WorkingTime;
}

bool ShopListModels::IsReconstruction::get()
{
	return shop_Reconstruction;
}

String^ ShopListModels::Phone::get()
{
	return shop_phone;
}

String^ ShopListModels::Address::get()
{
	return shop_address;
}

float ShopListModels::CoordLong::get()
{
	return shop_CoordLong;
}

float ShopListModels::CoordLat::get()
{
	return shop_CoordLat;
}

String^ ShopListModels::WayWalk::get()
{
	return shop_wayWalk;
}

String^ ShopListModels::WayAuto::get()
{
	return shop_WayAuto;
}

IVector<ImagesModels^>^ ShopListModels::Images::get()
{
	return shop_Images;
}

void ShopListModels::Images::set(IVector<ImagesModels^>^ val)
{
	shop_Images = val;
}

GeoShopModels^ ShopListModels::Geo::get()
{
	return source_geo;
}

void ShopListModels::Geo::set(GeoShopModels^ val)
{
	source_geo = val;
}