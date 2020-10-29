#include "pch.h"
#include "SplashFilterViewModels.h"

using namespace Enter;
using namespace Enter::ViewModels;
using namespace Enter::DataModel;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Controls::Primitives;

auto selectedVect = ref new Vector<Object^>();
IObservableVector<FilterProductDataModel^>^ source_filters = ref new Vector<FilterProductDataModel^>();
String^ bufferSorting;
int categoryId = 0;

SplashFilterViewModels::SplashFilterViewModels(Page^ page) : ViewModelsBase(page)
{
}

void SplashFilterViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
}

void SplashFilterViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
}

void SplashFilterViewModels::OnLoadedFilterView(Object ^sender, RoutedEventArgs ^e)
{
	Helpers::LogPage("MainPageView/SplashFilterView");

	this->OnActiveState(true);

	if (categoryId != CategoryId)
	{
		source_filters->Clear();
		selectedVect->Clear();
		categoryId = CategoryId;
	}

	auto filterCommand = ref new FilterProductCommands(RegionId, CategoryId);
	auto filterOperation = filterCommand->FilterAsync();

	concurrency::create_task(filterOperation).then([this](IVector<FilterProductModels^>^ productFilters)
	{
		auto content = FilterConversation::ToConvert(productFilters);
		if (source_filters->Size == 0)
		{
			unsigned int size = content->Size;
			for (unsigned int i = 0; i < size; i++)
			{
				source_filters->Append(content->GetAt(i));
				SelectedSortingItem = "По умолчанию";
			}
		}
		else
		{
			SelectedSortingItem = bufferSorting;
		}

		SelectedItem = source_filters->GetAt(0);
	}).then([this](void)
	{
		this->OnActiveState(false);
	});
}

void SplashFilterViewModels::OnMultipleDataContextChanged(FrameworkElement^ sender, DataContextChangedEventArgs^ args)
{
	source_multiple = dynamic_cast<FilterProductDataModel^>(args->NewValue);
}

int SplashFilterViewModels::HasFilter(String^ filterId)
{
	unsigned int size = selectedVect->Size;
	for (unsigned int i = 0; i < size; i++)
	{
		Object^ element = selectedVect->GetAt(i);

		auto rangeElement = dynamic_cast<RangeSelectedFilter^>(element);
		if (rangeElement != nullptr)
		{
			if (rangeElement->FilterId == filterId)
			{
				return i;
			}
		}

		auto multipleElement = dynamic_cast<MultipleSelectedFilter^>(element);
		if (multipleElement != nullptr)
		{
			if (multipleElement->FilterId == filterId)
			{
				return i;
			}
		}

		auto booleanElement = dynamic_cast<BooleanSelectedFilter^>(element);
		if (booleanElement != nullptr)
		{
			if (booleanElement->FilterId == filterId)
			{
				return i;
			}
		}
	}

	return -1;
}

void SplashFilterViewModels::OnCheckedTemplateCommand(Object^ element, bool isChecked)
{
	auto filter = dynamic_cast<FilterProductDataModel^>(element);
	if (filter != nullptr)
	{
		int elementIndex = HasFilter(filter->Product->FilterId);
		unsigned int size = source_filters->Size;

		for (unsigned int i = 0; i < size; i++)
		{
			auto item = source_filters->GetAt(i);
			if (item->Product->FilterId == filter->Product->FilterId)
			{
				if (item->Yes || item->No)
				{
					auto newBoolean = ref new BooleanSelectedFilter(filter->Product->FilterId, isChecked);
					if (elementIndex == -1)
					{
						selectedVect->Append(newBoolean);
					}
					else
					{
						selectedVect->SetAt(elementIndex, newBoolean);
					}

					auto newValue = ref new FilterProductDataModel(item->Product, item->Options, 
						item->Min, item->Max, item->PositionLeft, item->PositionRight);
					newValue->Yes = isChecked == true ? true : false;
					newValue->No = isChecked == false ? true : false;

					Filters->SetAt(i, newValue);
					SelectedItem = Filters->GetAt(i);
					return;
				}
				else
				{
					if (elementIndex != -1)
					{
						selectedVect->RemoveAt(elementIndex);
					}
				}
			}
		}
	}
}

void SplashFilterViewModels::OnMultipleCommand(Object^ parameter)
{
	if (this->MultipleDataContext == nullptr) return;

	auto filter = dynamic_cast<FilterOptionsDataModel^>(parameter);
	if (filter != nullptr)
	{
		int elementIndex = HasFilter(MultipleDataContext->Product->FilterId);
		if (filter->IsChecked == true) //addition
		{
			if (elementIndex == -1)
			{
				auto vectMultiple = ref new Vector<int>();
				vectMultiple->Append(filter->Option->Id);

				auto multipleModel = ref new MultipleSelectedFilter(MultipleDataContext->Product->FilterId);
				multipleModel->SelectedType = vectMultiple;
				selectedVect->Append(multipleModel);
			}
			else
			{
				auto element = dynamic_cast<MultipleSelectedFilter^>(selectedVect->GetAt(elementIndex));
				if (element != nullptr)
				{
					auto vectMultiple = ref new Vector<int>(begin(element->SelectedType), end(element->SelectedType));
					vectMultiple->Append(filter->Option->Id);

					auto multipleModel = ref new MultipleSelectedFilter(MultipleDataContext->Product->FilterId);
					multipleModel->SelectedType = vectMultiple;
					selectedVect->SetAt(elementIndex, multipleModel);
				}
			}
		}
		else //remove
		{
			if (elementIndex != -1)
			{
				auto element = dynamic_cast<MultipleSelectedFilter^>(selectedVect->GetAt(elementIndex));
				if (element != nullptr)
				{
					auto vectMultiple = ref new Vector<int>(begin(element->SelectedType), end(element->SelectedType));
					unsigned int size = vectMultiple->Size;

					if (vectMultiple->Size > 1)
					{
						for (unsigned int i = 0; i < size; i++)
						{
							auto id = vectMultiple->GetAt(i);
							if (id == filter->Option->Id)
							{
								vectMultiple->RemoveAt(i);

								auto multipleModel = ref new MultipleSelectedFilter(MultipleDataContext->Product->FilterId);
								multipleModel->SelectedType = vectMultiple;
								selectedVect->SetAt(elementIndex, multipleModel);
								return;
							}
						}
					}
					else
					{
						selectedVect->RemoveAt(elementIndex);
					}
				}
			}
		}
	}
}

void SplashFilterViewModels::OnRangeCommand(Object^ parameter)
{
	auto sliderElement = dynamic_cast<Enter::Controls::UI::SliderRange^>(parameter);
	if (sliderElement != nullptr)
	{
		auto filter = dynamic_cast<FilterProductDataModel^>(sliderElement->Tag);
		if (filter != nullptr)
		{
			auto elementIndex = HasFilter(filter->Product->FilterId);
			auto rangeModel = ref new RangeSelectedFilter(filter->Product->FilterId, filter->Min, filter->Max);
			if (elementIndex == -1)
			{
				selectedVect->Append(rangeModel);
			}
			else
			{
				selectedVect->SetAt(elementIndex, rangeModel);
			}
		}
	}
}

int SplashFilterViewModels::RegionId::get()
{
	return source_regionId;
}

void SplashFilterViewModels::RegionId::set(int value)
{
	source_regionId = value;
}

int SplashFilterViewModels::CategoryId::get()
{
	return source_categoryId;
}

void SplashFilterViewModels::CategoryId::set(int value)
{
	source_categoryId = value;
}

IObservableVector<FilterProductDataModel^>^ SplashFilterViewModels::Filters::get()
{
	return source_filters;
}

void SplashFilterViewModels::Filters::set(IObservableVector<FilterProductDataModel^>^ value)
{
	source_filters = value;
	OnPropertyChanged("Filters");
}

FilterProductDataModel^ SplashFilterViewModels::MultipleDataContext::get()
{
	return source_multiple;
}

IVector<Object^>^ SplashFilterViewModels::SelectedFilters::get()
{
	return selectedVect;
}

Object^ SplashFilterViewModels::SelectedItem::get()
{
	return source_selectedItem;
}

void SplashFilterViewModels::SelectedItem::set(Object^ value)
{
	source_selectedItem = value;
	OnPropertyChanged("SelectedItem");
}

IVector<String^>^ SplashFilterViewModels::AllSorting::get()
{
	auto vect = ref new Vector<String^>();
	vect->Append("По умолчанию");
	vect->Append("Хит продаж");
	vect->Append("По возрастанию цены");
	vect->Append("По убыванию цены");

	return vect;
}

String^ SplashFilterViewModels::SelectedSortingItem::get()
{
	return source_selectedSorting;
}

void SplashFilterViewModels::SelectedSortingItem::set(String^ value)
{
	source_selectedSorting = value;
	bufferSorting = value;
	OnPropertyChanged("SelectedSortingItem");
}

RelayCommand^ SplashFilterViewModels::YesTemplateCommand::get()
{
	return ref new RelayCommand([this](Object^ parameter)
	{
		this->OnCheckedTemplateCommand(parameter, true);
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ SplashFilterViewModels::NoTemplateCommand::get()
{
	return ref new RelayCommand([this](Object^ parameter)
	{
		this->OnCheckedTemplateCommand(parameter, false);
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ SplashFilterViewModels::RangeSliderCommand::get()
{
	return ref new RelayCommand([this](Object^ parameter)
	{
		this->OnRangeCommand(parameter);
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ SplashFilterViewModels::MultipleCommand::get()
{
	return ref new RelayCommand([this](Object^ parameter)
	{
		this->OnMultipleCommand(parameter);
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ SplashFilterViewModels::ResetFilterCommand::get()
{
	return ref new RelayCommand([this](Object^ parameter)
	{
		selectedVect->Clear();
		source_filters->Clear();
		SelectedSortingItem = "По умолчанию";
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ SplashFilterViewModels::CloseWindowCommand::get()
{
	return ref new RelayCommand([this](Object^ parameter)
	{
		if (ViewPage != nullptr)
		{
			auto popup = dynamic_cast<Popup^>(ViewPage->Parent);
			if (popup != nullptr)
			{
				popup->IsOpen = false;
			}
		}
	}, [this](Object^)
	{
		return true;
	});
}