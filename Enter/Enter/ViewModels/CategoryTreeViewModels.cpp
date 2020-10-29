#include "pch.h"
#include "CategoryTreeViewModels.h"

using namespace Enter;
using namespace Enter::ViewModels;
using namespace Enter::DataModel;
using namespace Enter::DataModel::Storage;
using namespace Enter::View;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;

CategoryTreeViewModels::CategoryTreeViewModels(Page^ page)
	: ViewModelsBase(page)
{
}

void CategoryTreeViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	Helpers::LogPage("MainPageView/CategoryTreeView");

	if (state->PageState != nullptr)
	{
		HorizontalOffset = safe_cast<double>(state->PageState->Lookup("categoryTreeHorizontalOffset"));
	}

	m_treeParameter = args->Parameter;
	LoadedTask(args->Parameter, false);
}

void CategoryTreeViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
	state->PageState->Insert("categoryTreeHorizontalOffset", HorizontalOffset);
}

void CategoryTreeViewModels::LoadedTask(Object^ parameter, bool isCached)
{
	OnActiveState(true);
	auto category = dynamic_cast<CategoryTreeModels^>(parameter);
	if (category != nullptr)
	{
		HeaderTree = category->Name;

		int geo_id = CityTokenStorage::Current->Id != 0 ? CityTokenStorage::Current->Id : 14974;
		auto treeCommand = ref new CategoryTreeCommands(category->Id, 3, geo_id, false);
		auto treeOperator = treeCommand->CategoryTreeCommandAsync(isCached);
		concurrency::create_task(treeOperator).then([&](IVector<CategoryTreeModels^>^ content)
		{
			if (content != nullptr && content->Size > 0)
			{
				auto groupModel = ref new GroupCategorySource(content->GetAt(0)->Children);
				CategoryTreeCollection = groupModel->GroupCollection();
				OnActiveState(false);
			}
		}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
		return;
	}

	auto treeModel = dynamic_cast<GridRowAndColumnTree^>(parameter);
	if (treeModel != nullptr)
	{
		this->GridParseContent(treeModel->Content);
		OnActiveState(false);
		return;
	}

	auto moreModel = dynamic_cast<GridRowAndColumnMore^>(parameter);
	if (moreModel != nullptr)
	{
		this->GridParseContent(moreModel->Content);
		OnActiveState(false);
		return;
	}
}

void CategoryTreeViewModels::VariableCategoryItemClick(Object^ parameter)
{
	auto modelMore = dynamic_cast<GridRowAndColumnMore^>(parameter);
	if (modelMore != nullptr)
	{
		auto contentMore = dynamic_cast<CategoryTreeModels^>(modelMore->Content);
		if (modelMore->Name == "Все товары категории")
		{
			ViewFrame->Navigate(ProductView::typeid, modelMore->Content);
			return;
		}
		else if (modelMore->Name == "Подкатегории")
		{
			if (contentMore != nullptr && contentMore->Children != nullptr && contentMore->HasChildren == true)
			{
				ViewFrame->Navigate(CategoryTreeView::typeid, modelMore);
				return;
			}
			else
			{
				ViewFrame->Navigate(ProductView::typeid, modelMore->Content);
				return;
			}
		}
	}

	auto modelTree = dynamic_cast<GridRowAndColumnTree^>(parameter);
	if (modelTree != nullptr)
	{
		auto contentTree = dynamic_cast<CategoryTreeModels^>(modelTree->Content);
		if (contentTree != nullptr && contentTree->Children != nullptr && contentTree->HasChildren == true)
		{
			ViewFrame->Navigate(CategoryTreeView::typeid, modelTree);
			return;
		}
		else
		{
			ViewFrame->Navigate(ProductView::typeid, modelTree->Content);
			return;
		}
	}
}

void CategoryTreeViewModels::GridParseContent(Object^ parameter)
{
	auto source = dynamic_cast<CategoryTreeModels^>(parameter);
	if (source != nullptr)
	{
		auto groupModel = ref new GroupCategorySource(source->Children);
		CategoryTreeCollection = groupModel->GroupCollection();
		HeaderTree = source->Name;
	}
}

String^ CategoryTreeViewModels::HeaderTree::get()
{
	return category_header;
}

void CategoryTreeViewModels::HeaderTree::set(String^ val)
{
	category_header = val;
	OnPropertyChanged("HeaderTree");
}

IObservableVector<GroupCategoryModel^>^ CategoryTreeViewModels::CategoryTreeCollection::get()
{
	return category_TreeCollection;
}

void CategoryTreeViewModels::CategoryTreeCollection::set(IObservableVector<GroupCategoryModel^>^ val)
{
	category_TreeCollection = val;
	OnPropertyChanged("CategoryTreeCollection");
}

double CategoryTreeViewModels::HorizontalOffset::get()
{
	return m_horizontalOffset;
}

void CategoryTreeViewModels::HorizontalOffset::set(double value)
{
	m_horizontalOffset = value;
	OnPropertyChanged("HorizontalOffset");
}

RelayCommand^ CategoryTreeViewModels::ShopCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		ViewFrame->Navigate(AboutShopView::typeid);
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ CategoryTreeViewModels::RefreshCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		LoadedTask(m_treeParameter, true);
	}, [this](Object^)
	{
		return true;
	});
}