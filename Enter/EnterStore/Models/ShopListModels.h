#pragma once

using namespace Platform;
using namespace Windows::Foundation::Collections;

namespace EnterStore
{
	namespace Models
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ImagesModels sealed
		{
		public:
			property String^ Source
			{
				String^ get();
			}

			property String^ Position
			{
				String^ get();
			}
		internal:
			ImagesModels(String^ source, String^ position);
		private:
			String^ im_source;
			String^ im_position;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class GeoShopModels sealed
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

			property String^ CoordLong
			{
				String^ get();
			}

			property String^ CoordLat
			{
				String^ get();
			}
		internal:
			GeoShopModels(int id, String^ name, String^ coordLong, String^ coordLat);
		private:
			int source_id;
			String^ source_name;
			String^ source_coordLong;
			String^ source_coordLat;
		};

		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ShopListModels sealed
		{
		public:
			property int Id
			{
				int get();
			}

			property String^ Token
			{
				String^ get();
			}

			property String^ Name
			{
				String^ get();
			}

			property String^ Description
			{
				String^ get();
			}

			property String^ MediaImage
			{
				String^ get();
			}

			property String^ WorkingTime
			{
				String^ get();
			}

			property bool IsReconstruction
			{
				bool get();
			}

			property String^ Phone
			{
				String^ get();
			}

			property String^ Address
			{
				String^ get();
			}

			property float CoordLong
			{
				float get();
			}

			property float CoordLat
			{
				float get();
			}

			property String^ WayWalk
			{
				String^ get();
			}

			property String^ WayAuto
			{
				String^ get();
			}

			property IVector<ImagesModels^>^ Images
			{
				IVector<ImagesModels^>^ get();
				void set(IVector<ImagesModels^>^ val);
			}

			property GeoShopModels^ Geo
			{
				GeoShopModels^ get();
				void set(GeoShopModels^ val);
			}
		internal:
			ShopListModels(int id,
				String^ token,
				String^ name,
				String^ description,
				String^ mediaImage,
				String^ workingTime,
				bool is_reconstruction,
				String^ phone,
				String^ address,
				float coordLong,
				float coordLat,
				String^ wayWalk,
				String^ wayAuto);
		private:
			int shop_id;
			String^ shop_token;
			String^ shop_name;
			String^ shop_description;
			String^ shop_mediaImage;
			String^ shop_WorkingTime;
			bool shop_Reconstruction;
			String^ shop_phone;
			String^ shop_address;
			float shop_CoordLong;
			float shop_CoordLat;
			String^ shop_wayWalk;
			String^ shop_WayAuto;
			IVector<ImagesModels^>^ shop_Images;
			GeoShopModels^ source_geo;
		};
	}
}