#pragma once

namespace Enter
{
	class SuspensionManager sealed
	{
	public:
		static void RegisterFrame(Windows::UI::Xaml::Controls::Frame^ frame, Platform::String^ sessionStateKey);
		static void UnregisterFrame(Windows::UI::Xaml::Controls::Frame^ frame);
		static concurrency::task<void> SaveAsync();
		static concurrency::task<void> RestoreAsync();
		static Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ SessionState();
		static Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ SessionStateForFrame(Windows::UI::Xaml::Controls::Frame^ frame);

	private:
		static void RestoreFrameNavigationState(Windows::UI::Xaml::Controls::Frame^ frame);
		static void SaveFrameNavigationState(Windows::UI::Xaml::Controls::Frame^ frame);

		static Platform::Collections::Map<Platform::String^, Platform::Object^>^ _sessionState;
		static const wchar_t* sessionStateFilename;

		static std::vector<Platform::WeakReference> _registeredFrames;
		static Windows::UI::Xaml::DependencyProperty^ FrameSessionStateKeyProperty;
		static Windows::UI::Xaml::DependencyProperty^ FrameSessionStateProperty;
	};
}