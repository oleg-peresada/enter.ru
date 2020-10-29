#include "pch.h"
#include "VariableGridView.h"

using namespace Enter::Template;
using namespace Enter::DataModel;

using namespace Platform;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

/*

GridViewOffsetBase

*/

GridViewOffsetBase::GridViewOffsetBase() : GridView()
{
	tokenLoaded = this->Loaded += ref new RoutedEventHandler(this, &GridViewOffsetBase::OnLoaded);
}

GridViewOffsetBase::~GridViewOffsetBase()
{
	this->Loaded -= tokenLoaded;

	if (m_ScrollViewer != nullptr)
	{
		m_ScrollViewer->ViewChanged -= tokenViewChanged;
	}
}

DependencyProperty^ GridViewOffsetBase::m_HorizontalProperty = DependencyProperty::Register("HorizontalOffset",
	TypeName(double::typeid), TypeName(GridViewOffsetBase::typeid), ref new PropertyMetadata(0.0));

DependencyProperty^ GridViewOffsetBase::HorizontalOffsetProperty::get()
{
	return m_HorizontalProperty;
}

double GridViewOffsetBase::HorizontalOffset::get()
{
	return safe_cast<double>(GetValue(HorizontalOffsetProperty));
}

void GridViewOffsetBase::HorizontalOffset::set(double value)
{
	SetValue(HorizontalOffsetProperty, value);
}

void GridViewOffsetBase::OnLoaded(Object ^sender, RoutedEventArgs ^e)
{
	m_ScrollViewer = dynamic_cast<ScrollViewer^>(this->GetTemplateChild("ScrollViewer"));
	if (m_ScrollViewer != nullptr)
	{
		tokenUpdate = m_ScrollViewer->LayoutUpdated += ref new EventHandler<Platform::Object^>(this, &GridViewOffsetBase::OnLayoutUpdated);
		tokenViewChanged = m_ScrollViewer->ViewChanged += ref new EventHandler<ScrollViewerViewChangedEventArgs^>(this, &GridViewOffsetBase::OnViewChanged);
	}
}

void GridViewOffsetBase::OnViewChanged(Object ^sender, ScrollViewerViewChangedEventArgs ^args)
{
	if (!args->IsIntermediate && m_ScrollViewer != nullptr)
	{
		HorizontalOffset = m_ScrollViewer->HorizontalOffset;
	}
}

void GridViewOffsetBase::OnLayoutUpdated(Object ^sender, Object ^args)
{
	if (m_ScrollViewer != nullptr && (m_ScrollViewer->ComputedHorizontalScrollBarVisibility == Windows::UI::Xaml::Visibility::Visible
		|| (m_ScrollViewer->ComputedVerticalScrollBarVisibility == Windows::UI::Xaml::Visibility::Visible)))
	{
		m_ScrollViewer->ChangeView(HorizontalOffset, nullptr, nullptr);
		m_ScrollViewer->LayoutUpdated -= tokenUpdate;
	}
}

/*

VariableGridView

*/

VariableGridView::VariableGridView() : GridViewOffsetBase()
{
}

void VariableGridView::PrepareContainerForItemOverride(DependencyObject^ element, Object^ item)
{
	auto modelTree = dynamic_cast<GridRowAndColumnTree^>(item);
	if (modelTree != nullptr)
	{
		element->SetValue(VariableSizedWrapGrid::ColumnSpanProperty, modelTree->Column);
		element->SetValue(VariableSizedWrapGrid::RowSpanProperty, modelTree->Row);
	}

	auto modelMore = dynamic_cast<GridRowAndColumnMore^>(item);
	if (modelMore != nullptr)
	{
		element->SetValue(VariableSizedWrapGrid::ColumnSpanProperty, modelMore->Column);
		element->SetValue(VariableSizedWrapGrid::RowSpanProperty, modelMore->Row);
	}

	GridViewOffsetBase::PrepareContainerForItemOverride(element, item);
}

/*

GridViewOffset

*/

GridViewOffset::GridViewOffset() : GridViewOffsetBase()
{
}