#pragma once

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace EnterStore
{
	namespace Models
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductViewTypeModel sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ Name
			{
				String^ get();
			}

			property String^ Token
			{
				String^ get();
			}

			property String^ MediaImage
			{
				String^ get();
			}
		internal:
			ProductViewTypeModel(int id, String^ name, String^ token, String^ mediaImage);
		private:
			int m_id;
			String^ m_name;
			String^ m_token;
			String^ m_mediaImage;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class OptionViewTypeModel sealed
		{
		public:
			property String^ Value
			{
				String^ get();
			}

			property ProductViewTypeModel^ Product
			{
				ProductViewTypeModel^ get();
			}
		internal:
			OptionViewTypeModel(String^ value, ProductViewTypeModel^ product);
		private:
			String^ m_value;
			ProductViewTypeModel^ m_product;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PropertyViewTypeModel sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property int TypeId
			{
				int get();
			}

			property String^ Name
			{
				String^ get();
			}

			property String^ Unit
			{
				String^ get();
			}

			property bool IsMultiple
			{
				bool get();
			}

			property IVector<OptionViewTypeModel^>^ Option
			{
				IVector<OptionViewTypeModel^>^ get();
			}
		internal:
			PropertyViewTypeModel(int id, int typeId, String^ name, String^ unit, bool isMultiple, IVector<OptionViewTypeModel^>^ option);
		private:
			int m_id;
			int m_typeId;
			String^ m_name;
			String^ m_unit;
			bool m_isMultiple;
			IVector<OptionViewTypeModel^>^ m_option;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PromoLabel sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ MediaImage
			{
				String^ get();
			}

			property String^ Name
			{
				String^ get();
			}
		internal:
			PromoLabel(int id, String^ mediaImage, String^ name);
		private:
			int m_id;
			String^ m_mediaImage;
			String^ m_name;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class OptionExtensionsCardModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ Value
			{
				String^ get();
			}

			property String^ Hint
			{
				String^ get();
			}
		internal:
			OptionExtensionsCardModels(int id, String^ value, String^ hint);
		private:
			int source_id;
			String^ source_value;
			String^ source_hint;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PropertyExtensionsCardModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property unsigned int GroupId
			{
				unsigned int get();
			}

			property int TypeId
			{
				int get();
			}

			property String^ Name
			{
				String^ get();
			}

			property String^ Hint
			{
				String^ get();
			}

			property String^ Value
			{
				String^ get();
			}

			property String^ ValueHint
			{
				String^ get();
			}

			property String^ Unit
			{
				String^ get();
			}

			property IVector<OptionExtensionsCardModels^>^ Option
			{
				IVector<OptionExtensionsCardModels^>^ get();
				void set(IVector<OptionExtensionsCardModels^>^ val);
			}
		internal:
			PropertyExtensionsCardModels(int id,
				unsigned int groupId,
				int typeId,
				String^ name,
				String^ hint,
				String^ value,
				String^ valueHint,
				String^ unit);
		private:
			int source_id;
			unsigned int source_groupId;
			int source_typeId;
			String^ source_name;
			String^ source_hint;
			String^ source_value;
			String^ source_valueHint;
			String^ source_unit;
			IVector<OptionExtensionsCardModels^>^ source_option;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class PropertyGroupExetensionsModels sealed
		{
		public:
			property unsigned int Id
			{
				unsigned int get();
			}

			property String^ Name
			{
				String^ get();
			}

			property unsigned int Position
			{
				unsigned int get();
			}
		internal:
			PropertyGroupExetensionsModels(unsigned int id, String^ name, unsigned int position);
		private:
			unsigned int source_id;
			String^ source_name;
			unsigned int source_position;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class MediaExtensionsCardModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ Source
			{
				String^ get();
			}
		internal:
			MediaExtensionsCardModels(int id, String^ source);
		private:
			int source_id;
			String^ source_Source;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class StockCardModels sealed
		{
		public:
			property int StoreId
			{
				int get();
			}

			property int ShopId
			{
				int get();
			}

			property unsigned int Quantity
			{
				unsigned int get();
			}
		internal:
			StockCardModels(int storeId, int shopId, unsigned int quantity);
		private:
			int source_storeId;
			int source_shopId;
			unsigned int source_quantity;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class StateCardModels sealed
		{
		public:
			property bool IsShop
			{
				bool get();
			}

			property bool IsStore
			{
				bool get();
			}

			property bool IsBuyable
			{
				bool get();
			}
		internal:
			StateCardModels(bool isShop, bool isStore, bool isBuyable);
		private:
			bool source_IsShop;
			bool source_IsStore;
			bool source_IsBuyable;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductExtensionsCardModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property int TypeId
			{
				int get();
			}

			property String^ Name
			{
				String^ get();
			}

			property String^ Token
			{
				String^ get();
			}

			property String^ Article
			{
				String^ get();
			}

			property String^ Description
			{
				String^ get();
			}

			property double Price
			{
				double get();
			}

			property double PriceOld
			{
				double get();
			}

			property String^ MediaImage
			{
				String^ get();
			}

			property IVector<PropertyExtensionsCardModels^>^ Property
			{
				IVector<PropertyExtensionsCardModels^>^ get();
				void set(IVector<PropertyExtensionsCardModels^>^ val);
			}

			property IVector<PropertyGroupExetensionsModels^>^ PropertyGroup
			{
				IVector<PropertyGroupExetensionsModels^>^ get();
				void set(IVector<PropertyGroupExetensionsModels^>^ value);
			}

			property IVector<PromoLabel^>^ Label
			{
				IVector<PromoLabel^>^ get();
				void set(IVector<PromoLabel^>^ value);
			}

			property IVector<MediaExtensionsCardModels^>^ Media
			{
				IVector<MediaExtensionsCardModels^>^ get();
				void set(IVector<MediaExtensionsCardModels^>^ val);
			}

			property IVector<PropertyViewTypeModel^>^ ModelProperty
			{
				IVector<PropertyViewTypeModel^>^ get();
				void set(IVector<PropertyViewTypeModel^>^ value);
			}

			property StateCardModels^ State
			{
				StateCardModels^ get();
				void set(StateCardModels^ val);
			}

			property StockCardModels^ Stock
			{
				StockCardModels^ get();
				void set(StockCardModels^ val);
			}

			property IVector<int>^ Accessories
			{
				IVector<int>^ get();
				void set(IVector<int>^ value);
			}
		internal:
			ProductExtensionsCardModels(int id,
				int typeId,
				String^ name,
				String^ token,
				String^ article,
				String^ description,
				double price,
				double priceOld,
				String^ mediaImage);
		private:
			int source_Id;
			int source_typeId;
			String^ source_name;
			String^ source_token;
			String^ source_article;
			String^ source_description;
			double source_price;
			double source_priceOld;
			String^ source_mediaImage;
			IVector<PropertyExtensionsCardModels^>^ source_property;
			IVector<PropertyGroupExetensionsModels^>^ source_propertyGroup;
			IVector<PromoLabel^>^ source_label;
			IVector<MediaExtensionsCardModels^>^ source_media;
			IVector<PropertyViewTypeModel^>^ source_modelProperty;
			StateCardModels^ source_state;
			StockCardModels^ source_stock;
			IVector<int>^ source_accessories;
		};
	}
}