#include "pch.h"
#include "FilterProductModels.h"

using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

FilterOptionsModels::FilterOptionsModels(int id, String^ name, int global, int quantity, int propertyId)
	: source_id(id), source_name(name), source_global(global), source_quantity(quantity), source_propertyId(propertyId)
{
}

int FilterOptionsModels::Id::get()
{
	return source_id;
}

String^ FilterOptionsModels::Name::get()
{
	return source_name;
}

int FilterOptionsModels::Global::get()
{
	return source_global;
}

int FilterOptionsModels::Quantity::get()
{
	return source_quantity;
}

int FilterOptionsModels::PropertyId::get()
{
	return source_propertyId;
}

FilterProductModels::FilterProductModels(String^ filterId,
	String^ name,
	int filter_typeId,
	String^ unit,
	bool isMultiple,
	bool isSlider,
	String^ step,
	double filter_min,
	double filter_max,
	double globalMax,
	double globalMin)
	: source_filterId(filterId), source_name(name),
	source_typeId(filter_typeId), source_unit(unit), source_isMultiple(isMultiple),
	source_isSlider(isSlider), source_step(step), source_min(filter_min), source_max(filter_max),
	source_globalMax(globalMax), source_globalMin(globalMin)
{
}

String^ FilterProductModels::FilterId::get()
{
	return source_filterId;
}

String^ FilterProductModels::Name::get()
{
	return source_name;
}

int FilterProductModels::TypeId::get()
{
	return source_typeId;
}

String^ FilterProductModels::Unit::get()
{
	return source_unit;
}

bool FilterProductModels::IsMultiple::get()
{
	return source_isMultiple;
}

bool FilterProductModels::IsSlider::get()
{
	return source_isSlider;
}

String^ FilterProductModels::Step::get()
{
	return source_step;
}

double FilterProductModels::Min::get()
{
	return source_min;
}

double FilterProductModels::Max::get()
{
	return source_max;
}

double FilterProductModels::GlobalMin::get()
{
	return source_globalMin;
}

double FilterProductModels::GlobalMax::get()
{
	return source_globalMax;
}

IVector<FilterOptionsModels^>^ FilterProductModels::Options::get()
{
	return source_options;
}

void FilterProductModels::Options::set(IVector<FilterOptionsModels^>^ val)
{
	source_options = val;
}

PromoItem::PromoItem(int id, int typeId) : m_id(id), m_typeId(typeId)
{
}

int PromoItem::Id::get()
{
	return m_id;
}

int PromoItem::TypeId::get()
{
	return m_typeId;
}

PromoBannerModels::PromoBannerModels()
{
}

PromoBannerModels::PromoBannerModels(String^ id, String^ typeId, String^ name, 
	String^ mediaImage, String^ url, IVector<PromoItem^>^ promoItems)
	: source_id(id), source_typeId(typeId), source_name(name), 
	source_mediaImage(mediaImage), m_url(url), m_promoItems(promoItems)
{
}

String^ PromoBannerModels::Id::get()
{
	return source_id;
}

String^ PromoBannerModels::TypeId::get()
{
	return source_typeId;
}

String^ PromoBannerModels::Name::get()
{
	return source_name;
}

String^ PromoBannerModels::MediaImage::get()
{
	return source_mediaImage;
}

String^ PromoBannerModels::Url::get()
{
	return m_url;
}

IVector<PromoItem^>^ PromoBannerModels::PromoItems::get()
{
	return m_promoItems;
}