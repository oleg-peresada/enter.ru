#include "pch.h"
#include "LoadStateEventArgs.h"

using namespace Enter;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

LoadStateEventArgs::LoadStateEventArgs(Object^ navigationParameter, IMap<String^, Object^>^ pageState)
{
	_navigationParameter = navigationParameter;
	_pageState = pageState;
}

Object^ LoadStateEventArgs::NavigationParameter::get()
{
	return _navigationParameter;
}

IMap<String^, Object^>^ LoadStateEventArgs::PageState::get()
{
	return _pageState;
}

SaveStateEventArgs::SaveStateEventArgs(IMap<String^, Object^>^ pageState)
{
	_pageState = pageState;
}

IMap<String^, Object^>^ SaveStateEventArgs::PageState::get()
{
	return _pageState;
}

