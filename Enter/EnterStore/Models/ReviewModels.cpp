#include "pch.h"
#include "ReviewModels.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

using namespace EnterStore;
using namespace EnterStore::Models;

ReviewModels::ReviewModels(int id,
	String^ origin,
	String^ type,
	int sourceId,
	String^ sourceName,
	String^ sourceLogoName,
	String^ url,
	String^ title,
	String^ extract,
	String^ pros,
	String^ cons,
	String^ author,
	float score,
	float scoreStar,
	int status,
	String^ date) : m_id(id), m_origin(origin), m_type(type), m_sourceId(sourceId), m_sourceName(sourceName),
	m_sourceLogoName(sourceLogoName), m_url(url), m_title(title), m_extract(extract), m_pros(pros), m_cons(cons),
	m_author(author), m_score(score), m_scoreStar(scoreStar), m_status(status), m_date(date)
{
}

int ReviewModels::Id::get()
{
	return m_id;
}

String^ ReviewModels::Origin::get()
{
	return m_origin;
}

String^ ReviewModels::Type::get()
{
	return m_type;
}

int ReviewModels::SourceId::get()
{
	return m_sourceId;
}

String^ ReviewModels::SourceName::get()
{
	return m_sourceName;
}

String^ ReviewModels::SourceLogoName::get()
{
	return m_sourceLogoName;
}

String^ ReviewModels::Url::get()
{
	return m_url;
}

String^ ReviewModels::Title::get()
{
	return m_title;
}

String^ ReviewModels::Extract::get()
{
	return m_extract;
}

String^ ReviewModels::Pros::get()
{
	return m_pros;
}

String^ ReviewModels::Cons::get()
{
	return m_cons;
}

String^ ReviewModels::Author::get()
{
	return m_author;
}

float ReviewModels::Score::get()
{
	return m_score;
}

float ReviewModels::ScoreStar::get()
{
	return m_scoreStar;
}

int ReviewModels::Status::get()
{
	return m_status;
}

String^ ReviewModels::Date::get()
{
	return m_date;
}