//
// SplashFilterView.xaml.cpp
// Реализация класса SplashFilterView
//

#include "pch.h"
#include "SplashFilterView.xaml.h"

using namespace Enter;
using namespace Enter::View;
using namespace Enter::ViewModels;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

SplashFilterChangedEventArgs::SplashFilterChangedEventArgs(IVector<Object^>^ newValue, EnterStore::Commands::SortProduct^ newSort)
: source_newValue(newValue), source_newSort(newSort)
{
}

IVector<Object^>^ SplashFilterChangedEventArgs::NewValue::get()
{
	return source_newValue;
}

EnterStore::Commands::SortProduct^ SplashFilterChangedEventArgs::NewSort::get()
{
	return source_newSort;
}

SplashFilterView::SplashFilterView()
{
	InitializeComponent();

	loadedToken = this->Loaded += ref new RoutedEventHandler(this, &SplashFilterView::OnLoaded);
	unloadedToken = this->Unloaded += ref new RoutedEventHandler(this, &SplashFilterView::OnUnloaded);

	splashFilterView = ref new SplashFilterViewModels(this);
	this->DataContext = splashFilterView;
}

void SplashFilterView::OnNavigatedTo(NavigationEventArgs^ e)
{
	splashFilterView->OnNavigatedTo(e);
}

void SplashFilterView::OnNavigatedFrom(NavigationEventArgs^ e)
{
	splashFilterView->OnNavigatedFrom(e);
	splashFilterView = nullptr;
}

DependencyProperty^ SplashFilterView::_RegionIdProperty = DependencyProperty::Register("RegionId",
	TypeName(int::typeid), SplashFilterView::typeid, 
	ref new PropertyMetadata(0, ref new PropertyChangedCallback(&SplashFilterView::OnRegionPropertyChanged)));

void SplashFilterView::OnRegionPropertyChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args)
{
	auto control = dynamic_cast<SplashFilterView^>(sender);
	if (control != nullptr)
	{
		control->splashFilterView->RegionId = control->RegionId;
	}
}

DependencyProperty^ SplashFilterView::RegionIdProperty::get()
{
	return _RegionIdProperty;
}

int SplashFilterView::RegionId::get()
{
	return safe_cast<int>(GetValue(RegionIdProperty));
}

void SplashFilterView::RegionId::set(int value)
{
	SetValue(RegionIdProperty, value);
}

DependencyProperty^ SplashFilterView::_CategoryIdProperty = DependencyProperty::Register("CategoryId",
	TypeName(int::typeid), SplashFilterView::typeid, 
	ref new PropertyMetadata(0, ref new PropertyChangedCallback(&SplashFilterView::OnCategoryPropertyChanged)));

void SplashFilterView::OnCategoryPropertyChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args)
{
	auto control = dynamic_cast<SplashFilterView^>(sender);
	if (control != nullptr)
	{
		control->splashFilterView->CategoryId = control->CategoryId;
	}
}

DependencyProperty^ SplashFilterView::CategoryIdProperty::get()
{
	return _CategoryIdProperty;
}

int SplashFilterView::CategoryId::get()
{
	return safe_cast<int>(GetValue(CategoryIdProperty));
}

void SplashFilterView::CategoryId::set(int value)
{
	SetValue(CategoryIdProperty, value);
}

void SplashFilterView::OnLoaded(Object ^sender, RoutedEventArgs ^e)
{
	splashFilterView->OnLoadedFilterView(sender, e);
}

void SplashFilterView::OnUnloaded(Object ^sender, RoutedEventArgs ^e)
{
	this->Loaded -= loadedToken;
	this->Unloaded -= unloadedToken;
	
	if (splashFilterView != nullptr)
	{
		delete splashFilterView;
	}
}

void SplashFilterView::MultipleDataContextChanged(FrameworkElement^ sender, DataContextChangedEventArgs^ args)
{
	splashFilterView->OnMultipleDataContextChanged(sender, args);
}

void SplashFilterView::OnPickClick(Object^ sender, RoutedEventArgs^ e)
{
	auto popup = dynamic_cast<Popup^>(this->Parent);
	if (popup != nullptr)
	{
		SortCommon commonValue = SortCommon::asc;
		String^ typeId = "default";

		if (splashFilterView->SelectedSortingItem == "По умолчанию")
		{
			typeId = "default";
		}
		else if (splashFilterView->SelectedSortingItem == "Хит продаж")
		{
			typeId = "rating";
		}
		else if (splashFilterView->SelectedSortingItem == "По возрастанию цены")
		{
			typeId = "price";
			commonValue = SortCommon::asc;
		}
		else if (splashFilterView->SelectedSortingItem == "По убыванию цены")
		{
			typeId = "price";
			commonValue = SortCommon::desc;
		}

		SplashFilterChanged(this, ref new SplashFilterChangedEventArgs(splashFilterView->SelectedFilters, ref new SortProduct(typeId, commonValue)));
		popup->IsOpen = false;
	}
}

void SplashFilterView::OnResetFilter(Object^ sender, RoutedEventArgs^ e)
{
	auto popup = dynamic_cast<Popup^>(this->Parent);
	if (popup != nullptr)
	{
		SplashFilterChanged(this, ref new SplashFilterChangedEventArgs(splashFilterView->SelectedFilters, nullptr));
		popup->IsOpen = false;
	}
}