#pragma once

#include <ppltasks.h>
#include <collection.h>

#include "DataModel\IncrementLoadingBase.h"

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Data;

namespace Enter
{
	namespace DataModel
	{
		public delegate void IncrementLoadingProgressHandler(Object^ sender, bool isProgress);

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class IncrementFilterLoading sealed : public IncrementLoadingBase
		{
		public:
			event IncrementLoadingProgressHandler^ IncrementLoadingProgress;
		internal:
			IncrementFilterLoading(int regionId, 
				int categoryId, 
				unsigned int limit, 
				unsigned int offset);

			virtual Concurrency::task<IVector<Object^>^> LoadMoreItemsOverride(Concurrency::cancellation_token c, unsigned int count) override;
			virtual bool HasMoreItemsOverride() override;

			property int RegionId
			{
				int get();
			}

			property int CategoryId
			{
				int get();
			}

			property unsigned int Limit
			{
				unsigned int get();
			}

			property unsigned int Offset
			{
				unsigned int get();
				void set(unsigned int index);
			}

			property SortProduct^ SortParameter
			{
				SortProduct^ get();
				void set(SortProduct^ value);
			}

			property IVector<Object^>^ Filters
			{
				IVector<Object^>^ get();
				void set(IVector<Object^>^ value);
			}
		private:
			int source_regionId;
			int source_categoryId;
			unsigned int source_limit;
			unsigned int source_offset;
			bool busy;
			IVector<Object^>^ source_filters;
			SortProduct^ source_sortParameter;

			event IncrementLoadingProgressHandler^ OnIncrementLoadingProgressHandler
			{
				EventRegistrationToken add(IncrementLoadingProgressHandler^ handler)
				{
					return IncrementLoadingProgress += handler;
				}

				void remove(EventRegistrationToken token)
				{
					IncrementLoadingProgress -= token;
				}

				void raise(Object^ sender, bool isProgress)
				{
					IncrementLoadingProgress(sender, isProgress);
				}
			}
		};
	}
}