#pragma once

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace EnterStore
{
	namespace Models
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ReviewModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ Origin
			{
				String^ get();
			}

			property String^ Type
			{
				String^ get();
			}

			property int SourceId
			{
				int get();
			}

			property String^ SourceName
			{
				String^ get();
			}

			property String^ SourceLogoName
			{
				String^ get();
			}

			property String^ Url
			{
				String^ get();
			}

			property String^ Title
			{
				String^ get();
			}

			property String^ Extract
			{
				String^ get();
			}

			property String^ Pros
			{
				String^ get();
			}

			property String^ Cons
			{
				String^ get();
			}

			property String^ Author
			{
				String^ get();
			}

			property float Score
			{
				float get();
			}

			property float ScoreStar
			{
				float get();
			}

			property int Status
			{
				int get();
			}

			property String^ Date
			{
				String^ get();
			}
		internal:
			ReviewModels(int id, 
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
				String^ date);
		private:
			int m_id;
			String^ m_origin;
			String^ m_type;
			int m_sourceId;
			String^ m_sourceName;
			String^ m_sourceLogoName;
			String^ m_url;
			String^ m_title;
			String^ m_extract;
			String^ m_pros;
			String^ m_cons;
			String^ m_author;
			float m_score;
			float m_scoreStar;
			int m_status;
			String^ m_date;
		};
	}
}