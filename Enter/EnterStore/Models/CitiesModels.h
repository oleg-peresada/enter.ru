#pragma once

using namespace Platform;

namespace EnterStore
{
	namespace Models
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class CitiesModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property int ParentId
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

			property bool IsMain
			{
				bool get();
			}

			property bool HasShop
			{
				bool get();
			}

			property bool HasDelivery
			{
				bool get();
			}

			property bool HasSubway
			{
				bool get();
			}

			property double CoordLong
			{
				double get();
			}

			property double CoordLat
			{
				double get();
			}

			property bool TkAvailable
			{
				bool get();
			}
		internal:
			CitiesModels(int id,
				int parent_id,
				String^ name,
				String^ token,
				bool is_main,
				bool has_shop,
				bool has_delivery,
				bool has_subway,
				double coordLong,
				double coordLat,
				bool tk_available);
		private:
			int source_id;
			int source_parentId;
			String^ source_name;
			String^ source_token;
			bool source_isMain;
			bool source_hasShop;
			bool source_hasDelivery;
			bool source_hasSubway;
			double source_coordLong;
			double source_coordLat;
			bool source_tkAvailable;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class AutoRegionModels sealed
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
		internal:
			AutoRegionModels(int id, String^ name);
		private:
			int m_id;
			String^ m_name;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class AutoCityModels sealed
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

			property AutoRegionModels^ Region
			{
				AutoRegionModels^ get();
			}
		internal:
			AutoCityModels(int id, String^ name, AutoRegionModels^ region);
		private:
			int m_id;
			String^ m_name;
			AutoRegionModels^ m_region;
		};
	}
}