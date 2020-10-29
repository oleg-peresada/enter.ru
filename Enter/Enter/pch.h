//
// pch.h
// Заголовок стандартных системных включаемых файлов.
//

#pragma once

#include <collection.h>
#include <ppltasks.h>
#include <iostream>
#include <string>

#include "App.xaml.h"
#include "RelayCommand.h"
#include "SuspensionManager.h"
#include "LoadStateEventArgs.h"
#include "ViewModelsBase.h"
#include "Helpers.h"

#include "DataModel\HubDataModel.h"
#include "DataModel\GroupCategorySource.h"
#include "DataModel\BasketProductSerialize.h"

#include "Converters\MediaImageConverter.h"
#include "Converters\TextSourceConvert.h"
#include "Converters\ProductValueConverter.h"
#include "Converters\VisibilityNullValueConverter.h"
#include "Converters\BuyableConverter.h"
#include "Converters\PriceConverter.h"
#include "Converters\TrackerStatusConverter.h"

#include "Template\VariableGridView.h"
#include "Template\CategoryTemplateSelector.h"

#include "View\CategoryTreeView.xaml.h"

using namespace Platform;

inline double StringToNumber(Platform::String^ m_string)
{
	std::string conversation(Platform::begin(m_string), Platform::end(m_string));
	double result = 0.0;
	std::istringstream(conversation) >> result;
	return result;
}

inline Windows::Foundation::DateTime StringToDateTime(Platform::String^ m_string)
{
	std::string strDate(begin(m_string), end(m_string));
	std::istringstream dateStream(strDate);

	auto calendar = ref new Windows::Globalization::Calendar();

	int year = 0;
	dateStream >> year;
	calendar->Year = year;
	dateStream.ignore(1, '-');

	int month = 0;
	dateStream >> month;
	calendar->Month = month;
	dateStream.ignore(1, '-');

	int day = 0;
	dateStream >> day;
	calendar->Day = day;

	return calendar->GetDateTime();
}