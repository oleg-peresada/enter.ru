#include "pch.h"
#include "TrackerCardModels.h"

using namespace EnterStore::Models;

StateCard::StateCard(bool is_buyable) : m_isbuyable(is_buyable)
{
}

bool StateCard::IsBuyable::get()
{
	return m_isbuyable;
}

PromoCard::PromoCard(int id, String^ name, String^ mediaImage)
: m_id(id), m_name(name), m_mediaImage(mediaImage)
{
}

int PromoCard::Id::get()
{
	return m_id;
}

String^ PromoCard::Name::get()
{
	return m_name;
}

String^ PromoCard::MediaImage::get()
{
	return m_mediaImage;
}

ProductCardModels::ProductCardModels(int id,
	String^ name,
	String^ token,
	String^ article,
	String^ barCode,
	String^ announce,
	String^ rating,
	double price,
	String^ media_image)
	: source_id(id), source_name(name), source_token(token), source_article(article),
	source_barCode(barCode), source_announce(announce), source_rating(rating),
	source_price(price), source_mediaImage(media_image)
{
}

int ProductCardModels::Id::get()
{
	return source_id;
}

String^ ProductCardModels::Name::get()
{
	return source_name;
}

String^ ProductCardModels::Token::get()
{
	return source_token;
}

String^ ProductCardModels::Article::get()
{
	return source_article;
}

String^ ProductCardModels::BarCode::get()
{
	return source_barCode;
}

String^ ProductCardModels::Announce::get()
{
	return source_announce;
}

String^ ProductCardModels::Rating::get()
{
	return source_rating;
}

double ProductCardModels::Price::get()
{
	return source_price;
}

String^ ProductCardModels::MediaImage::get()
{
	return source_mediaImage;
}

IVector<PromoCard^>^ ProductCardModels::LabelCard::get()
{
	return source_labelCard;
}

void ProductCardModels::LabelCard::set(IVector<PromoCard^>^ value)
{
	source_labelCard = value;
}

StateCard^ ProductCardModels::State::get()
{
	return source_state;
}

void ProductCardModels::State::set(StateCard^ value)
{
	source_state = value;
}

TrackerIntervalOrderModels::TrackerIntervalOrderModels(int id, String^ name, String^ time_begin, String^ time_end)
	: m_id(id), m_name(name), m_time_begin(time_begin), m_time_end(time_end)
{
}

int TrackerIntervalOrderModels::Id::get()
{
	return m_id;
}

String^ TrackerIntervalOrderModels::Name::get()
{
	return m_name;
}

String^ TrackerIntervalOrderModels::TimeBegin::get()
{
	return m_time_begin;
}

String^ TrackerIntervalOrderModels::TimeEnd::get()
{
	return m_time_end;
}

TrackerProductOrderModels::TrackerProductOrderModels(int id, int price, int quantity, double sum)
	: m_id(id), m_price(price), m_quantity(quantity), m_sum(sum)
{
}

int TrackerProductOrderModels::Id::get()
{
	return m_id;
}

int TrackerProductOrderModels::Price::get()
{
	return m_price;
}

int TrackerProductOrderModels::Quantity::get()
{
	return m_quantity;
}

double TrackerProductOrderModels::Sum::get()
{
	return m_sum;
}

TrackerDeliveryOrderModels::TrackerDeliveryOrderModels(int delivery_id,
	double price,
	int delivery_type_id,
	int delivery_period_id,
	String^ delivery_date) : m_delivery_id(delivery_id), m_price(price), m_delivery_type_id(delivery_type_id), 
	m_delivery_period_id(delivery_period_id), m_delivery_date(delivery_date)
{
}

int TrackerDeliveryOrderModels::DeliveryId::get()
{
	return m_delivery_id;
}

double TrackerDeliveryOrderModels::Price::get()
{
	return m_price;
}

int TrackerDeliveryOrderModels::DeliveryTypeId::get()
{
	return m_delivery_type_id;
}

int TrackerDeliveryOrderModels::DeliveryPeriodId::get()
{
	return m_delivery_period_id;
}

String^ TrackerDeliveryOrderModels::DeliveryDate::get()
{
	return m_delivery_date;
}

TrackerOrderModels::TrackerOrderModels(int id,
	int type_id,
	int status_id,
	String^ number,
	String^ number_exp,
	int user_id,
	String^ email,
	String^ last_name,
	String^ first_name,
	String^ middle_name,
	String^ phone,
	String^ mobile,
	int payment_status_id,
	int payment_id,
	String^ payment_detail,
	String^ credit_card_number,
	String^ payment_card_code,
	double sum,
	bool is_delivery,
	bool is_delivery_paid,
	int delivery_type_id,
	String^ delivery_date,
	int delivery_interval_id,
	int store_id,
	int shop_id,
	int geo_id,
	int region_id,
	String^ address,
	String^ added,
	String^ updated) : m_id(id), m_typeId(type_id), m_statusId(status_id), m_number(number), m_numberExp(number_exp),
	m_userId(user_id), m_email(email), m_lastName(last_name), m_firstName(first_name), m_middleName(middle_name),
	m_phone(phone), m_mobile(mobile), m_payment_status_id(payment_status_id), m_payment_id(payment_id),
	m_payment_detail(payment_detail), m_credit_card_number(credit_card_number), m_payment_card_code(payment_card_code),
	m_sum(sum), m_isDelivery(is_delivery), m_isDeliveryPaid(is_delivery_paid), m_delivery_date(delivery_date),
	m_delivery_interval_id(delivery_interval_id), m_store_id(store_id), m_shopId(shop_id), m_geoId(geo_id), m_regionId(region_id), m_address(address),
	m_added(added), m_updated(updated), m_productSize(0)
{
}

int TrackerOrderModels::Id::get()
{
	return m_id;
}

int TrackerOrderModels::TypeId::get()
{
	return m_typeId;
}

int TrackerOrderModels::StatusId::get()
{
	return m_statusId;
}

String^ TrackerOrderModels::Number::get()
{
	return m_number;
}

String^ TrackerOrderModels::NumberExp::get()
{
	return m_numberExp;
}

int TrackerOrderModels::UserId::get()
{
	return m_userId;
}

String^ TrackerOrderModels::Email::get()
{
	return m_email;
}

String^ TrackerOrderModels::LastName::get()
{
	return m_lastName;
}

String^ TrackerOrderModels::FirstName::get()
{
	return m_firstName;
}

String^ TrackerOrderModels::MiddleName::get()
{
	return m_middleName;
}

String^ TrackerOrderModels::Phone::get()
{
	return m_phone;
}

String^ TrackerOrderModels::Mobile::get()
{
	return m_mobile;
}

int TrackerOrderModels::PaymentStatusId::get()
{
	return m_payment_status_id;
}

int TrackerOrderModels::PaymentId::get()
{
	return m_payment_id;
}

String^ TrackerOrderModels::PaymentDetail::get()
{
	return m_payment_detail;
}

String^ TrackerOrderModels::CreditCardNumber::get()
{
	return m_credit_card_number;
}

String^ TrackerOrderModels::PaymentCardCode::get()
{
	return m_payment_card_code;
}

double TrackerOrderModels::Sum::get()
{
	return m_sum;
}

bool TrackerOrderModels::IsDelivery::get()
{
	return m_isDelivery;
}

bool TrackerOrderModels::IsDeliveryPaid::get()
{
	return m_isDeliveryPaid;
}

int TrackerOrderModels::DeliveryTypeId::get()
{
	return m_delivery_type_id;
}

String^ TrackerOrderModels::DeliveryDate::get()
{
	return m_delivery_date;
}

int TrackerOrderModels::DeliveryIntervalId::get()
{
	return m_delivery_interval_id;
}

int TrackerOrderModels::StoreId::get()
{
	return m_store_id;
}

int TrackerOrderModels::ShopId::get()
{
	return m_shopId;
}

int TrackerOrderModels::GeoId::get()
{
	return m_geoId;
}

int TrackerOrderModels::RegionId::get()
{
	return m_regionId;
}

String^ TrackerOrderModels::Address::get()
{
	return m_address;
}

String^ TrackerOrderModels::Added::get()
{
	return m_added;
}

String^ TrackerOrderModels::Updated::get()
{
	return m_updated;
}

unsigned int TrackerOrderModels::ProductSize::get()
{
	return m_productSize;
}

void TrackerOrderModels::ProductSize::set(unsigned int value)
{
	m_productSize = value;
}

IVector<TrackerIntervalOrderModels^>^ TrackerOrderModels::Interval::get()
{
	return m_interval;
}

void TrackerOrderModels::Interval::set(IVector<TrackerIntervalOrderModels^>^ value)
{
	m_interval = value;
}

IVector<TrackerProductOrderModels^>^ TrackerOrderModels::Product::get()
{
	return m_product;
}

void TrackerOrderModels::Product::set(IVector<TrackerProductOrderModels^>^ value)
{
	m_product = value;
}

IVector<TrackerDeliveryOrderModels^>^ TrackerOrderModels::Delivery::get()
{
	return m_delivery;
}

void TrackerOrderModels::Delivery::set(IVector<TrackerDeliveryOrderModels^>^ value)
{
	m_delivery = value;
}