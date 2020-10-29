#pragma once

#include <string>

using namespace Platform;

namespace Enter
{
	namespace DataModel
	{
		namespace Storage
		{
			[Windows::Foundation::Metadata::WebHostHidden]
			public ref class AutorizationStorage sealed
			{
			public:
				AutorizationStorage();
				void CreateSaveToken(String^ token);

				property static AutorizationStorage^ Current
				{
					AutorizationStorage^ get();
				}

				property String^ Token
				{
					String^ get();
					void set(String^ val);
				}
			};

			[Windows::Foundation::Metadata::WebHostHidden]
			public ref class CityTokenStorage sealed
			{
			public:
				CityTokenStorage();
				CityTokenStorage(int id, int parentId, String^ name);
				void Save();
				CityTokenStorage^ Open();

				property static CityTokenStorage^ Current
				{
					CityTokenStorage^ get();
				}

				property int Id
				{
					int get();
					void set(int val);
				}

				property int ParentId
				{
					int get();
					void set(int val);
				}

				property String^ Name
				{
					String^ get();
					void set(String^ val);
				}

				property bool IsCityToken
				{
					bool get();
				}
			private:
				int source_id;
				int source_parentId;
				String^ source_name;
			};

			[Windows::Foundation::Metadata::WebHostHidden]
			public ref class Customizations sealed
			{
			public:
				Customizations();
				void Save();

				property static Customizations^ Current
				{
					Customizations^ get();
				}

				property String^ ResourceProductTemplate
				{
					String^ get();
					void set(String^ value);
				}

				property int CurrentStore
				{
					int get();
					void set(int value);
				}
			private:
				Customizations(String^ resourceProductTemplate, int currentSource);
				String^ source_resourceProductTemplate;
				int source_currentStore;
				static Customizations^ Open();
			};
		}
	}
}