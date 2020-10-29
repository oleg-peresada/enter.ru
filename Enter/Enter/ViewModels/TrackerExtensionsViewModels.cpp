#include "pch.h"
#include "TrackerExtensionsViewModels.h"

using namespace Enter;
using namespace Enter::View;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Navigation;

TrackerExtensionsViewModels::TrackerExtensionsViewModels(Page^ page) 
	: ViewModelsBase(page)
{
}

void TrackerExtensionsViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	Helpers::LogPage("MainPageView/TrackerExtensionsView");

	auto tracker = dynamic_cast<TrackerOrderModels^>(args->Parameter);
	if (tracker != nullptr)
	{
		if (tracker->Product != nullptr)
		{
			OrderTracker = tracker;
			NumberTracker = "Заказ № " + tracker->Number;
			auto arrayProduct = ref new Vector<int>();
			for (unsigned int i = 0; i < tracker->Product->Size; i++)
			{
				auto element = tracker->Product->GetAt(i);
				arrayProduct->Append(element->Id);
			}

			auto productCommand = ref new ProductCommands(arrayProduct, tracker->RegionId);
			auto operatorCommand = productCommand->ProductsAsync();

			concurrency::create_task(operatorCommand).then([this](IVector<ProductCardModels^>^ productCard)
			{
				ProductVector = productCard;
			}).then([this](void)
			{
				VectorTracker = ref new Vector<TrackerNewDataModel^>();
				unsigned int size = OrderTracker->Product->Size;
				for (unsigned int i = 0; i < size; i++)
				{
					auto element_product = OrderTracker->Product->GetAt(i);
					auto new_element = FindNewTracker(element_product);
					if (new_element != nullptr)
					{
						VectorTracker->Append(new_element);
					}
				}

			}).then(TaskException<void>());
		}
	}
}

void TrackerExtensionsViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
}

TrackerNewDataModel^ TrackerExtensionsViewModels::FindNewTracker(TrackerProductOrderModels^ new_value)
{
	if (ProductVector == nullptr) return nullptr;

	unsigned int size = ProductVector->Size;
	for (unsigned int i = 0; i < size; i++)
	{
		ProductCardModels^ element = ProductVector->GetAt(i);
		if (element->Id == new_value->Id)
		{
			return ref new TrackerNewDataModel(new_value, element);
		}
	}

	return nullptr;
}

void TrackerExtensionsViewModels::OnProductItemClick(Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e)
{
	auto element = dynamic_cast<TrackerNewDataModel^>(e->ClickedItem);
	if (element != nullptr)
	{
		int productId = element->TrackerOrder->Id;
		ViewFrame->Navigate(ProductExtensionsView::typeid, productId);
	}
}

String^ TrackerExtensionsViewModels::NumberTracker::get()
{
	return m_numberTracker;
}

void TrackerExtensionsViewModels::NumberTracker::set(String^ value)
{
	m_numberTracker = value;
	OnPropertyChanged("NumberTracker");
}

IVector<ProductCardModels^>^ TrackerExtensionsViewModels::ProductVector::get()
{
	return m_productVector;
}

void TrackerExtensionsViewModels::ProductVector::set(IVector<ProductCardModels^>^ value)
{
	m_productVector = value;
	OnPropertyChanged("ProductVector");
}

TrackerOrderModels^ TrackerExtensionsViewModels::OrderTracker::get()
{
	return m_orderTracker;
}

void TrackerExtensionsViewModels::OrderTracker::set(TrackerOrderModels^ value)
{
	m_orderTracker = value;
	OnPropertyChanged("OrderTracker");
}

IVector<TrackerNewDataModel^>^ TrackerExtensionsViewModels::VectorTracker::get()
{
	return m_VectorTracker;
}

void TrackerExtensionsViewModels::VectorTracker::set(IVector<TrackerNewDataModel^>^ value)
{
	m_VectorTracker = value;
	OnPropertyChanged("VectorTracker");
}