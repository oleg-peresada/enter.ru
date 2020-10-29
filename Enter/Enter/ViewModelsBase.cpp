#include "pch.h"
#include "ViewModelsBase.h"

using namespace Enter;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::System;
using namespace Windows::UI::Core;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::Graphics::Display;

ViewModelsBase::ViewModelsBase(Page^ page, RelayCommand^ goBack, RelayCommand^ goForward)
	: view_Page(page), view_goBackCommand(goBack), view_goForwardCommand(goForward), 
	_isActive(false), _rootVisibility(Visibility::Collapsed)
{
	_loadedEventToken = page->Loaded += ref new RoutedEventHandler(this, &ViewModelsBase::OnLoaded);
	_unloadedEventToken = page->Unloaded += ref new RoutedEventHandler(this, &ViewModelsBase::OnUnloaded);
	_sizeChangedPageToken = page->SizeChanged += ref new SizeChangedEventHandler(this, &ViewModelsBase::OnSizeChanged);
}

Page^ ViewModelsBase::ViewPage::get()
{
	return view_Page;
}

Frame^ ViewModelsBase::ViewFrame::get()
{
	return view_Page->Frame;
}

void ViewModelsBase::OnPropertyChanged(String^ propertyName)
{
	PropertyChanged(this, ref new PropertyChangedEventArgs(propertyName));
}

bool ViewModelsBase::CanGoBack()
{
	return (ViewFrame != nullptr && ViewFrame->CanGoBack);
}

void ViewModelsBase::GoBack()
{
	if (this->CanGoBack())
	{
		ViewFrame->GoBack();
	}
}

bool ViewModelsBase::CanGoForward()
{
	return (ViewFrame != nullptr && ViewFrame->CanGoForward);
}

void ViewModelsBase::GoForward()
{
	if (this->CanGoForward())
	{
		ViewFrame->GoForward();
	}
}

RelayCommand^ ViewModelsBase::GoBackCommand::get()
{
	if (view_goBackCommand == nullptr)
	{
		view_goBackCommand = ref new RelayCommand([&](Object^) -> void
		{
			GoBack();
		}, [&](Object^) -> bool
		{
			return CanGoBack();
		});
	}

	return view_goBackCommand;
}

RelayCommand^ ViewModelsBase::GoForwardCommand::get()
{
	if (view_goForwardCommand == nullptr)
	{
		view_goForwardCommand = ref new RelayCommand([&](Object^) -> void
		{
			GoForward();
		}, [&](Object^) -> bool
		{
			return CanGoForward();
		});
	}

	return view_goForwardCommand;
}

double ViewModelsBase::WidthScreen::get()
{
	return _widthScreen;
}

void ViewModelsBase::WidthScreen::set(double sizeValue)
{
	_widthScreen = sizeValue;
	OnPropertyChanged("WidthScreen");
}

bool ViewModelsBase::IsActive::get()
{
	return _isActive;
}

void ViewModelsBase::IsActive::set(bool value)
{
	_isActive = value;
	OnPropertyChanged("IsActive");
}

Visibility ViewModelsBase::RootVisibility::get()
{
	return _rootVisibility;
}

void ViewModelsBase::RootVisibility::set(Visibility value)
{
	_rootVisibility = value;
	OnPropertyChanged("RootVisibility");
}

void ViewModelsBase::OnSizeChanged(Object ^sender, SizeChangedEventArgs ^e)
{
	WidthScreen = e->NewSize.Width;
}

void ViewModelsBase::OnLoaded(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Навигация с помощью мыши и клавиатуры применяется, только если страница занимает все окно
	if (view_Page->ActualHeight == Window::Current->Bounds.Height &&
		view_Page->ActualWidth == Window::Current->Bounds.Width)
	{
		// Непосредственное прослушивание окна, поэтому фокус не требуется
		_acceleratorKeyEventToken = Window::Current->CoreWindow->Dispatcher->AcceleratorKeyActivated +=
			ref new TypedEventHandler<CoreDispatcher^, AcceleratorKeyEventArgs^>(this,
			&ViewModelsBase::CoreDispatcher_AcceleratorKeyActivated);

		_pointerPressedEventToken = Window::Current->CoreWindow->PointerPressed +=
			ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this,
			&ViewModelsBase::CoreWindow_PointerPressed);

		_navigationShortcutsRegistered = true;
	}
}

void ViewModelsBase::OnUnloaded(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (_navigationShortcutsRegistered)
	{
		Window::Current->CoreWindow->Dispatcher->AcceleratorKeyActivated -= _acceleratorKeyEventToken;
		Window::Current->CoreWindow->PointerPressed -= _pointerPressedEventToken;
		_navigationShortcutsRegistered = false;
	}

	// Удаление обработчика и освобождение ссылки на страницу
	view_Page->Loaded -= _loadedEventToken;
	view_Page->Unloaded -= _unloadedEventToken;
	view_Page->SizeChanged -= _sizeChangedPageToken;

	delete view_goBackCommand;
	delete view_goForwardCommand;
	view_Page = nullptr;
}

void ViewModelsBase::CoreDispatcher_AcceleratorKeyActivated(CoreDispatcher^ sender,
	AcceleratorKeyEventArgs^ e)
{
	sender; // Неиспользуемый параметр
	auto virtualKey = e->VirtualKey;

	// Дальнейшее изучение следует выполнять, только если нажата клавиша со стрелкой влево или вправо либо назначенная клавиша "Назад" или
	// нажаты
	if ((e->EventType == CoreAcceleratorKeyEventType::SystemKeyDown ||
		e->EventType == CoreAcceleratorKeyEventType::KeyDown) &&
		(virtualKey == VirtualKey::Left || virtualKey == VirtualKey::Right ||
		virtualKey == VirtualKey::GoBack || virtualKey == VirtualKey::GoForward))
	{
		auto coreWindow = Window::Current->CoreWindow;
		auto downState = Windows::UI::Core::CoreVirtualKeyStates::Down;
		bool menuKey = (coreWindow->GetKeyState(VirtualKey::Menu) & downState) == downState;
		bool controlKey = (coreWindow->GetKeyState(VirtualKey::Control) & downState) == downState;
		bool shiftKey = (coreWindow->GetKeyState(VirtualKey::Shift) & downState) == downState;
		bool noModifiers = !menuKey && !controlKey && !shiftKey;
		bool onlyAlt = menuKey && !controlKey && !shiftKey;

		if ((virtualKey == VirtualKey::GoBack && noModifiers) ||
			(virtualKey == VirtualKey::Left && onlyAlt))
		{
			// Переход назад при нажатии клавиши "Назад" или сочетания клавиш ALT+СТРЕЛКА ВЛЕВО
			e->Handled = true;
			GoBackCommand->Execute(this);
		}
		else if ((virtualKey == VirtualKey::GoForward && noModifiers) ||
			(virtualKey == VirtualKey::Right && onlyAlt))
		{
			// Переход вперед при нажатии клавиши "Вперед" или сочетания клавиш ALT+СТРЕЛКА ВПРАВО
			e->Handled = true;
			GoForwardCommand->Execute(this);
		}
	}
}

void ViewModelsBase::CoreWindow_PointerPressed(CoreWindow^ sender, PointerEventArgs^ e)
{
	auto properties = e->CurrentPoint->Properties;

	// Пропуск сочетаний кнопок, включающих левую, правую и среднюю кнопки
	if (properties->IsLeftButtonPressed ||
		properties->IsRightButtonPressed ||
		properties->IsMiddleButtonPressed)
	{
		return;
	}

	// Если нажата кнопка "Назад" или "Вперед" (но не обе), выполняется соответствующий переход
	bool backPressed = properties->IsXButton1Pressed;
	bool forwardPressed = properties->IsXButton2Pressed;
	if (backPressed ^ forwardPressed)
	{
		e->Handled = true;
		if (backPressed)
		{
			if (GoBackCommand->CanExecute(this))
			{
				GoBackCommand->Execute(this);
			}
		}
		else
		{
			if (GoForwardCommand->CanExecute(this))
			{
				GoForwardCommand->Execute(this);
			}
		}
	}
}

void ViewModelsBase::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	LoadState(this, state);
}

void ViewModelsBase::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
	SaveState(this, state);
}

void ViewModelsBase::OnNavigatedTo(NavigationEventArgs^ e)
{
	auto frameState = SuspensionManager::SessionStateForFrame(view_Page->Frame);
	_pageKey = "Page-" + view_Page->Frame->BackStackDepth;

	if (e->NavigationMode == NavigationMode::New)
	{
		// Очистка существующего состояния для перехода вперед при добавлении новой страницы в
		// стек навигации
		auto nextPageKey = _pageKey;
		int nextPageIndex = view_Page->Frame->BackStackDepth;
		while (frameState->HasKey(nextPageKey))
		{
			frameState->Remove(nextPageKey);
			nextPageIndex++;
			nextPageKey = "Page-" + nextPageIndex;
		}

		// Передача параметра навигации на новую страницу
		OnLoadState(e, ref new LoadStateEventArgs(e->Parameter, nullptr));
	}
	else
	{
		// Передача на страницу параметра навигации и сохраненного состояния страницы с использованием
		// той же стратегии загрузки приостановленного состояния и повторного создания страниц, удаленных
		// из кэша
		OnLoadState(e, ref new LoadStateEventArgs(e->Parameter, safe_cast<IMap<String^, Object^>^>(frameState->Lookup(_pageKey))));
	}
}

void ViewModelsBase::OnNavigatedFrom(NavigationEventArgs^ e)
{
	auto frameState = SuspensionManager::SessionStateForFrame(view_Page->Frame);
	auto pageState = ref new Map<String^, Object^>();
	OnSaveState(e, ref new SaveStateEventArgs(pageState));
	frameState->Insert(_pageKey, pageState);
}

void ViewModelsBase::SearchRequest(SearchBox^ sender, SearchBoxSuggestionsRequestedEventArgs^ args)
{
	using namespace Windows::Storage::Streams;
	using namespace EnterStore::Commands;
	using namespace EnterStore::Models;
	using namespace Enter::DataModel::Storage;
	
	if (args == nullptr) return;

	auto queryText = args->QueryText;
	if (queryText != nullptr && queryText->Length() > 1)
	{
		auto request = args->Request;
		auto defferal = request->GetDeferral();

		auto searchCollection = request->SearchSuggestionCollection;
		searchCollection->AppendSearchSeparator("Товары");

		int geo_id = CityTokenStorage::Current->Id != 0 ? CityTokenStorage::Current->Id : 14974;
		auto searchCommand = ref new SearchCommands(queryText, geo_id, 0, SearchType::Product);
		auto searchOperation = searchCommand->SearchAsync();

		concurrency::create_task(searchOperation).then([=](IVector<ProductCardModels^>^ vectorProduct)
		{
			return vectorProduct;
		}).then([=](IVector<ProductCardModels^>^ vectElements)
		{
			try
			{
				if (vectElements != nullptr && vectElements->Size > 0)
				{
					unsigned int size = vectElements->Size;
					for (unsigned int index = 0; index < size; index++)
					{
						String^ uriString = "http://fs03.enter.ru/1/1/" + "163/" + vectElements->GetAt(index)->MediaImage;
						auto streamReference = RandomAccessStreamReference::CreateFromUri(ref new Uri(uriString));

						searchCollection->AppendResultSuggestion(vectElements->GetAt(index)->Name, "", vectElements->GetAt(index)->Id.ToString(), streamReference, "");
					}

					Finally f([&]
					{
						defferal->Complete();
					});
				}
			}
			catch (std::exception&)
			{
			}
			catch (Exception^)
			{
			}
		}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
	}
}

void ViewModelsBase::SearchSubmitted(SearchBox^ sender, SearchBoxQuerySubmittedEventArgs^ args)
{
	Helpers::SearchSubmitted(sender, args);
}

void ViewModelsBase::SearchSuggestionChosen(SearchBox^ sender, SearchBoxResultSuggestionChosenEventArgs^ args)
{
	Helpers::SearchSuggestionChosen(sender, args);
}

void ViewModelsBase::OnActiveState(bool isTransition)
{
	if (isTransition)
	{
		IsActive = true;
		RootVisibility = Visibility::Collapsed;
	}
	else
	{
		IsActive = false;
		RootVisibility = Visibility::Visible;
	}
}