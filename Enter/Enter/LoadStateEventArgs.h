#pragma once

namespace Enter
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class LoadStateEventArgs sealed
	{
	public:
		property Platform::Object^ NavigationParameter
		{
			Platform::Object^ get();
		}
		property Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ PageState
		{
			Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ get();
		}
	internal:
		LoadStateEventArgs(Platform::Object^ navigationParameter, Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ pageState);
	private:
		Platform::Object^ _navigationParameter;
		Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ _pageState;
	};


	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class SaveStateEventArgs sealed
	{
	public:
		property Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ PageState
		{
			Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ get();
		}
	internal:
		SaveStateEventArgs(Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ pageState);
	private:
		Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ _pageState;
	};

	public delegate void LoadStateEventHandler(Platform::Object^ sender, LoadStateEventArgs^ e);
	public delegate void SaveStateEventHandler(Platform::Object^ sender, SaveStateEventArgs^ e);
}