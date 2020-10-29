#pragma once

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
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class IncrementLoadingBase : DependencyObject, IBindableObservableVector, ISupportIncrementalLoading
		{
		internal:
			IncrementLoadingBase();
			Concurrency::task<LoadMoreItemsResult> LoadMoreItemsAsync(Concurrency::cancellation_token c, unsigned int count);

			property Object^ default[int]
			{
				Object^ get(int index);
				void set(int index, Object^ value);
			}

			virtual Concurrency::task<IVector<Object^>^> LoadMoreItemsOverride(Concurrency::cancellation_token c, unsigned int count);
			virtual bool HasMoreItemsOverride();
		public:
			virtual IAsyncOperation<LoadMoreItemsResult>^ LoadMoreItemsAsync(unsigned int count);

			property bool HasMoreItems
			{
				virtual bool get();
			}

			event BindableVectorChangedEventHandler^ VectorChanged
			{
				virtual EventRegistrationToken add(BindableVectorChangedEventHandler^ e)
				{
					_isVectorChangedObserved = true;
					return _privateVectorChanged += e;
				}
				virtual void remove(EventRegistrationToken t)
				{
					_privateVectorChanged -= t;
				}
				void raise(IBindableObservableVector^ vector, Object^ e)
				{
					if (_isVectorChangedObserved)
					{
						_privateVectorChanged(vector, e);
					}
				}
			}

			virtual IBindableIterator^ First()
			{
				return dynamic_cast<IBindableIterator^>(_storage->First());
			}

			virtual void Append(Object^ value)
			{
				_storage->Append(value);
			}

			virtual void Clear()
			{
				_storage->Clear();
			}

			virtual Object^ GetAt(unsigned int index)
			{
				return _storage->GetAt(index);
			}

			virtual IBindableVectorView^ GetView()
			{
				return safe_cast<IBindableVectorView^>(_storage->GetView());
			}

			virtual bool IndexOf(Object^ value, unsigned int* index)
			{
				return _storage->IndexOf(value, index);
			}

			virtual void InsertAt(unsigned int index, Object^ value)
			{
				_storage->InsertAt(index, value);
			}

			virtual void RemoveAt(unsigned int index)
			{
				_storage->RemoveAt(index);
			}

			virtual void RemoveAtEnd()
			{
				_storage->RemoveAtEnd();
			}

			virtual void SetAt(unsigned int index, Object^ value)
			{
				_storage->SetAt(index, value);
			}

			virtual property unsigned int Size
			{
				unsigned int get() { return _storage->Size; }
			}

		private:
			Vector<Object^>^ _storage;
			bool _busy;
			bool _isVectorChangedObserved;
			event BindableVectorChangedEventHandler^ _privateVectorChanged;

			void _storageVectorChanged(IObservableVector<Object^>^ sender, IVectorChangedEventArgs^ e)
			{
				if (_isVectorChangedObserved)
				{
					VectorChanged(this, e);
				}
			}
		};
	}
}