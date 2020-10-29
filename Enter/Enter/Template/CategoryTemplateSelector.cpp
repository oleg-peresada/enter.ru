#include "pch.h"
#include "CategoryTemplateSelector.h"

using namespace Enter::Template;
using namespace Enter::DataModel;

using namespace Platform;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

DataTemplate^ CategoryTemplateSelector::TemplateTree::get()
{
	return source_TemplateTree;
}

void CategoryTemplateSelector::TemplateTree::set(DataTemplate^ val)
{
	source_TemplateTree = val;
}

DataTemplate^ CategoryTemplateSelector::TemplateMore::get()
{
	return source_TemplateMore;
}

void CategoryTemplateSelector::TemplateMore::set(DataTemplate^ val)
{
	source_TemplateMore = val;
}

DataTemplate^ CategoryTemplateSelector::SelectTemplateCore(Object^ item, DependencyObject^ container)
{
	auto modelTree = dynamic_cast<GridRowAndColumnTree^>(item);
	if (modelTree != nullptr)
	{
		return TemplateTree;
	}

	auto modelMore = dynamic_cast<GridRowAndColumnMore^>(item);
	if (modelMore != nullptr)
	{
		return TemplateMore;
	}

	return DataTemplateSelector::SelectTemplateCore(item, container);
}

DataTemplate^ FilterTemplateSelector::SliderTemplate::get()
{
	return source_sliderTemplate;
}

void FilterTemplateSelector::SliderTemplate::set(DataTemplate^ value)
{
	source_sliderTemplate = value;
}

DataTemplate^ FilterTemplateSelector::MultipleTemplate::get()
{
	return source_multipleTemplate;
}

void FilterTemplateSelector::MultipleTemplate::set(DataTemplate^ value)
{
	source_multipleTemplate = value;
}

DataTemplate^ FilterTemplateSelector::BooleanTemplate::get()
{
	return source_booleanTemplate;
}

void FilterTemplateSelector::BooleanTemplate::set(DataTemplate^ value)
{
	source_booleanTemplate = value;
}

DataTemplate^ FilterTemplateSelector::SelectTemplateCore(Object^ item, DependencyObject^ container)
{
	auto filterItem = dynamic_cast<FilterProductDataModel^>(item);
	if (filterItem != nullptr)
	{
		switch (filterItem->Product->TypeId)
		{
		case 1:
			return this->BooleanTemplate;
			break;
		case 3:
			return this->SliderTemplate;
			break;
		case 5:
			return this->MultipleTemplate;
			break;
		case 6:
			return this->SliderTemplate;
			break;
		}
	}

	return DataTemplateSelector::SelectTemplateCore(item, container);
}