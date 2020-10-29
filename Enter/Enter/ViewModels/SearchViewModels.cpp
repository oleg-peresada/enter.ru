#include "pch.h"
#include "SearchViewModels.h"

using namespace Enter;
using namespace Enter::DataModel;
using namespace Enter::DataModel::Storage;
using namespace Enter::ViewModels;
using namespace Enter::View;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Media::Animation;

SearchViewModels::SearchViewModels(Page^ page) : ViewModelsBase(page)
{
}

void SearchViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	Helpers::LogPage("MainPageView/SearchView");

	auto queryText = dynamic_cast<String^>(args->Parameter);
	if (queryText != nullptr)
	{
		this->SearchBegin(queryText);
	}
}

void SearchViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
}

void SearchViewModels::SearchBegin(String^ queryText)
{
	QueryHeader = queryText;
	isCategory = false;
	isSort = false;

	int geo_id = CityTokenStorage::Current->Id != 0 ? CityTokenStorage::Current->Id : 14974;
	auto searchCommand = ref new SearchCommands(queryText, geo_id, 0, SearchType::Product);
	auto searchOperation = searchCommand->SearchAsync();

	concurrency::create_task(searchOperation).then([this, searchCommand](IVector<ProductCardModels^>^ vectorProduct)
	{
		QueryProduct = vectorProduct;
		CategoryView = searchCommand->CategoryVector;
		CategoryItem = CategoryView->GetAt(0);
		SearchSortItem = SearchSortView->GetAt(0);

	}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
}

void SearchViewModels::OnItemProductClick(Object^ parameter)
{
	this->ViewFrame->Navigate(ProductExtensionsView::typeid, parameter);
}

void SearchViewModels::OnSearchCategoryProduct(int idCategory, String^ queryName, String^ sortValue)
{
	SearchSortType sortType = SearchSortType::category_name;
	SortCommon sort = SortCommon::asc;

	if (sortValue == "По умолчанию")
	{
		sortType = SearchSortType::category_name;
	}
	else if (sortValue == "Хит продаж")
	{
		sortType = SearchSortType::rating;
	}
	else if (sortValue == "По возрастанию цены")
	{
		sortType = SearchSortType::price;
		sort = SortCommon::asc;
	}
	else if (sortValue == "По убыванию цены")
	{
		sortType = SearchSortType::price;
		sort = SortCommon::desc;
	}

	String^ query = idCategory != 0 ? QueryHeader + " " + queryName : QueryHeader;
	auto searchCommand = ref new SearchCommands(query, 0, 0, SearchType::Product);
	searchCommand->ProductQuery = ref new SearchProductQuery(idCategory, sortType, sort);

	auto searchOperation = searchCommand->SearchAsync();
	concurrency::create_task(searchOperation).then([this, searchCommand](IVector<ProductCardModels^>^ vectorProduct)
	{
		QueryProduct = vectorProduct;
	});
}

void SearchViewModels::OnSearchQuerySubmittedView(SearchBox^ sender, SearchBoxQuerySubmittedEventArgs^ args)
{
	auto queryText = args->QueryText;
	if (queryText == nullptr) return;

	this->SearchBegin(queryText);
}

String^ SearchViewModels::QueryHeader::get()
{
	return source_QueryHeader;
}

void SearchViewModels::QueryHeader::set(String^ val)
{
	source_QueryHeader = val;
	OnPropertyChanged("QueryHeader");
}

IVector<ProductCardModels^>^ SearchViewModels::QueryProduct::get()
{
	return source_QueryProduct;
}

void SearchViewModels::QueryProduct::set(IVector<ProductCardModels^>^ val)
{
	source_QueryProduct = val;
	OnPropertyChanged("QueryProduct");
}

IVector<SearchIsCategory^>^ SearchViewModels::CategoryView::get()
{
	return source_categoryView;
}

void SearchViewModels::CategoryView::set(IVector<SearchIsCategory^>^ val)
{
	val->InsertAt(0, ref new SearchIsCategory(0, 0, "Все категории"));
	source_categoryView = val;
	OnPropertyChanged("CategoryView");
}

SearchIsCategory^ SearchViewModels::CategoryItem::get()
{
	return source_categoryItem;
}

void SearchViewModels::CategoryItem::set(SearchIsCategory^ val)
{
	if (val != nullptr)
	{
		if (val->Name == "Все категории")
		{
			if (isCategory)
			{
				this->OnSearchCategoryProduct(0, QueryHeader, SearchSortItem);
			}
			else
			{
				isCategory = true;
			}
		}
		else
		{
			this->OnSearchCategoryProduct(val->Id, val->Name, SearchSortItem);
		}
	}

	source_categoryItem = val;
	OnPropertyChanged("CategoryItem");
}

IVector<String^>^ SearchViewModels::SearchSortView::get()
{
	auto vect = ref new Vector<String^>();
	vect->Append("По умолчанию");
	vect->Append("Хит продаж");
	vect->Append("По возрастанию цены");
	vect->Append("По убыванию цены");

	return vect;
}

String^ SearchViewModels::SearchSortItem::get()
{
	return source_searchSortItem;
}

void SearchViewModels::SearchSortItem::set(String^ value)
{
	if (value != nullptr)
	{
		if (value == "По умолчанию" && CategoryItem->Name == "Все категории")
		{
			if (isSort)
			{
				this->OnSearchCategoryProduct(0, QueryHeader, value);
			}
			else
			{
				isSort = true;
			}
		}
		else
		{
			this->OnSearchCategoryProduct(CategoryItem->Id, CategoryItem->Name, value);
		}
	}

	source_searchSortItem = value;
	OnPropertyChanged("SearchSortItem");
}