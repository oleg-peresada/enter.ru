//
// SliderRange.h
// Объявление класса SliderRange.
//

#pragma once

#include <algorithm>

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Shapes;

namespace Enter
{
	namespace Controls
	{
		namespace UI
		{
			[Windows::Foundation::Metadata::WebHostHidden]
			public ref class SliderRangeItemEventArgs sealed
			{
			public:
				property double ValueMin
				{
					double get();
				}

				property double ValueMax
				{
					double get();
				}
			internal:
				SliderRangeItemEventArgs(double valueMin, double valueMax);
			private:
				double _valueMin;
				double _valueMax;
			};

			public delegate void SliderRangeValueHandler(Object^ sender, SliderRangeItemEventArgs^ args);

			[Windows::Foundation::Metadata::WebHostHidden]
			public ref class SliderRange sealed : public Windows::UI::Xaml::Controls::Control
			{
			public:
				event SliderRangeValueHandler^ SliderRangeValue;

				property static DependencyProperty^ HeaderProperty
				{
					DependencyProperty^ get();
				}

				property Object^ Header
				{
					Object^ get();
					void set(Object^ value);
				}

				property static DependencyProperty^ HeaderTemplateProperty
				{
					DependencyProperty^ get();
				}

				property DataTemplate^ HeaderTemplate
				{
					DataTemplate^ get();
					void set(DataTemplate^ value);
				}

				property static DependencyProperty^ MinimumProperty
				{
					DependencyProperty^ get();
				}

				property double Minimum
				{
					double get();
					void set(double value);
				}

				property static DependencyProperty^ MaximumProperty
				{
					DependencyProperty^ get();
				}

				property double Maximum
				{
					double get();
					void set(double value);
				}

				property static DependencyProperty^ ValueLeftProperty
				{
					DependencyProperty^ get();
				}

				property double ValueLeft
				{
					double get();
					void set(double value);
				}

				property static DependencyProperty^ ValueRightProperty
				{
					DependencyProperty^ get();
				}

				property double ValueRight
				{
					double get();
					void set(double value);
				}

				property static DependencyProperty^ UintProperty
				{
					DependencyProperty^ get();
				}

				property Object^ Uint
				{
					Object^ get();
					void set(Object^ value);
				}

				property static DependencyProperty^ StepProperty
				{
					DependencyProperty^ get();
				}

				property String^ Step
				{
					String^ get();
					void set(String^ value);
				}

				property static DependencyProperty^ CommandProperty
				{
					DependencyProperty^ get();
				}

				property Windows::UI::Xaml::Input::ICommand^ Command
				{
					Windows::UI::Xaml::Input::ICommand^ get();
					void set(Windows::UI::Xaml::Input::ICommand^ value);
				}

				property static DependencyProperty^ CommandParameterProperty
				{
					DependencyProperty^ get();
				}

				property Object^ CommandParameter
				{
					Object^ get();
					void set(Object^ value);
				}

				property static DependencyProperty^ PositionLeftProperty
				{
					DependencyProperty^ get();
				}

				property double PositionLeft
				{
					double get();
					void set(double value);
				}

				property static DependencyProperty^ PositionRightProperty
				{
					DependencyProperty^ get();
				}

				property double PositionRight
				{
					double get();
					void set(double value);
				}

				SliderRange();
			private:
				event SliderRangeValueHandler^ OnSliderRangeValue
				{
					EventRegistrationToken add(SliderRangeValueHandler^ handler)
					{
						return SliderRangeValue += handler;
					}

					void remove(EventRegistrationToken token)
					{
						SliderRangeValue -= token;
					}

					void raise(Object^ sender, SliderRangeItemEventArgs^ args)
					{
						SliderRangeValue(sender, args);
					}
				}

				EventRegistrationToken sizeChangedToken;
				EventRegistrationToken unloadedToken;
				EventRegistrationToken dragRightDeltaToken;
				EventRegistrationToken dragLeftDeltaToken;

				static DependencyProperty^ _headerProperty;
				static DependencyProperty^ _headerTemplateProperty;
				static DependencyProperty^ _minimumProperty;
				static DependencyProperty^ _maximumProperty;
				static DependencyProperty^ _valueLeftProperty;
				static DependencyProperty^ _valueRightProperty;
				static DependencyProperty^ _uintProperty;
				static DependencyProperty^ _stepProperty;
				static DependencyProperty^ _commandProperty;
				static DependencyProperty^ _commandParameterCommand;
				static DependencyProperty^ _positionLeftProperty;
				static DependencyProperty^ _positionRightProperty;

				Thumb^ _thumbLeft;
				Thumb^ _thumbRight;

				Rectangle^ _rectangleLeft;
				Rectangle^ _rectangleRight;

				static void OnMinimumChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args);
				static void OnMaximumChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args);
				static void OnValueLeftChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args);
				static void OnValueRightChanged(DependencyObject^ sender, DependencyPropertyChangedEventArgs^ args);

				void OnUnloaded(Platform::Object ^sender, Windows::UI::Xaml::RoutedEventArgs ^e);
				void OnSizeChanged(Platform::Object ^sender, Windows::UI::Xaml::SizeChangedEventArgs ^e);
				void OnDragRightDelta(Platform::Object ^sender, Windows::UI::Xaml::Controls::Primitives::DragDeltaEventArgs ^e);
				void OnDragLeftDelta(Platform::Object ^sender, Windows::UI::Xaml::Controls::Primitives::DragDeltaEventArgs ^e);
				void UpdateMinimum();
				void UpdateMaximum();
				void UpdateValueLeft();
				void UpdateValueRight();
			protected:
				virtual void OnApplyTemplate() override;
};
		}
	}
}