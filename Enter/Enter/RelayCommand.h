#pragma once

namespace Enter
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class RelayCommand sealed : [Windows::Foundation::Metadata::Default]Windows::UI::Xaml::Input::ICommand
	{
	public:
		virtual event Windows::Foundation::EventHandler<Platform::Object^>^ CanExecuteChanged;
		virtual void Execute(Platform::Object^ parameter);
		virtual bool CanExecute(Platform::Object^ parameter);
		virtual ~RelayCommand();
	internal:
		RelayCommand(std::function < void(Platform::Object^)> executeCallback, std::function < bool(Platform::Object^)> canExecuteCallback);
		void RaiseCanExecuteChanged();
	private:
		std::function < void(Platform::Object^) > i_executeCallback;
		std::function < bool(Platform::Object^) > i_canExecuteCallback;
	};
}