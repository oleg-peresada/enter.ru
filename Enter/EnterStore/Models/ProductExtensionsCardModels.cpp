#include "pch.h"
#include "ProductExtensionsCardModels.h"

using namespace EnterStore;
using namespace EnterStore::Models;

ProductViewTypeModel::ProductViewTypeModel(int id, String^ name, String^ token, String^ mediaImage) 
	: m_id(id), m_name(name), m_token(token), m_mediaImage(mediaImage)
{
}

int ProductViewTypeModel::Id::get()
{
	return m_id;
}

String^ ProductViewTypeModel::Name::get()
{
	return m_name;
}

String^ ProductViewTypeModel::Token::get()
{
	return m_token;
}

String^ ProductViewTypeModel::MediaImage::get()
{
	return m_mediaImage;
}

OptionViewTypeModel::OptionViewTypeModel(String^ value, ProductViewTypeModel^ product) : m_value(value), m_product(product)
{
}

String^ OptionViewTypeModel::Value::get()
{
	return m_value;
}

ProductViewTypeModel^ OptionViewTypeModel::Product::get()
{
	return m_product;
}

PropertyViewTypeModel::PropertyViewTypeModel(int id, int typeId, String^ name, String^ unit, 
	bool isMultiple, IVector<OptionViewTypeModel^>^ option) : m_id(id), m_typeId(typeId), m_name(name),
	m_unit(unit), m_isMultiple(isMultiple), m_option(option)
{
}

int PropertyViewTypeModel::Id::get()
{
	return m_id;
}

int PropertyViewTypeModel::TypeId::get()
{
	return m_typeId;
}

String^ PropertyViewTypeModel::Name::get()
{
	return m_name;
}

String^ PropertyViewTypeModel::Unit::get()
{
	return m_unit;
}

bool PropertyViewTypeModel::IsMultiple::get()
{
	return m_isMultiple;
}

IVector<OptionViewTypeModel^>^ PropertyViewTypeModel::Option::get()
{
	return m_option;
}

PromoLabel::PromoLabel(int id, String^ mediaImage, String^ name) : m_id(id), m_mediaImage(mediaImage), m_name(name)
{
}

int PromoLabel::Id::get()
{
	return m_id;
}

String^ PromoLabel::MediaImage::get()
{
	return m_mediaImage;
}

String^ PromoLabel::Name::get()
{
	return m_name;
}

OptionExtensionsCardModels::OptionExtensionsCardModels(int id, String^ value, String^ hint)
	: source_id(id), source_value(value), source_hint(hint)
{
}

int OptionExtensionsCardModels::Id::get()
{
	return source_id;
}

String^ OptionExtensionsCardModels::Value::get()
{
	return source_value;
}

String^ OptionExtensionsCardModels::Hint::get()
{
	return source_hint;
}

PropertyExtensionsCardModels::PropertyExtensionsCardModels(int id,
	unsigned int groupId,
	int typeId,
	String^ name,
	String^ hint,
	String^ value,
	String^ valueHint,
	String^ unit)
	: source_id(id), source_groupId(groupId), source_typeId(typeId), source_name(name), source_hint(hint),
	source_value(value), source_valueHint(valueHint), source_unit(unit)
{
}

int PropertyExtensionsCardModels::Id::get()
{
	return source_id;
}

unsigned int PropertyExtensionsCardModels::GroupId::get()
{
	return source_groupId;
}

int PropertyExtensionsCardModels::TypeId::get()
{
	return source_typeId;
}

String^ PropertyExtensionsCardModels::Name::get()
{
	return source_name;
}

String^ PropertyExtensionsCardModels::Hint::get()
{
	return source_hint;
}

String^ PropertyExtensionsCardModels::Value::get()
{
	return source_value;
}

String^ PropertyExtensionsCardModels::ValueHint::get()
{
	return source_valueHint;
}

String^ PropertyExtensionsCardModels::Unit::get()
{
	return source_unit;
}

IVector<OptionExtensionsCardModels^>^ PropertyExtensionsCardModels::Option::get()
{
	return source_option;
}

void PropertyExtensionsCardModels::Option::set(IVector<OptionExtensionsCardModels^>^ val)
{
	source_option = val;
}

PropertyGroupExetensionsModels::PropertyGroupExetensionsModels(unsigned int id, String^ name, unsigned int position) 
	: source_id(id), source_name(name), source_position(position)
{
}

unsigned int PropertyGroupExetensionsModels::Id::get()
{
	return source_id;
}

String^ PropertyGroupExetensionsModels::Name::get()
{
	return source_name;
}

unsigned int PropertyGroupExetensionsModels::Position::get()
{
	return source_position;
}

MediaExtensionsCardModels::MediaExtensionsCardModels(int id, String^ source)
	: source_id(id), source_Source(source)
{
}

int MediaExtensionsCardModels::Id::get()
{
	return source_id;
}

String^ MediaExtensionsCardModels::Source::get()
{
	return source_Source;
}

StockCardModels::StockCardModels(int storeId, int shopId, unsigned int quantity)
	: source_storeId(storeId), source_shopId(shopId), source_quantity(quantity)
{
}

int StockCardModels::StoreId::get()
{
	return source_storeId;
}

int StockCardModels::ShopId::get()
{
	return source_shopId;
}

unsigned int StockCardModels::Quantity::get()
{
	return source_quantity;
}

StateCardModels::StateCardModels(bool isShop, bool isStore, bool isBuyable)
	: source_IsShop(isShop), source_IsStore(isStore), source_IsBuyable(isBuyable)
{
}

bool StateCardModels::IsShop::get()
{
	return source_IsShop;
}

bool StateCardModels::IsStore::get()
{
	return source_IsStore;
}

bool StateCardModels::IsBuyable::get()
{
	return source_IsBuyable;
}

ProductExtensionsCardModels::ProductExtensionsCardModels(int id,
	int typeId,
	String^ name,
	String^ token,
	String^ article,
	String^ description,
	double price,
	double priceOld,
	String^ mediaImage)
	: source_Id(id), source_typeId(typeId), source_name(name), source_token(token),
	source_article(article), source_description(description),
	source_price(price), source_priceOld(priceOld), source_mediaImage(mediaImage)
{
}

int ProductExtensionsCardModels::Id::get()
{
	return source_Id;
}

int ProductExtensionsCardModels::TypeId::get()
{
	return source_typeId;
}

String^ ProductExtensionsCardModels::Name::get()
{
	return source_name;
}

String^ ProductExtensionsCardModels::Token::get()
{
	return source_token;
}

String^ ProductExtensionsCardModels::Article::get()
{
	return source_article;
}

String^ ProductExtensionsCardModels::Description::get()
{
	return source_description;
}

double ProductExtensionsCardModels::Price::get()
{
	return source_price;
}

double ProductExtensionsCardModels::PriceOld::get()
{
	return source_priceOld;
}

String^ ProductExtensionsCardModels::MediaImage::get()
{
	return source_mediaImage;
}

IVector<PropertyExtensionsCardModels^>^ ProductExtensionsCardModels::Property::get()
{
	return source_property;
}

void ProductExtensionsCardModels::Property::set(IVector<PropertyExtensionsCardModels^>^ val)
{
	source_property = val;
}

IVector<PropertyGroupExetensionsModels^>^ ProductExtensionsCardModels::PropertyGroup::get()
{
	return source_propertyGroup;
}

void ProductExtensionsCardModels::PropertyGroup::set(IVector<PropertyGroupExetensionsModels^>^ value)
{
	source_propertyGroup = value;
}

IVector<PromoLabel^>^ ProductExtensionsCardModels::Label::get()
{
	return source_label;
}

void ProductExtensionsCardModels::Label::set(IVector<PromoLabel^>^ value)
{
	source_label = value;
}

IVector<MediaExtensionsCardModels^>^ ProductExtensionsCardModels::Media::get()
{
	return source_media;
}

void ProductExtensionsCardModels::Media::set(IVector<MediaExtensionsCardModels^>^ val)
{
	source_media = val;
}

IVector<PropertyViewTypeModel^>^ ProductExtensionsCardModels::ModelProperty::get()
{
	return source_modelProperty;
}

void ProductExtensionsCardModels::ModelProperty::set(IVector<PropertyViewTypeModel^>^ value)
{
	source_modelProperty = value;
}

StateCardModels^ ProductExtensionsCardModels::State::get()
{
	return source_state;
}

void ProductExtensionsCardModels::State::set(StateCardModels^ val)
{
	source_state = val;
}

StockCardModels^ ProductExtensionsCardModels::Stock::get()
{
	return source_stock;
}

void ProductExtensionsCardModels::Stock::set(StockCardModels^ val)
{
	source_stock = val;
}

IVector<int>^ ProductExtensionsCardModels::Accessories::get()
{
	return source_accessories;
}

void ProductExtensionsCardModels::Accessories::set(IVector<int>^ value)
{
	source_accessories = value;
}