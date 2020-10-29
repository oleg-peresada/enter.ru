#pragma once

using namespace EnterStore::Models;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace DataModel
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class GroupCategoryModel sealed
		{
		public:
			property String^ Title
			{
				String^ get();
				void set(String^ val);
			}

			property IObservableVector<Object^>^ Tree
			{
				IObservableVector<Object^>^ get();
				void set(IObservableVector<Object^>^ val);
			}
		private:
			String^ source_Title;
			IObservableVector<Object^>^ source_Tree;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class GridRowAndColumnTree sealed
		{
		public:
			property unsigned int Row
			{
				unsigned int get();
			}

			property unsigned int Column
			{
				unsigned int get();
			}

			property Object^ Content
			{
				Object^ get();
			}
		internal:
			GridRowAndColumnTree(unsigned int row, unsigned int column, Object^ content);
		private:
			unsigned int source_Row;
			unsigned int source_Column;
			Object^ source_Content;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class GridRowAndColumnMore sealed
		{
		public:
			property unsigned int Row
			{
				unsigned int get();
			}

			property unsigned int Column
			{
				unsigned int get();
			}

			property String^ Name
			{
				String^ get();
			}

			property Object^ Content
			{
				Object^ get();
			}
		internal:
			GridRowAndColumnMore(unsigned int row, unsigned int column, String^ name, Object^ content);
		private:
			unsigned int source_Row;
			unsigned int source_Column;
			String^ source_name;
			Object^ source_content;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class GroupCategorySource sealed
		{
		internal:
			GroupCategorySource(IVector<CategoryTreeModels^>^ viewModel);
			IObservableVector<GroupCategoryModel^>^ GroupCollection();
		private:
			IVector<CategoryTreeModels^>^ source_viewModel;
		};

		//Создание группы магазинов
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ShopGroupDataModel sealed
		{
		public:
			property String^ Title
			{
				String^ get();
			}

			property IVector<ShopListModels^>^ Shop
			{
				IVector<ShopListModels^>^ get();
			}
		internal:
			ShopGroupDataModel();
			ShopGroupDataModel(String^ title, IVector<ShopListModels^>^ shop);

			//Представление группы магазинов
			IVector<ShopGroupDataModel^>^ ToViewShop(IVector<ShopListModels^>^ content);
		private:
			String^ source_Title;
			IVector<ShopListModels^>^ source_Shop;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class FilterOptionsDataModel sealed
		{
		public:
			property EnterStore::Models::FilterOptionsModels^ Option
			{
				EnterStore::Models::FilterOptionsModels^ get();
			}

			property bool IsChecked
			{
				bool get();
				void set(bool value);
			}
		internal:
			FilterOptionsDataModel(EnterStore::Models::FilterOptionsModels^ option);
		private:
			EnterStore::Models::FilterOptionsModels^ source_Option;
			bool source_IsChecked;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class FilterProductDataModel sealed
		{
		public:
			property IVector<FilterOptionsDataModel^>^ Options
			{
				IVector<FilterOptionsDataModel^>^ get();
			}

			property EnterStore::Models::FilterProductModels^ Product
			{
				EnterStore::Models::FilterProductModels^ get();
			}

			property double Min
			{
				double get();
				void set(double value);
			}

			property double Max
			{
				double get();
				void set(double value);
			}

			property double PositionLeft
			{
				double get();
				void set(double value);
			}

			property double PositionRight
			{
				double get();
				void set(double value);
			}

			property bool Yes
			{
				bool get();
				void set(bool value);
			}

			property bool No
			{
				bool get();
				void set(bool value);
			}
		internal:
			FilterProductDataModel(EnterStore::Models::FilterProductModels^ product, 
				IVector<FilterOptionsDataModel^>^ options, double min, double max, double positionLeft, double positionRight);
		private:
			IVector<FilterOptionsDataModel^>^ source_options;
			EnterStore::Models::FilterProductModels^ source_product;
			double source_min;
			double source_max;
			double source_positionLeft;
			double source_positionRight;
			bool source_yes;
			bool source_no;
		};

		class FilterConversation
		{
		public:
			static IVector<FilterProductDataModel^>^ ToConvert(IVector<EnterStore::Models::FilterProductModels^>^ valueVector);
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductPropertyDataModel sealed
		{
		public:
			property PropertyGroupExetensionsModels^ PropertyGroup
			{
				PropertyGroupExetensionsModels^ get();
			}

			property IVector<PropertyExtensionsCardModels^>^ PropertyVector
			{
				IVector<PropertyExtensionsCardModels^>^ get();
			}
		internal:
			ProductPropertyDataModel(PropertyGroupExetensionsModels^ propertyGroup, IVector<PropertyExtensionsCardModels^>^ propertyVector);
		private:
			PropertyGroupExetensionsModels^ source_propertyGroup;
			IVector<PropertyExtensionsCardModels^>^ source_PropertyVector;
		};

		class ProductPropertyConvert
		{
		public:
			static IVector<ProductPropertyDataModel^>^ PropertyGroupCreate(IVector<PropertyGroupExetensionsModels^>^ 
				propertyGroup, IVector<PropertyExtensionsCardModels^>^ propertyValue);
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductOptionPropertyDataModel sealed
		{
		public:
			property PropertyViewTypeModel^ Prop
			{
				PropertyViewTypeModel^ get();
			}

			property OptionViewTypeModel^ OptionSelectedItem
			{
				OptionViewTypeModel^ get();
				void set(OptionViewTypeModel^ value);
			}

			property IVector<OptionViewTypeModel^>^ Option
			{
				IVector<OptionViewTypeModel^>^ get();
			}
		internal:
			ProductOptionPropertyDataModel(OptionViewTypeModel^ selectedItem,
				IVector<OptionViewTypeModel^>^ option,
				PropertyViewTypeModel^ prop);
			static bool FindPropertyValue(IVector<PropertyExtensionsCardModels^>^ oldValue, String^ newValue);
			static IVector<ProductOptionPropertyDataModel^>^ 
				ToView(IVector<PropertyViewTypeModel^>^ propValue,
				IVector<PropertyExtensionsCardModels^>^ cardValue);
		private:
			OptionViewTypeModel^ m_viewOptionSelectedItem;
			IVector<OptionViewTypeModel^>^ m_vectOption;
			PropertyViewTypeModel^ m_prop;
		};
	}
}