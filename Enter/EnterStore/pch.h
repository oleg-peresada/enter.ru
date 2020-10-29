//
// pch.h
// Header for standard system include files.
//

#pragma once

#include <collection.h>
#include <ppltasks.h>
#include <sstream>
#include <string>

#include "Helpers.h"
#include "HttpCommand.h"

inline Platform::String^ HtmlSymbol(String^ value)
{
	return Windows::Data::Html::HtmlUtilities::ConvertToText(value);
}