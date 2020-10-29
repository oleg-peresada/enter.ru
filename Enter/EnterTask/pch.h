//
// pch.h
// Header for standard system include files.
//

#pragma once

#include <collection.h>
#include <ppltasks.h>
#include <utility>
#include <vector>

#include "TileNotificationTask.h"
using namespace Windows::UI::Notifications;

template<typename T>
struct TaskException
{
public:
	TaskException() : m_platformException(nullptr)
	{
	}

	TaskException(std::function<void(Object^)> platformException) : m_platformException(platformException)
	{
	}

	concurrency::task<T> operator() (concurrency::task<T> antecedent) const
	{
		T result;
		try
		{
			result = antecedent.get();
		}
		catch (const concurrency::task_canceled&)
		{
		}
		catch (const std::exception&)
		{
		}
		catch (Platform::Exception^ ex)
		{
			if (m_platformException != nullptr)
			{
				m_platformException(ex->Message);
			}
		}

		return antecedent;
	}
private:
	std::function<void(Object^)> m_platformException;
};

concurrency::task<void> TaskException<void>::operator() (concurrency::task<void> antecedent) const
{
	try
	{
		antecedent.get();
	}
	catch (const concurrency::task_canceled&)
	{
	}
	catch (const std::exception&)
	{
	}
	catch (Platform::Exception^ ex)
	{
	}

	return antecedent;
}