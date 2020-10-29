#pragma once

#include "DataModel\GroupCategorySource.h"

using namespace Enter::DataModel;

using namespace Platform;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace Enter
{
	namespace Template
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class CategoryTemplateSelector sealed : public DataTemplateSelector
		{
		public:
			property DataTemplate^ TemplateTree
			{
				DataTemplate^ get();
				void set(DataTemplate^ val);
			}

			property DataTemplate^ TemplateMore
			{
				DataTemplate^ get();
				void set(DataTemplate^ val);
			}
		private:
			DataTemplate^ source_TemplateTree;
			DataTemplate^ source_TemplateMore;
		protected:
			virtual DataTemplate^ SelectTemplateCore(Object^ item, DependencyObject^ container) override;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class FilterTemplateSelector sealed : public DataTemplateSelector
		{
		public:
			property DataTemplate^ SliderTemplate
			{
				DataTemplate^ get();
				void set(DataTemplate^ value);
			}

			property DataTemplate^ MultipleTemplate
			{
				DataTemplate^ get();
				void set(DataTemplate^ value);
			}

			property DataTemplate^ BooleanTemplate
			{
				DataTemplate^ get();
				void set(DataTemplate^ value);
			}
		private:
			DataTemplate^ source_sliderTemplate;
			DataTemplate^ source_multipleTemplate;
			DataTemplate^ source_booleanTemplate;
		protected:
			virtual DataTemplate^ SelectTemplateCore(Object^ item, DependencyObject^ container) override;
		};
	}
}