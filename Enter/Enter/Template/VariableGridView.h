#pragma once

#include "DataModel\GroupCategorySource.h"

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace Enter
{
	namespace Template
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class GridViewOffsetBase : public GridView
		{
		public:
			virtual ~GridViewOffsetBase();

			property static DependencyProperty^ HorizontalOffsetProperty
			{
				DependencyProperty^ get();
			}

			property double HorizontalOffset
			{
				double get();
				void set(double value);
			}
		internal:
			GridViewOffsetBase();
		private:
			ScrollViewer^ m_ScrollViewer;
			static DependencyProperty^ m_HorizontalProperty;

			EventRegistrationToken tokenLoaded;
			EventRegistrationToken tokenUpdate;
			EventRegistrationToken tokenViewChanged;

			void OnLoaded(Object ^sender, RoutedEventArgs ^e);
			void OnViewChanged(Object ^sender, ScrollViewerViewChangedEventArgs ^args);
			void OnLayoutUpdated(Object ^sender, Object ^args);
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class VariableGridView sealed : public GridViewOffsetBase
		{
		public:
			VariableGridView();
		protected:
			virtual void PrepareContainerForItemOverride(DependencyObject^ element, Object^ item) override;
		};

		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class GridViewOffset sealed : public GridViewOffsetBase
		{
		public:
			GridViewOffset();
		};
	}
}