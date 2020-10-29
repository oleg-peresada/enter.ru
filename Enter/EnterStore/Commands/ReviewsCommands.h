#pragma once

#include "HttpCommand.h"
#include "Helpers.h"
#include "Models\ReviewModels.h"

#include <string>
#include <collection.h>
#include <sstream>

using namespace EnterStore;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Web::Http;

namespace EnterStore
{
	namespace Commands
	{
		[Platform::Metadata::Flags]
		public enum class StatusReviews : unsigned int
		{
			NewStatus = 0,
			Work = 1,
			Adopted = 2,
			Rejected = 3,
			None = 4,
		};

		[Platform::Metadata::Flags]
		public enum class FlagReviewsVote : unsigned int
		{
			Bad = 0,
			Good = 1,
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class NewReviewAdd sealed
		{
		public:
			NewReviewAdd(String^ pros, String^ cons, String^ extract, float score, String^ author, String^ authorEmail);

			property String^ Pros
			{
				String^ get();
			}

			property String^ Cons
			{
				String^ get();
			}

			property String^ Extract
			{
				String^ get();
			}

			property float Score
			{
				float get();
			}

			property String^ Author
			{
				String^ get();
			}

			property String^ AuthorEmail
			{
				String^ get();
			}
		private:
			String^ m_pros;
			String^ m_cons;
			String^ m_extract;
			float m_score;
			String^ m_author;
			String^ m_authorEmail;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ReviewsCommands sealed
		{
		public:
			ReviewsCommands();
			ReviewsCommands(int productId);
			ReviewsCommands(int productId, int pageSize, int currentPage, StatusReviews status);
			IAsyncOperationWithProgress<IObservableVector<ReviewModels^>^, HttpProgress>^ ReviewsListAsync();
			IAsyncAction^ ReviewVoteAsync(IVector<int>^ valueList, FlagReviewsVote newflag, FlagReviewsVote oldFlag);
			IAsyncOperation<bool>^ ReviewAddAsync(NewReviewAdd^ newValue);

			property int ProductId
			{
				int get();
			}

			property int PageSize
			{
				int get();
			}

			property int CurrentPage
			{
				int get();
			}

			property StatusReviews Status
			{
				StatusReviews get();
			}
		private:
			int m_productId;
			int m_pageSize;
			int m_currentPage;
			StatusReviews m_status;
		};
	}
}