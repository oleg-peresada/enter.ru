#include "pch.h"
#include "ReviewsCommands.h"

using namespace EnterStore;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;
using namespace Windows::Web::Http::Filters;
using namespace Windows::Web::Http::Headers;
using namespace Windows::Data::Json;
using namespace Windows::Storage::Streams;

std::wstring interface_reviews = L"reviews";
std::wstring category_reviewsList = L"list";
std::wstring category_reviewsVote = L"vote";
std::wstring category_reviewsAdd = L"add";

NewReviewAdd::NewReviewAdd(String^ pros, String^ cons, String^ extract, 
	float score, String^ author, String^ authorEmail) : m_pros(pros), m_cons(cons), m_extract(extract), 
	m_score(score), m_author(author), m_authorEmail(authorEmail)
{
}

String^ NewReviewAdd::Pros::get()
{
	return m_pros;
}

String^ NewReviewAdd::Cons::get()
{
	return m_cons;
}

String^ NewReviewAdd::Extract::get()
{
	return m_extract;
}

float NewReviewAdd::Score::get()
{
	return m_score;
}

String^ NewReviewAdd::Author::get()
{
	return m_author;
}

String^ NewReviewAdd::AuthorEmail::get()
{
	return m_authorEmail;
}

ReviewsCommands::ReviewsCommands() : m_productId(0), m_pageSize(0), m_currentPage(0), m_status(StatusReviews::None)
{
}

ReviewsCommands::ReviewsCommands(int productId) : m_productId(productId), m_pageSize(0), m_currentPage(0), m_status(StatusReviews::None)
{
}

ReviewsCommands::ReviewsCommands(int productId, int pageSize, int currentPage, StatusReviews status) : m_productId(productId), 
	m_pageSize(pageSize), m_currentPage(currentPage), m_status(status)
{
}

IAsyncOperationWithProgress<IObservableVector<ReviewModels^>^, HttpProgress>^ ReviewsCommands::ReviewsListAsync()
{
	using namespace concurrency;
	return create_async([this](progress_reporter<HttpProgress> reporter, cancellation_token token) -> task<IObservableVector<ReviewModels^>^>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["product_id"] = this->ProductId.ToString();
		
		if (PageSize > 0)
		{
			queryParameter["page_size"] = this->PageSize.ToString();
		}

		if (CurrentPage > -1)
		{
			queryParameter["current_page"] = this->CurrentPage.ToString();
		}

		if (Status != StatusReviews::None)
		{
			queryParameter["status"] = static_cast<int>(Status).ToString();
		}

		auto httpCommand = ref new HttpCommand(Helpers::reviewsQueryCommand, queryParameter);
		httpCommand->CacheReadBehavior = HttpCacheReadBehavior::MostRecent;
		auto httpOperator = httpCommand->ToReviewsHttpAsync(interface_reviews, category_reviewsList);

		return create_task(httpOperator, token).then([this](String^ content) -> IObservableVector<ReviewModels^>^
		{
			auto vect = ref new Vector<ReviewModels^>();
			auto json = JsonObject::Parse(content);

			if (json->HasKey("review_list"))
			{
				if (json->GetNamedValue("review_list")->ValueType == JsonValueType::Array)
				{
					auto jsonArray = json->GetNamedArray("review_list");
					for (const auto &item : jsonArray)
					{
						auto element = item->GetObject();
						auto reviewModel = ref new ReviewModels(element->HasKey("id") ? Helpers::ToNumber(element->GetNamedValue("id")) : 0,
							element->HasKey("origin") ? Helpers::ToString(element->GetNamedValue("origin")) : "",
							element->HasKey("type") ? Helpers::ToString(element->GetNamedValue("type")) : "",
							element->HasKey("source_id") ? Helpers::ToNumber(element->GetNamedValue("source_id")) : 0,
							element->HasKey("source_name") ? Helpers::ToString(element->GetNamedValue("source_name")) : "",
							element->HasKey("source_logo_url") ? Helpers::ToString(element->GetNamedValue("source_logo_url")) : "",
							element->HasKey("url") ? Helpers::ToString(element->GetNamedValue("url")) : "",
							element->HasKey("title") ? Helpers::ToString(element->GetNamedValue("title")) : "",
							element->HasKey("extract") ? Helpers::ToString(element->GetNamedValue("extract")) : "",
							element->HasKey("pros") ? Helpers::ToString(element->GetNamedValue("pros")) : "",
							element->HasKey("cons") ? Helpers::ToString(element->GetNamedValue("cons")) : "",
							element->HasKey("author") ? Helpers::ToString(element->GetNamedValue("author")) : "",
							element->HasKey("score") ? Helpers::ToNumber(element->GetNamedValue("score")) : 0.0f,
							element->HasKey("star_score") ? Helpers::ToNumber(element->GetNamedValue("star_score")) : 0.0f,
							element->HasKey("status") ? Helpers::ToNumber(element->GetNamedValue("status")) : 0,
							element->HasKey("date") ? Helpers::ToString(element->GetNamedValue("date")) : "");

						vect->Append(reviewModel);
					}
				}
				
				return vect;
			}

		},task_continuation_context::use_current())
			.then(TaskExceptionExtensions<IObservableVector<ReviewModels^>^>(), 
			task_continuation_context::use_current());
	});
}

IAsyncAction^ ReviewsCommands::ReviewVoteAsync(IVector<int>^ valueList, FlagReviewsVote newflag, FlagReviewsVote oldFlag)
{
	using namespace concurrency;
	return create_async([this, valueList, oldFlag, newflag](cancellation_token token) -> task<void>
	{
		std::wstringstream ss;
		bool flag = true;
		for (const auto &item : valueList)
		{
			ss << item;
			
			if (true) flag = false;
			else ss << L",";
		}

		std::map<String^, String^> queryParameter;
		queryParameter["reviews_list"] = StringReference(ss.str().c_str());
		queryParameter["flag"] = static_cast<int>(oldFlag).ToString();
		queryParameter["value"] = static_cast<int>(newflag).ToString();

		auto httpCommand = ref new HttpCommand(Helpers::reviewsQueryCommand, queryParameter);
		auto httpOperator = httpCommand->ToReviewsHttpAsync(interface_reviews, category_reviewsVote);

		return create_task(httpOperator, token).then([this](String^ content) -> void
		{

		}).then(TaskExceptionExtensions<void>(), task_continuation_context::use_current());
	});
}

IAsyncOperation<bool>^ ReviewsCommands::ReviewAddAsync(NewReviewAdd^ newValue)
{
	using namespace concurrency;
	return create_async([this, newValue](cancellation_token token) -> task<bool>
	{
		std::map<String^, String^> queryParameter;
		queryParameter["product_id"] = ProductId.ToString();
		
		auto sendJson = ref new JsonObject();
		sendJson->SetNamedValue("pros", JsonValue::CreateStringValue(newValue->Pros));
		sendJson->SetNamedValue("cons", JsonValue::CreateStringValue(newValue->Cons));
		sendJson->SetNamedValue("extract", JsonValue::CreateStringValue(newValue->Extract));
		sendJson->SetNamedValue("score", JsonValue::CreateNumberValue(newValue->Score));
		sendJson->SetNamedValue("author", JsonValue::CreateStringValue(newValue->Author));
		sendJson->SetNamedValue("author_email", JsonValue::CreateStringValue(newValue->AuthorEmail));

		auto contentString = ref new HttpStringContent(sendJson->Stringify(), UnicodeEncoding::Utf8, "application/json");
		auto httpCommand = ref new HttpCommand(Helpers::reviewsQueryCommand, queryParameter, HttpMethod::Post, contentString);
		auto httpOperator = httpCommand->ToReviewsHttpAsync(interface_reviews, category_reviewsAdd);

		return create_task(httpOperator, token).then([this](String^ content) -> bool
		{
			auto json = JsonObject::Parse(content);
			if (json->HasKey("success"))
			{
				return Helpers::ToBool(json->GetNamedValue("success"));
			}
			else
			{
				return false;
			}

		}, task_continuation_context::use_current()).then(TaskExceptionExtensions<bool>(), task_continuation_context::use_current());
	});
}

int ReviewsCommands::ProductId::get()
{
	return m_productId;
}

int ReviewsCommands::PageSize::get()
{
	return m_pageSize;
}

int ReviewsCommands::CurrentPage::get()
{
	return m_currentPage;
}

StatusReviews ReviewsCommands::Status::get()
{
	return m_status;
}