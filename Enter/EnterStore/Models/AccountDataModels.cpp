#include "pch.h"
#include "AccountDataModels.h"

using namespace EnterStore::Models;

PickupDateShopListModels::PickupDateShopListModels(int id, Array<int>^ interval_list)
	: source_id(id), source_intervallist(interval_list)
{
}

int PickupDateShopListModels::Id::get()
{
	return source_id;
}

Array<int>^ PickupDateShopListModels::IntervalList::get()
{
	return source_intervallist;
}

PickupDateListModels::PickupDateListModels(String^ dateTime, IVector<PickupDateShopListModels^>^ vectShop)
	: source_dateTime(dateTime), source_vectShop(vectShop)
{
}

String^ PickupDateListModels::DateTime::get()
{
	return source_dateTime;
}

IVector<PickupDateShopListModels^>^ PickupDateListModels::VectShop::get()
{
	return source_vectShop;
}

StandartDateListModels::StandartDateListModels(String^ dateTime, Array<int>^ intervalList)
	: source_dateTime(dateTime), source_intervalList(intervalList)
{
}

String^ StandartDateListModels::DateTime::get()
{
	return source_dateTime;
}

Array<int>^ StandartDateListModels::IntervalList::get()
{
	return source_intervalList;
}

PickupUpNowDeliveryModels::PickupUpNowDeliveryModels(unsigned int id, 
	String^ name, 
	String^ token, 
	String^ description) : source_Id(id), source_name(name), source_Token(token), source_description(description)
{
}

unsigned int PickupUpNowDeliveryModels::Id::get()
{
	return source_Id;
}

String^ PickupUpNowDeliveryModels::Name::get()
{
	return source_name;
}

String^ PickupUpNowDeliveryModels::Token::get()
{
	return source_Token;
}

String^ PickupUpNowDeliveryModels::Description::get()
{
	return source_description;
}

IVector<PickupDateListModels^>^ PickupUpNowDeliveryModels::VectorDateInterval::get()
{
	return source_VectorDateInterval;
}

void PickupUpNowDeliveryModels::VectorDateInterval::set(IVector<PickupDateListModels^>^ val)
{
	source_VectorDateInterval = val;
}

PickupDeliveryModels::PickupDeliveryModels(unsigned int id, 
	String^ name, 
	String^ token, 
	int deliveryId, 
	double price) : source_id(id), source_name(name),
	source_token(token), source_deliveryId(deliveryId), source_price(price)
{
}

unsigned int PickupDeliveryModels::Id::get()
{
	return source_id;
}

String^ PickupDeliveryModels::Name::get()
{
	return source_name;
}

String^ PickupDeliveryModels::Token::get()
{
	return source_token;
}

int PickupDeliveryModels::DeliveryId::get()
{
	return source_deliveryId;
}

double PickupDeliveryModels::Price::get()
{
	return source_price;
}

IVector<PickupDateListModels^>^ PickupDeliveryModels::VectorDateInterval::get()
{
	return source_VectorDateInterval;
}

void PickupDeliveryModels::VectorDateInterval::set(IVector<PickupDateListModels^>^ val)
{
	source_VectorDateInterval = val;
}

StandartDeliveryModels::StandartDeliveryModels(unsigned int id,
	String^ name,
	String^ token,
	int deliveryId,
	double price) : source_id(id), source_name(name),
	source_token(token), source_deliveryId(deliveryId), source_price(price)
{
}

unsigned int StandartDeliveryModels::Id::get()
{
	return source_id;
}

String^ StandartDeliveryModels::Name::get()
{
	return source_name;
}

String^ StandartDeliveryModels::Token::get()
{
	return source_token;
}

int StandartDeliveryModels::DeliveryId::get()
{
	return source_deliveryId;
}

double StandartDeliveryModels::Price::get()
{
	return source_price;
}

IVector<StandartDateListModels^>^ StandartDeliveryModels::Datalist::get()
{
	return source_datalist;
}

void StandartDeliveryModels::Datalist::set(IVector<StandartDateListModels^>^ val)
{
	source_datalist = val;
}

DeliveryModeListModels::DeliveryModeListModels(int id, String^ token)
	: source_id(id), source_token(token)
{
}

int DeliveryModeListModels::Id::get()
{
	return source_id;
}

String^ DeliveryModeListModels::Token::get()
{
	return source_token;
}

PickupDeliveryModels^ DeliveryModeListModels::PickupDelivery::get()
{
	return source_pickupDelivery;
}

void DeliveryModeListModels::PickupDelivery::set(PickupDeliveryModels^ val)
{
	source_pickupDelivery = val;
}

PickupUpNowDeliveryModels^ DeliveryModeListModels::PickupDeliveryUp::get()
{
	return source_pickupDeliveryUp;
}

void DeliveryModeListModels::PickupDeliveryUp::set(PickupUpNowDeliveryModels^ val)
{
	source_pickupDeliveryUp = val;
}

StandartDeliveryModels^ DeliveryModeListModels::StandartDelivery::get()
{
	return source_standartDelivery;
}

void DeliveryModeListModels::StandartDelivery::set(StandartDeliveryModels^ val)
{
	source_standartDelivery = val;
}

IntervalListModels::IntervalListModels(int id, String^ ui, String^ timeBegin, String^ timeEnd)
	: source_id(id), source_ui(ui), source_TimeBegin(timeBegin), source_TimeEnd(timeEnd)
{
}

int IntervalListModels::Id::get()
{
	return source_id;
}

String^ IntervalListModels::Ui::get()
{
	return source_ui;
}

String^ IntervalListModels::TimeBegin::get()
{
	return source_TimeBegin;
}

String^ IntervalListModels::TimeEnd::get()
{
	return source_TimeEnd;
}

OrderShopListModels::OrderShopListModels(int id, String^ ui, 
	String^ name, int geoId, 
	String^ address, String^ workingTime, double coordLat, double coordLong)
	: source_id(id), source_ui(ui), source_name(name),
	source_geoId(geoId), source_address(address), source_workingTime(workingTime), 
	source_coordLat(coordLat), source_coordLong(coordLong)
{
}

int OrderShopListModels::Id::get()
{
	return source_id;
}

String^ OrderShopListModels::Ui::get()
{
	return source_ui;
}

String^ OrderShopListModels::Name::get()
{
	return source_name;
}

int OrderShopListModels::GeoId::get()
{
	return source_geoId;
}

String^ OrderShopListModels::Address::get()
{
	return source_address;
}

String^ OrderShopListModels::WorkingTime::get()
{
	return source_workingTime;
}

double OrderShopListModels::CoordLat::get()
{
	return source_coordLat;
}

double OrderShopListModels::CoordLong::get()
{
	return source_coordLong;
}

OrderCalcModels::OrderCalcModels(IVector<DeliveryModeListModels^>^ mode,
	IVector<IntervalListModels^>^ intervalList,
	IVector<OrderShopListModels^>^ shopList)
	: source_Mode(mode), source_intervalList(intervalList), source_OrderShopList(shopList)
{
}

IVector<DeliveryModeListModels^>^ OrderCalcModels::Mode::get()
{
	return source_Mode;
}

IVector<IntervalListModels^>^ OrderCalcModels::IntervalList::get()
{
	return source_intervalList;
}

IVector<OrderShopListModels^>^ OrderCalcModels::ShopList::get()
{
	return source_OrderShopList;
}

UserContentModels::UserContentModels(int id, String^ ui,
	String^ firstName, String^ lastName,
	String^ middleName, String^ sex,
	String^ occupation, String^ email,
	String^ phone, String^ mobilePhone,
	String^ skype, String^ birthday) : source_id(id), source_ui(ui),
	source_firstName(firstName), source_lastName(lastName), source_middleName(middleName),
	source_sex(sex), source_occupation(occupation), source_email(email),
	source_phone(phone), source_mobilePhone(mobilePhone),
	source_skype(skype), source_birthday(birthday)
{
}

int UserContentModels::Id::get()
{
	return source_id;
}

String^ UserContentModels::Ui::get()
{
	return source_ui;
}

String^ UserContentModels::FirstName::get()
{
	return source_firstName;
}

String^ UserContentModels::LastName::get()
{
	return source_lastName;
}

String^ UserContentModels::MiddleName::get()
{
	return source_middleName;
}

String^ UserContentModels::Sex::get()
{
	return source_sex;
}

String^ UserContentModels::Occupation::get()
{
	return source_occupation;
}

String^ UserContentModels::Email::get()
{
	return source_email;
}

String^ UserContentModels::Phone::get()
{
	return source_phone;
}

String^ UserContentModels::MobilePhone::get()
{
	return source_mobilePhone;
}

String^ UserContentModels::Skype::get()
{
	return source_skype;
}

String^ UserContentModels::Birtday::get()
{
	return source_birthday;
}

PersonalDataUpdateModels::PersonalDataUpdateModels(String^ firstName, String^ lastName, String^ middleName,
	String^ sex, String^ occupation, String^ email, String^ phone,
	String^ mobilePhone, String^ birtday, String^ skype) : source_firstName(firstName), source_lastName(lastName),
	source_middleName(middleName), source_sex(sex), source_Occupation(occupation),
	source_Email(email), source_phone(phone), source_mobilePhone(mobilePhone),
	source_birthday(birtday), source_skype(skype)
{
}

String^ PersonalDataUpdateModels::FirstName::get()
{
	return source_firstName;
}

String^ PersonalDataUpdateModels::LastName::get()
{
	return source_lastName;
}

String^ PersonalDataUpdateModels::MiddleName::get()
{
	return source_middleName;
}

String^ PersonalDataUpdateModels::Sex::get()
{
	return source_sex;
}

String^ PersonalDataUpdateModels::Occupation::get()
{
	return source_Occupation;
}

String^ PersonalDataUpdateModels::Email::get()
{
	return source_Email;
}

String^ PersonalDataUpdateModels::Phone::get()
{
	return source_phone;
}

String^ PersonalDataUpdateModels::MobilePhone::get()
{
	return source_mobilePhone;
}

String^ PersonalDataUpdateModels::Birthday::get()
{
	return source_birthday;
}

String^ PersonalDataUpdateModels::Skype::get()
{
	return source_skype;
}