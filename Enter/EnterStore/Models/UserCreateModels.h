#pragma once

using namespace Platform;

namespace EnterStore
{
	namespace Models
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class UserCreateModels sealed
		{
		public:
			property String^ Id
			{
				String^ get();
			}

			property String^ Password
			{
				String^ get();
			}

			property String^ Token
			{
				String^ get();
			}
		internal:
			UserCreateModels(String^ id, String^ password, String^ token);
		private:
			String^ source_id;
			String^ source_password;
			String^ source_token;
		};
	}
}