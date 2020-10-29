#include "pch.h"
#include "IncrementLoadingBase.h"

using namespace Enter::DataModel;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Data;

IncrementLoadingBase::IncrementLoadingBase()
{
	_storage = ref new Vector<Object^>();
	_storage->VectorChanged += ref new VectorChangedEventHandler<Object^>(this, &IncrementLoadingBase::_storageVectorChanged);
	_busy = false;
	_isVectorChangedObserved = false;
}

Concurrency::task<LoadMoreItemsResult> IncrementLoadingBase::LoadMoreItemsAsync(Concurrency::cancellation_token c, unsigned int count)
{
	try
	{
		return Concurrency::task<void>([=]() {}).then([=]() 
		{
			return LoadMoreItemsOverride(c, count);
		}).then([=](IVector<Platform::Object^>^ items) -> LoadMoreItemsResult 
		{
			auto baseIndex = _storage->Size;
			for (unsigned int i = 0; i < items->Size; i++)
			{
				_storage->Append(items->GetAt(i));
			}
			LoadMoreItemsResult result;
			result.Count = items->Size;
			return result;
		}, Concurrency::task_continuation_context::use_current());
	}
	catch (Exception^ e)
	{
		throw e;
	}
}

Object^ IncrementLoadingBase::default::get(int index)
{
	return _storage->GetAt(index);
}

void IncrementLoadingBase::default::set(int index, Object^ value)
{
	_storage->SetAt(index, value);
}

Concurrency::task<IVector<Object^>^>  IncrementLoadingBase::LoadMoreItemsOverride(Concurrency::cancellation_token c, unsigned int count)
{
	return Concurrency::task<IVector<Object^>^>([=]() -> IVector<Object^>^ 
	{
		auto items = ref new Vector<Object^>();
		return items;
	});
}

bool IncrementLoadingBase::HasMoreItemsOverride()
{
	return false;
}

IAsyncOperation<LoadMoreItemsResult>^ IncrementLoadingBase::LoadMoreItemsAsync(unsigned int count)
{
	if (_busy)
	{
		throw ref new Platform::FailureException("Only one operation in flight at a time");
	}

	_busy = true;

	return Concurrency::create_async([=](Concurrency::cancellation_token c) 
	{
		return LoadMoreItemsAsync(c, count).then([=](LoadMoreItemsResult result) -> LoadMoreItemsResult 
		{
			_busy = false;
			return result;
		});
	});
}

bool IncrementLoadingBase::HasMoreItems::get()
{
	return HasMoreItemsOverride();
}