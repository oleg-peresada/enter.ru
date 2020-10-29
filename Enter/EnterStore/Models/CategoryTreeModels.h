#pragma once

using namespace Platform;
using namespace Windows::Foundation::Collections;

namespace EnterStore
{
	namespace Models
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class CategoryTreeModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ ParentId
			{
				String^ get();
			}

			property bool IsFurniture
			{
				bool get();
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

			property unsigned int Level
			{
				unsigned int get();
			}

			property String^ SeoHeader
			{
				String^ get();
			}

			property String^ ProductCount
			{
				String^ get();
			}

			property String^ ProductCountGlobal
			{
				String^ get();
			}

			property bool HasChildren
			{
				bool get();
			}

			property IVector<CategoryTreeModels^>^ Children
			{
				IVector<CategoryTreeModels^>^ get();
				void set(IVector<CategoryTreeModels^>^ val);
			}
		internal:
			CategoryTreeModels(int id, 
				String^ parentId, 
				bool isFurniture, 
				String^ name, 
				String^ token, 
				String^ mediaImage,
				unsigned int level,
				String^ seoHeader,
				String^ productCount,
				String^ productCountGlobal,
				bool hasChildren);
		private:
			int tree_id;
			String^ tree_parentId;
			bool tree_isFurniture;
			String^ tree_name;
			String^ tree_token;
			String^ tree_mediaImage;
			unsigned int tree_level;
			String^ tree_seoHeader;
			String^ tree_productCount;
			String^ tree_productCountGlobal;
			bool tree_hasChildren;
			IVector<CategoryTreeModels^> ^ tree_children;
		};
	}
}