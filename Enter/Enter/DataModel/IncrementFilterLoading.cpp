#include "pch.h"
#include "IncrementFilterLoading.h"

using namespace Enter;
using namespace Enter::DataModel;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::Web::Http;

IncrementFilterLoading::IncrementFilterLoading(int regionId, 
	int categoryId, 
	unsigned int limit, 
	unsigned int offset) : source_regionId(regionId), 
	source_categoryId(categoryId), 
	source_limit(limit), 
	source_offset(offset),
	busy(false)
{
}

concurrency::task<IVector<Object^>^> IncrementFilterLoading::LoadMoreItemsOverride(concurrency::cancellation_token token, unsigned int count)
{
	IncrementLoadingProgress(this, true);
	busy = false;
	return concurrency::task<IVector<Object^>^>([=]()-> concurrency::task <IVector<Object^>^>
	{
		SortProduct^ sort = SortParameter == nullptr ? ref new SortProduct("default", SortCommon::asc) : SortParameter;
		auto query = ref new FilterProductQuery(CategoryId, Limit, Offset, sort);
		query->Filters = this->Filters == nullptr ? nullptr : this->Filters;

		auto product = ref new ProductListCommands(RegionId, query);
		auto operation = product->ProductOperationAsync();
		return concurrency::create_task(operation).then([this](IVector<ProductCardModels^>^ content) -> IVector<Object^>^
		{
			auto vect = ref new Vector<Object^>(begin(content), end(content));

			if (vect->Size == 0)
			{
				busy = true;
			}

			Offset += vect->Size;
			IncrementLoadingProgress(this, false);

			return vect;
		}).then(TaskException<IVector<Object^>^>(), concurrency::task_continuation_context::use_current());
	});
}

bool IncrementFilterLoading::HasMoreItemsOverride()
{
	if (busy)
	{
		return false;
	}

	if (!busy) busy = true;

	return busy;
}

int IncrementFilterLoading::RegionId::get()
{
	return source_regionId;
}

int IncrementFilterLoading::CategoryId::get()
{
	return source_categoryId;
}

unsigned int IncrementFilterLoading::Limit::get()
{
	return source_limit;
}

unsigned int IncrementFilterLoading::Offset::get()
{
	return source_offset;
}

void IncrementFilterLoading::Offset::set(unsigned int index)
{
	source_offset = index;
}

SortProduct^ IncrementFilterLoading::SortParameter::get()
{
	return source_sortParameter;
}

void IncrementFilterLoading::SortParameter::set(SortProduct^ value)
{
	source_sortParameter = value;
}

IVector<Object^>^ IncrementFilterLoading::Filters::get()
{
	return source_filters;
}

void IncrementFilterLoading::Filters::set(IVector<Object^>^ value)
{
	source_filters = value;
}