#include "pch.h"
#include "BasketViewModels.h"

using namespace Enter;
using namespace Enter::ViewModels;
using namespace Enter::DataModel;
using namespace Enter::DataModel::Storage;
using namespace Enter::View;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

std::vector<BasketProductDataModel^> vect;

BasketViewModels::BasketViewModels(Page^ page)
	: ViewModelsBase(page)
{
}

void BasketViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	Helpers::LogPage("MainPageView/BasketView");
	this->OnLoadedView();
}

void BasketViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
}

void BasketViewModels::OnLoadedView()
{
	VisibilityEdit = Visibility::Collapsed;
	VisibilitySelectedButton = Visibility::Collapsed;
	SelectionIndex = -1;

	auto basketContent = std::shared_ptr<BasketProductSerialize>();
	auto basketOperation = (*basketContent).Open();
	concurrency::create_task(basketOperation).then([&](IVector<BasketProductDataModel^>^ productBasket)
	{
		auto vect = ref new Vector<BasketProductDataModel^>(begin(productBasket), end(productBasket));
		VectorProduct = vect;
		this->OnAmountSum();
	});
}

void BasketViewModels::OnAmountSum()
{
	this->Amount = 0.0;
	for (const auto &itemValue : VectorProduct)
	{
		this->Amount += itemValue->Price * itemValue->Count;
	}
}

void BasketViewModels::OnSaveSerialize()
{
	auto content = ref new Vector<BasketProductDataModel^>(begin(VectorProduct), end(VectorProduct));
	auto basket = std::shared_ptr<BasketProductSerialize>();
	(*basket).Save(content);
}

void BasketViewModels::OnSelectionProduct(Object^ sender, SelectionChangedEventArgs^ parameter)
{
	auto addedCollection = dynamic_cast<IVector<BasketProductDataModel^>^>(parameter->AddedItems);
	if (parameter->AddedItems != nullptr && parameter->AddedItems->Size > 0)
	{
		IsOpenBottom = true;
		IsStiskyBottom = true;
		VisibilitySelectedButton = Visibility::Visible;

		auto element = parameter->AddedItems->GetAt(0);
		vect.push_back(safe_cast<BasketProductDataModel^>(element));
		return;
	}

	if (parameter->RemovedItems != nullptr && parameter->RemovedItems->Size > 0)
	{
		auto removeItem = safe_cast<BasketProductDataModel^>(parameter->RemovedItems->GetAt(0));

		for (unsigned int iter = 0; iter < vect.size(); iter++)
		{
			if (removeItem->Id == vect[iter]->Id)
			{
				vect.erase(vect.begin() + iter);
			}
		}
		
		if (vect.size() == 0)
		{
			VisibilitySelectedButton = Visibility::Collapsed;
			IsOpenBottom = false;
			IsStiskyBottom = false;
			vect.clear();
		}
	}
}

void BasketViewModels::OnItemClickView(Object^ parameter)
{
	if (vect.size() <= 1)
	{
		ViewFrame->Navigate(ProductExtensionsView::typeid, parameter);
	}
}

IObservableVector<BasketProductDataModel^>^ BasketViewModels::VectorProduct::get()
{
	return source_VectorProduct;
}

void BasketViewModels::VectorProduct::set(IObservableVector<BasketProductDataModel^>^ val)
{
	source_VectorProduct = val;
	OnPropertyChanged("VectorProduct");
}

double BasketViewModels::Amount::get()
{
	return source_Amount;
}

void BasketViewModels::Amount::set(double val)
{
	source_Amount = val;
	OnPropertyChanged("Amount");
}

Visibility BasketViewModels::VisibilityEdit::get()
{
	return source_editVisibility;
}

void BasketViewModels::VisibilityEdit::set(Visibility val)
{
	source_editVisibility = val;
	OnPropertyChanged("VisibilityEdit");
}

Visibility BasketViewModels::VisibilitySelectedButton::get()
{
	return source_SelectedAppBarBottom;
}

void BasketViewModels::VisibilitySelectedButton::set(Visibility val)
{
	source_SelectedAppBarBottom = val;
	OnPropertyChanged("VisibilitySelectedButton");
}

int BasketViewModels::SelectionIndex::get()
{
	return source_selectionIndex;
}

void BasketViewModels::SelectionIndex::set(int index)
{
	source_selectionIndex = index;
	OnPropertyChanged("SelectionIndex");
}

bool BasketViewModels::IsStiskyBottom::get()
{
	return source_isBottomStisky;
}

void BasketViewModels::IsStiskyBottom::set(bool val)
{
	source_isBottomStisky = val;
	OnPropertyChanged("IsStiskyBottom");
}

bool BasketViewModels::IsOpenBottom::get()
{
	return source_isBottomOpen;
}

void BasketViewModels::IsOpenBottom::set(bool val)
{
	source_isBottomOpen = val;
	OnPropertyChanged("IsOpenBottom");
}

bool BasketViewModels::IsStiskyTop::get()
{
	return source_isTopStisky;
}

void BasketViewModels::IsStiskyTop::set(bool val)
{
	source_isTopStisky = val;
	OnPropertyChanged("IsStiskyTop");
}

bool BasketViewModels::IsOpenTop::get()
{
	return source_isTopOpen;
}

void BasketViewModels::IsOpenTop::set(bool val)
{
	source_isTopOpen = val;
	OnPropertyChanged("IsOpenTop");
}

RelayCommand^ BasketViewModels::RemoveCommand::get()
{
	return ref new RelayCommand([this](Object^ executeObject)
	{
		BasketProductDataModel^ elemenetCurrent = dynamic_cast<BasketProductDataModel^>(executeObject);
		if (elemenetCurrent != nullptr)
		{
			auto size = VectorProduct->Size;
			for (unsigned int i = 0; i < size; i++)
			{
				auto element = VectorProduct->GetAt(i);
				if (element->Id == elemenetCurrent->Id)
				{
					auto basketModel = ref new BasketProductDataModel(element->Id,
						element->Article,
						element->Token,
						element->Name,
						element->Image,
						element->Count > 1 ? element->Count - 1 : 1,
						element->Quantity,
						element->Price);
					VectorProduct->SetAt(i, basketModel);
				}
			}
			this->OnAmountSum();
			this->OnSaveSerialize();
		}
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ BasketViewModels::AddCommand::get()
{
	return ref new RelayCommand([this](Object^ executeObject)
	{
		BasketProductDataModel^ elemenetCurrent = dynamic_cast<BasketProductDataModel^>(executeObject);
		if (elemenetCurrent != nullptr)
		{
			auto size = VectorProduct->Size;
			for (unsigned int i = 0; i < size; i++)
			{
				auto element = VectorProduct->GetAt(i);
				if (element->Id == elemenetCurrent->Id)
				{
					auto basketModel = ref new BasketProductDataModel(element->Id,
						element->Article,
						element->Token,
						element->Name,
						element->Image,
						element->Count < element->Quantity ? element->Count + 1 : element->Count,
						element->Quantity,
						element->Price);
					VectorProduct->SetAt(i, basketModel);
				}
			}
			this->OnAmountSum();
			this->OnSaveSerialize();
		}
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ BasketViewModels::EditCommand::get()
{
	return ref new RelayCommand([this](Object^ obj)
	{
		if (VisibilityEdit == Visibility::Collapsed)
		{
			VisibilityEdit = Visibility::Visible;
		}
		else if (VisibilityEdit == Visibility::Visible)
		{
			VisibilityEdit = Visibility::Collapsed;
		}
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ BasketViewModels::OrderCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		if (VectorProduct->Size > 0)
		{
			auto token = AutorizationStorage::Current->Token;
			if (token == nullptr)
			{
				auto auth = ref new Enter::View::Settings::AutorizationFlyout();
				auth->Width = 500;
				auth->ShowIndependent();
			}
			else
			{
				ViewFrame->Navigate(OrderView::typeid, VectorProduct);
				VectorProduct->Clear();
			}
		}
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ BasketViewModels::RefreshCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		if (VectorProduct->Size > 0)
		{
			VectorProduct->Clear();
		}
		this->OnLoadedView();

	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ BasketViewModels::ClearCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		VectorProduct->Clear();
		this->OnAmountSum();
		this->OnSaveSerialize();

	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ BasketViewModels::DeleteCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		std::vector<BasketProductDataModel^> v(std::begin(vect), std::end(vect));
		for (const auto &item : v)
		{
			for (unsigned int iter = 0; iter < VectorProduct->Size; iter++)
			{
				BasketProductDataModel^ element = VectorProduct->GetAt(iter);
				if (element->Id == item->Id)
				{
					VectorProduct->RemoveAt(iter);
				}
			}
		}

		vect.clear();
		this->OnAmountSum();
		this->OnSaveSerialize();

	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ BasketViewModels::ShopCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		ViewFrame->Navigate(AboutShopView::typeid);
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ BasketViewModels::ClearSelectionCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		SelectionIndex = -1;
		VisibilitySelectedButton = Visibility::Collapsed;

		IsOpenBottom = false;
		IsStiskyBottom = false;

		IsStiskyTop = false;
		IsOpenTop = false;

		vect.clear();

	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ BasketViewModels::WithOrderCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		if (vect.size() > 0)
		{
			auto token = AutorizationStorage::Current->Token;
			if (token == nullptr)
			{
				auto auth = ref new Enter::View::Settings::AutorizationFlyout();
				auth->Width = 500;
				auth->ShowIndependent();
			}
			else
			{
				auto vectOrder = ref new Vector<BasketProductDataModel^>(begin(vect), end(vect));
				ViewFrame->Navigate(OrderView::typeid, vectOrder);

				vect.clear();
			}
		}
	}, [this](Object^)
	{
		return true;
	});
}