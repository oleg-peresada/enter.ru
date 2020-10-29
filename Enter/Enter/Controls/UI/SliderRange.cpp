//
// SliderRange.cpp
// Реализация класса SliderRange.
//

#include "pch.h"
#include "SliderRange.h"

using namespace Enter;
using namespace Enter::Controls::UI;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Documents;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Shapes;
using namespace Windows::UI::Xaml::Controls::Primitives;

SliderRangeItemEventArgs::SliderRangeItemEventArgs(double valueMin, double valueMax) : _valueMin(valueMin), _valueMax(valueMax)
{
}

double SliderRangeItemEventArgs::ValueMin::get()
{
	return _valueMin;
}

double SliderRangeItemEventArgs::ValueMax::get()
{
	return _valueMax;
}

String^ part_ThumbLeft = "PART_ThumbLeft";
String^ part_ThumbRight = "PART_ThumbRight";

String^ part_RectangleLeft = "PART_RectangleLeft";
String^ part_RectangleRight = "PART_RectangleRight";

SliderRange::SliderRange()
{
	DefaultStyleKey = "Enter.Controls.UI.SliderRange";
}

DependencyProperty^ SliderRange::_headerProperty = DependencyProperty::Register("Header",
	TypeName(Object::typeid), SliderRange::typeid, ref new PropertyMetadata(nullptr));

DependencyProperty^ SliderRange::HeaderProperty::get()
{
	return _headerProperty;
}

Object^ SliderRange::Header::get()
{
	return safe_cast<Object^>(GetValue(HeaderProperty));
}

void SliderRange::Header::set(Object^ value)
{
	SetValue(HeaderProperty, value);
}

DependencyProperty^ SliderRange::_headerTemplateProperty = DependencyProperty::Register("HeaderTemplate",
	TypeName(DataTemplate::typeid), SliderRange::typeid, ref new PropertyMetadata(nullptr));

DependencyProperty^ SliderRange::HeaderTemplateProperty::get()
{
	return _headerTemplateProperty;
}

DataTemplate^ SliderRange::HeaderTemplate::get()
{
	return safe_cast<DataTemplate^>(GetValue(HeaderTemplateProperty));
}

void SliderRange::HeaderTemplate::set(DataTemplate^ value)
{
	SetValue(HeaderTemplateProperty, value);
}

DependencyProperty^ SliderRange::_minimumProperty = DependencyProperty::Register("Minimum",
	TypeName(double::typeid), SliderRange::typeid, 
	ref new PropertyMetadata(0.0, ref new PropertyChangedCallback(&SliderRange::OnMinimumChanged)));

void SliderRange::OnMinimumChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args)
{
	auto sliderRange = dynamic_cast<SliderRange^>(sender);
	if (sliderRange != nullptr)
	{
		sliderRange->UpdateMinimum();
	}
}

DependencyProperty^ SliderRange::MinimumProperty::get()
{
	return _minimumProperty;
}

double SliderRange::Minimum::get()
{
	return safe_cast<double>(GetValue(MinimumProperty));
}

void SliderRange::Minimum::set(double value)
{
	SetValue(MinimumProperty, value);
}

DependencyProperty^ SliderRange::_maximumProperty = DependencyProperty::Register("Maximum",
	TypeName(double::typeid), SliderRange::typeid, 
	ref new PropertyMetadata(0.0, ref new PropertyChangedCallback(&SliderRange::OnMaximumChanged)));

void SliderRange::OnMaximumChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args)
{
	auto sliderRange = dynamic_cast<SliderRange^>(sender);
	if (sliderRange != nullptr)
	{
		sliderRange->UpdateMaximum();
	}
}

DependencyProperty^ SliderRange::MaximumProperty::get()
{
	return _maximumProperty;
}

double SliderRange::Maximum::get()
{
	return safe_cast<double>(GetValue(MaximumProperty));
}

void SliderRange::Maximum::set(double value)
{
	SetValue(MaximumProperty, value);
}

DependencyProperty^ SliderRange::_valueLeftProperty = DependencyProperty::Register("ValueLeft",
	TypeName(double::typeid), SliderRange::typeid, 
	ref new PropertyMetadata(0.0, ref new PropertyChangedCallback(&SliderRange::OnValueLeftChanged)));

void SliderRange::OnValueLeftChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args)
{
	auto sliderRange = dynamic_cast<SliderRange^>(sender);
	if (sliderRange != nullptr)
	{
		sliderRange->UpdateValueLeft();
	}
}

DependencyProperty^ SliderRange::ValueLeftProperty::get()
{
	return _valueLeftProperty;
}

double SliderRange::ValueLeft::get()
{
	return safe_cast<double>(GetValue(ValueLeftProperty));
}

void SliderRange::ValueLeft::set(double value)
{
	SetValue(ValueLeftProperty, value);
}

DependencyProperty^ SliderRange::_valueRightProperty = DependencyProperty::Register("ValueRight",
	TypeName(double::typeid), SliderRange::typeid, 
	ref new PropertyMetadata(0.0, ref new PropertyChangedCallback(&SliderRange::OnValueRightChanged)));

void SliderRange::OnValueRightChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args)
{
	auto sliderRange = dynamic_cast<SliderRange^>(sender);
	if (sliderRange != nullptr)
	{
		sliderRange->UpdateValueRight();
	}
}

DependencyProperty^ SliderRange::ValueRightProperty::get()
{
	return _valueRightProperty;
}

double SliderRange::ValueRight::get()
{
	return safe_cast<double>(GetValue(ValueRightProperty));
}

void SliderRange::ValueRight::set(double value)
{
	SetValue(ValueRightProperty, value);
}

DependencyProperty^ SliderRange::_uintProperty = DependencyProperty::Register("Uint",
	TypeName(Object::typeid), SliderRange::typeid, ref new PropertyMetadata(nullptr));

DependencyProperty^ SliderRange::UintProperty::get()
{
	return _uintProperty;
}

Object^ SliderRange::Uint::get()
{
	return safe_cast<Object^>(GetValue(UintProperty));
}

void SliderRange::Uint::set(Object^ value)
{
	SetValue(UintProperty, value);
}

DependencyProperty^ SliderRange::_stepProperty = DependencyProperty::Register("Step",
	TypeName(String::typeid), SliderRange::typeid, ref new PropertyMetadata(nullptr));

DependencyProperty^ SliderRange::StepProperty::get()
{
	return _stepProperty;
}

String^ SliderRange::Step::get()
{
	return safe_cast<String^>(GetValue(StepProperty));
}

void SliderRange::Step::set(String^ value)
{
	SetValue(StepProperty, value);
}

DependencyProperty^ SliderRange::_commandProperty = DependencyProperty::Register("Command",
	TypeName(Windows::UI::Xaml::Input::ICommand::typeid), SliderRange::typeid, ref new PropertyMetadata(nullptr));

DependencyProperty^ SliderRange::CommandProperty::get()
{
	return _commandProperty;
}

Windows::UI::Xaml::Input::ICommand^ SliderRange::Command::get()
{
	return safe_cast<Windows::UI::Xaml::Input::ICommand^>(GetValue(CommandProperty));
}

void SliderRange::Command::set(Windows::UI::Xaml::Input::ICommand^ value)
{
	SetValue(CommandProperty, value);
}

DependencyProperty^ SliderRange::_commandParameterCommand = DependencyProperty::Register("CommandParameter",
	TypeName(Object::typeid), SliderRange::typeid, ref new PropertyMetadata(nullptr));

DependencyProperty^ SliderRange::CommandParameterProperty::get()
{
	return _commandParameterCommand;
}

Object^ SliderRange::CommandParameter::get()
{
	return safe_cast<Object^>(GetValue(CommandParameterProperty));
}

void SliderRange::CommandParameter::set(Object^ value)
{
	SetValue(CommandParameterProperty, value);
}

DependencyProperty^ SliderRange::_positionLeftProperty = DependencyProperty::Register("PositionLeft",
	TypeName(double::typeid), SliderRange::typeid, 
	ref new PropertyMetadata(0.0, ref new PropertyChangedCallback(&SliderRange::OnMinimumChanged)));

DependencyProperty^ SliderRange::PositionLeftProperty::get()
{
	return _positionLeftProperty;
}

double SliderRange::PositionLeft::get()
{
	return safe_cast<double>(GetValue(PositionLeftProperty));
}

void SliderRange::PositionLeft::set(double value)
{
	SetValue(PositionLeftProperty, value);
}

DependencyProperty^ SliderRange::_positionRightProperty = DependencyProperty::Register("PositionRight",
	TypeName(double::typeid), SliderRange::typeid, 
	ref new PropertyMetadata(0.0, ref new PropertyChangedCallback(&SliderRange::OnMaximumChanged)));

DependencyProperty^ SliderRange::PositionRightProperty::get()
{
	return _positionRightProperty;
}

double SliderRange::PositionRight::get()
{
	return safe_cast<double>(GetValue(PositionRightProperty));
}

void SliderRange::PositionRight::set(double value)
{
	SetValue(PositionRightProperty, value);
}

void SliderRange::OnApplyTemplate()
{
	_thumbLeft = dynamic_cast<Thumb^>(GetTemplateChild(part_ThumbLeft));
	if (_thumbLeft != nullptr)
	{
		dragLeftDeltaToken = this->_thumbLeft->DragDelta += ref new DragDeltaEventHandler(this, &SliderRange::OnDragLeftDelta);
	}

	_thumbRight = dynamic_cast<Thumb^>(GetTemplateChild(part_ThumbRight));
	if (_thumbRight != nullptr)
	{
		dragRightDeltaToken = _thumbRight->DragDelta += ref new DragDeltaEventHandler(this, &SliderRange::OnDragRightDelta);
	}

	_rectangleLeft = dynamic_cast<Rectangle^>(GetTemplateChild(part_RectangleLeft));
	_rectangleRight = dynamic_cast<Rectangle^>(GetTemplateChild(part_RectangleRight));

	sizeChangedToken = this->SizeChanged += ref new SizeChangedEventHandler(this, &SliderRange::OnSizeChanged);
	unloadedToken = this->Unloaded += ref new RoutedEventHandler(this, &SliderRange::OnUnloaded);

	return Control::OnApplyTemplate();
}

void SliderRange::OnSizeChanged(Object ^sender, SizeChangedEventArgs ^e)
{
	if (e->NewSize.Width != e->PreviousSize.Width)
	{
		this->UpdateMinimum();
		this->UpdateMaximum();
	}
}

void SliderRange::OnDragLeftDelta(Object ^sender, DragDeltaEventArgs ^e)
{
	auto left = Canvas::GetLeft(_thumbLeft);
	auto right = Canvas::GetLeft(_thumbRight);
	auto pixel = e->HorizontalChange;

	if ((left + pixel) < 0)
	{
		ValueLeft = this->Minimum;
	}
	else if ((left + pixel) < (right - 20) && (left + pixel) > 0)
	{
		PositionLeft = pixel + left;

		auto totalSize = this->ActualWidth;
		auto ratio = pixel / totalSize;
		auto rangeSize = Maximum - Minimum;
		auto range = rangeSize * ratio;

		if (Step == "integer")
		{
			ValueLeft += safe_cast<int>(range);
		}
		else
		{
			ValueLeft += range;
		}
	}
}

void SliderRange::OnDragRightDelta(Object ^sender, DragDeltaEventArgs ^e)
{
	auto left = Canvas::GetLeft(_thumbLeft);
	auto right = Canvas::GetLeft(_thumbRight);
	auto pixel = e->HorizontalChange;
	
	if ((right + pixel + _thumbRight->ActualWidth) > (this->ActualWidth + _thumbRight->ActualWidth))
	{
		ValueRight = this->Maximum;
	}
	else if ((right + pixel) > (left + 20) && (right + e->HorizontalChange) < this->ActualWidth)
	{
		PositionRight = pixel + right;

		auto totalSize = this->ActualWidth;
		auto ratio = pixel / totalSize;
		auto rangeSize = Maximum - Minimum;
		auto range = rangeSize * ratio;

		if (Step == "integer")
		{
			ValueRight += safe_cast<int>(range);
		}
		else
		{
			ValueRight += range;
		}
	}
}

void SliderRange::UpdateMinimum()
{
	this->ValueLeft = ValueLeft == 0.0 ? this->Minimum : ValueLeft;
	double position = PositionLeft == 0.0 ? 0.0 : PositionLeft;

	if (_thumbLeft != nullptr)
	{
		Canvas::SetLeft(this->_thumbLeft, position);
	}

	if (_rectangleLeft != nullptr)
	{
		_rectangleLeft->Width = position;
	}
}

void SliderRange::UpdateMaximum()
{
	this->ValueRight = ValueRight == 0.0 ? this->Maximum : ValueRight;
	double position = PositionRight == 0.0 ? this->ActualWidth : PositionRight;

	if (_thumbRight != nullptr)
	{
		Canvas::SetLeft(this->_thumbRight, position);
	}

	if (_rectangleRight != nullptr)
	{
		Canvas::SetLeft(_rectangleRight, position);
		_rectangleRight->Width = this->ActualWidth - position;
	}
}

void SliderRange::UpdateValueLeft()
{
	if (ValueLeft  > Minimum || ValueRight < Maximum)
	{
		double min = std::min<double>(this->ValueLeft, this->ValueRight);
		double max = std::max<double>(this->ValueLeft, this->ValueRight);

		SliderRangeValue(this, ref new SliderRangeItemEventArgs(min, max));

		Object^ ExecuteParameter = CommandParameter == nullptr ? this : CommandParameter;
		Command->Execute(ExecuteParameter);
		Command->CanExecute(ExecuteParameter);
	}
}

void SliderRange::UpdateValueRight()
{
	if (ValueLeft > Minimum || ValueRight < Maximum)
	{
		double min = std::min<double>(this->ValueLeft, this->ValueRight);
		double max = std::max<double>(this->ValueLeft, this->ValueRight);

		SliderRangeValue(this, ref new SliderRangeItemEventArgs(min, max));

		Object^ ExecuteParameter = CommandParameter == nullptr ? this : CommandParameter;
		Command->Execute(ExecuteParameter);
		Command->CanExecute(ExecuteParameter);
	}
}

void SliderRange::OnUnloaded(Object ^sender, RoutedEventArgs ^e)
{
	if (_thumbLeft != nullptr)
	{
		_thumbLeft->DragDelta -= dragLeftDeltaToken;
	}

	if (_thumbRight != nullptr)
	{
		_thumbRight->DragDelta -= dragRightDeltaToken;
	}

	this->SizeChanged -= sizeChangedToken;
	this->Unloaded -= unloadedToken;
}