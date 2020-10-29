#include "pch.h"
#include "GroupCategorySource.h"

using namespace Enter;
using namespace Enter::DataModel;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

String^ GroupCategoryModel::Title::get()
{
	return source_Title;
}

void GroupCategoryModel::Title::set(String^ val)
{
	source_Title = val;
}

IObservableVector<Object^>^ GroupCategoryModel::Tree::get()
{
	return source_Tree;
}

void GroupCategoryModel::Tree::set(IObservableVector<Object^>^ val)
{
	source_Tree = val;
}

GridRowAndColumnTree::GridRowAndColumnTree(unsigned int row, unsigned int column, Object^ content)
	: source_Row(row), source_Column(column), source_Content(content)
{
}

unsigned int GridRowAndColumnTree::Row::get()
{
	return source_Row;
}

unsigned int GridRowAndColumnTree::Column::get()
{
	return source_Column;
}

Object^ GridRowAndColumnTree::Content::get()
{
	return source_Content;
}

GridRowAndColumnMore::GridRowAndColumnMore(unsigned int row, unsigned int column, String^ name, Object^ content)
	: source_Row(row), source_Column(column), source_name(name), source_content(content)
{
}

unsigned int GridRowAndColumnMore::Row::get()
{
	return source_Row;
}

unsigned int GridRowAndColumnMore::Column::get()
{
	return source_Column;
}

String^ GridRowAndColumnMore::Name::get()
{
	return source_name;
}

Object^ GridRowAndColumnMore::Content::get()
{
	return source_content;
}

GroupCategorySource::GroupCategorySource(IVector<CategoryTreeModels^>^ viewModel)
	: source_viewModel(viewModel)
{
}

IObservableVector<GroupCategoryModel^>^ GroupCategorySource::GroupCollection()
{
	if (source_viewModel == nullptr) return nullptr;

	auto vectorGroup = ref new Vector<GroupCategoryModel^>();
	for (const auto &item : source_viewModel)
	{
		auto group = ref new GroupCategoryModel();
		group->Title = item->Name;

		auto v_tree = ref new Vector<Object^>();
		v_tree->Append(ref new GridRowAndColumnTree(3, 2, item));
		v_tree->Append(ref new GridRowAndColumnMore(0, 0, "Все товары категории", item));
		
		if (item->Children != nullptr && item->HasChildren == true)
		{
			v_tree->Append(ref new GridRowAndColumnMore(0, 0, "Подкатегории", item));
		}

		group->Tree = v_tree;

		vectorGroup->Append(group);
	}

	return vectorGroup;
}

ShopGroupDataModel::ShopGroupDataModel()
{
}

ShopGroupDataModel::ShopGroupDataModel(String^ title, IVector<ShopListModels^>^ shop)
	: source_Title(title), source_Shop(shop)
{
}

IVector<ShopGroupDataModel^>^ ShopGroupDataModel::ToViewShop(IVector<ShopListModels^>^ content)
{
	if (content == nullptr) return nullptr;

	auto vs = ref new Map<String^, IVector<ShopListModels^>^>();
	auto vect = ref new Vector<ShopGroupDataModel^>();

	for (const auto &item : content)
	{
		if (item->Geo != nullptr)
		{
			String^ name = item->Geo->Name;
			if (name != nullptr && !name->IsEmpty())
			{
				const wchar_t* key = name->Data();
				if (vs->HasKey(key[0].ToString()))
				{
					auto element = vs->Lookup(key[0].ToString());
					auto iValue = ref new Vector<ShopListModels^>(begin(element), end(element));
					iValue->Append(item);
					vs->Insert(key[0].ToString(), iValue);
				}
				else
				{
					auto tValue = ref new Vector<ShopListModels^>();
					tValue->Append(item);
					vs->Insert(key[0].ToString(), tValue);
				}
			}
		}
	}

	for (const auto &elementKey : vs)
	{
		auto bufferVect = ref new Vector<ShopListModels^>();
		for (const auto &elementValue : elementKey->Value)
		{
			bufferVect->Append(elementValue);
		}

		auto shopModel = ref new ShopGroupDataModel(elementKey->Key, bufferVect);
		vect->Append(shopModel);
	}

	return vect;
}

String^ ShopGroupDataModel::Title::get()
{
	return source_Title;
}

IVector<ShopListModels^>^ ShopGroupDataModel::Shop::get()
{
	return source_Shop;
}

FilterOptionsDataModel::FilterOptionsDataModel(EnterStore::Models::FilterOptionsModels^ option) : source_Option(option)
{
}

EnterStore::Models::FilterOptionsModels^ FilterOptionsDataModel::Option::get()
{
	return source_Option;
}

bool FilterOptionsDataModel::IsChecked::get()
{
	return source_IsChecked;
}

void FilterOptionsDataModel::IsChecked::set(bool value)
{
	source_IsChecked = value;
}

FilterProductDataModel::FilterProductDataModel(EnterStore::Models::FilterProductModels^ product, 
	IVector<FilterOptionsDataModel^>^ options, double min, double max, double positionLeft, double positionRight) 
	: source_product(product), source_options(options), source_min(min), 
	source_max(max), source_positionLeft(positionLeft), source_positionRight(positionRight)
{
}

EnterStore::Models::FilterProductModels^ FilterProductDataModel::Product::get()
{
	return source_product;
}

IVector<FilterOptionsDataModel^>^ FilterProductDataModel::Options::get()
{
	return source_options;
}

double FilterProductDataModel::Min::get()
{
	return source_min;
}

void FilterProductDataModel::Min::set(double value)
{
	source_min = value;
}

double FilterProductDataModel::Max::get()
{
	return source_max;
}

void FilterProductDataModel::Max::set(double value)
{
	source_max = value;
}

double FilterProductDataModel::PositionLeft::get()
{
	return source_positionLeft;
}

void FilterProductDataModel::PositionLeft::set(double value)
{
	source_positionLeft = value;
}

double FilterProductDataModel::PositionRight::get()
{
	return source_positionRight;
}

void FilterProductDataModel::PositionRight::set(double value)
{
	source_positionRight = value;
}

bool FilterProductDataModel::Yes::get()
{
	return source_yes;
}

void FilterProductDataModel::Yes::set(bool value)
{
	source_yes = value;
}

bool FilterProductDataModel::No::get()
{
	return source_no;
}

void FilterProductDataModel::No::set(bool value)
{
	source_no = value;
}

IVector<FilterProductDataModel^>^ FilterConversation::ToConvert(IVector<EnterStore::Models::FilterProductModels^>^ valueVector)
{
	auto vect = ref new Vector<FilterProductDataModel^>();

	for (const auto &item : valueVector)
	{
		auto optionsVect = ref new Vector<FilterOptionsDataModel^>();
		if (item->Options != nullptr)
		{
			for (const auto &option : item->Options)
			{
				optionsVect->Append(ref new FilterOptionsDataModel(option));
			}
		}

		vect->Append(ref new FilterProductDataModel(item, optionsVect, item->Min, item->Max, 0.0, 0.0));
	}

	return vect;
}

ProductPropertyDataModel::ProductPropertyDataModel(PropertyGroupExetensionsModels^ propertyGroup, 
	IVector<PropertyExtensionsCardModels^>^ propertyVector) : source_propertyGroup(propertyGroup), source_PropertyVector(propertyVector)
{
}

PropertyGroupExetensionsModels^ ProductPropertyDataModel::PropertyGroup::get()
{
	return source_propertyGroup;
}

IVector<PropertyExtensionsCardModels^>^ ProductPropertyDataModel::PropertyVector::get()
{
	return source_PropertyVector;
}

IVector<ProductPropertyDataModel^>^ ProductPropertyConvert::PropertyGroupCreate(IVector<PropertyGroupExetensionsModels^>^ 
	propertyGroup, IVector<PropertyExtensionsCardModels^>^ propertyValue)
{
	auto vect = ref new Vector<ProductPropertyDataModel^>();

	unsigned int groupSize = propertyGroup->Size;
	for (unsigned int i = 0; i < groupSize; i++)
	{
		auto element = propertyGroup->GetAt(i);
		unsigned int size = propertyValue->Size;

		auto vectProp = ref new Vector<PropertyExtensionsCardModels^>();
		for (unsigned int count = 0; count < size; count++)
		{
			auto item = propertyValue->GetAt(count);
			if (element->Id == item->GroupId)
			{
				vectProp->Append(item);
			}
		}

		vect->Append(ref new ProductPropertyDataModel(element, vectProp));
	}

	return vect;
}

ProductOptionPropertyDataModel::ProductOptionPropertyDataModel(OptionViewTypeModel^ selectedItem,
	IVector<OptionViewTypeModel^>^ option,
	PropertyViewTypeModel^ prop) : m_viewOptionSelectedItem(selectedItem), m_vectOption(option), m_prop(prop)
{
}

PropertyViewTypeModel^ ProductOptionPropertyDataModel::Prop::get()
{
	return m_prop;
}

OptionViewTypeModel^ ProductOptionPropertyDataModel::OptionSelectedItem::get()
{
	return m_viewOptionSelectedItem;
}

void ProductOptionPropertyDataModel::OptionSelectedItem::set(OptionViewTypeModel^ value)
{
	m_viewOptionSelectedItem = value;
}

IVector<OptionViewTypeModel^>^ ProductOptionPropertyDataModel::Option::get()
{
	return m_vectOption;
}

bool ProductOptionPropertyDataModel::FindPropertyValue(IVector<PropertyExtensionsCardModels^>^ oldValue, String^ newValue)
{
	if (oldValue == nullptr) return false;

	unsigned int size = oldValue->Size;
	for (unsigned int i = 0; i < size; i++)
	{
		auto element = oldValue->GetAt(i);
		if (element->Value != nullptr && element->Value == newValue)
		{
			return true;
		}
		else if (element->Option != nullptr)
		{
			unsigned int optionSize = element->Option->Size;
			for (unsigned int index = 0; index < optionSize; index++)
			{
				auto optionElement = element->Option->GetAt(index);
				if (optionElement->Value == newValue)
				{
					return true;
				}
			}
		}
	}

	return false;
}

IVector<ProductOptionPropertyDataModel^>^ ProductOptionPropertyDataModel::ToView(IVector<PropertyViewTypeModel^>^ propValue, IVector<PropertyExtensionsCardModels^>^ cardValue)
{
	if (propValue == nullptr) return nullptr;

	auto vectProp = ref new Vector<ProductOptionPropertyDataModel^>();

	for (const auto &item : propValue)
	{
		for (const auto &optionItem : item->Option)
		{
			if (FindPropertyValue(cardValue, optionItem->Value))
			{
				vectProp->Append(ref new ProductOptionPropertyDataModel(optionItem, item->Option, item));
				break;
			}
		}
	}

	return vectProp;
}