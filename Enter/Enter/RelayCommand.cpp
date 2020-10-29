#include "pch.h"
#include "RelayCommand.h"

using namespace Enter;
using namespace Platform;

RelayCommand::RelayCommand(std::function < void(Object^)> executeCallback, std::function < bool(Object^)> canExecuteCallback)
	: i_executeCallback(executeCallback), i_canExecuteCallback(canExecuteCallback)
{
}

RelayCommand::~RelayCommand()
{
	i_executeCallback = nullptr;
	i_canExecuteCallback = nullptr;
}

void RelayCommand::Execute(Object^ parameter)
{
	(i_executeCallback) (parameter);
}

bool RelayCommand::CanExecute(Object^ parameter)
{
	return (i_canExecuteCallback) (parameter);
}

void RelayCommand::RaiseCanExecuteChanged()
{
	CanExecuteChanged(this, nullptr);
}
