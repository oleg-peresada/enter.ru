#include "pch.h"
#include "OrderViewModels.h"

using namespace Enter;
using namespace Enter::ViewModels;
using namespace Enter::DataModel;
using namespace Enter::DataModel::Storage;
using namespace Enter::Controls;
using namespace Enter::View::Settings;
using namespace EnterStore::Commands;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Media::Animation;

OrderViewModels::OrderViewModels(Page^ page)
	: ViewModelsBase(page)
{
}

OrderViewModels::~OrderViewModels()
{

}

void OrderViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	Helpers::LogPage("MainPageView/OrderView");

	this->OnActiveState(true);
	ListProductVisibility = Visibility::Collapsed;
	AddressDeliveryVisibility = Visibility::Collapsed;
	PersonalDataVisibility = Visibility::Collapsed;

	auto model = dynamic_cast<IObservableVector<BasketProductDataModel^>^>(args->Parameter);
	if (model != nullptr)
	{
		ProductBasket = ref new Vector<BasketProductDataModel^>(begin(model), end(model));
		auto vectProduct = ref new Vector<ProductListOrder^>();
		for (const auto &item : model)
		{
			vectProduct->Append(ref new ProductListOrder(item->Id, item->Count));
		}

		auto tokenId = CityTokenStorage::Current->Id;
		auto calc = ref new OrderCalcCommands(tokenId, vectProduct);
		concurrency::create_task(calc->OrderCalcAsync()).then([this](Object^ content)
		{
			auto modelContent = dynamic_cast<OrderCalcModels^>(content);
			if (modelContent != nullptr)
			{
				if (modelContent != nullptr && modelContent->Mode->Size != 0)
				{
					OrderCalc = modelContent;
					this->OnActiveState(false);
				}
			}

			auto modelError = dynamic_cast<String^>(content);
			if (modelError != nullptr)
			{
				auto messageBox = ref new Windows::UI::Popups::MessageDialog(modelError);
				messageBox->ShowAsync();
				this->OnActiveState(false);
			}
		}).then([this](void)
		{
			auto token = AutorizationStorage::Current->Token;
			auto userCommand = ref new UserContentCommands(token);
			auto operUserCommand = userCommand->CurrentUserAsync();
			concurrency::create_task(operUserCommand).then([this](UserContentModels^ user)
			{
				if (user != nullptr)
				{
					FirstName = user->FirstName != nullptr ? user->FirstName : "";
					LastName = user->LastName != nullptr ? user->LastName : "";
					Email = user->Email != nullptr ? user->Email : "";
					Phone = user->MobilePhone != nullptr ? user->MobilePhone : "";
				}
			}).then(TaskException<void>());

		}).then(TaskException<void>());
	}
}

void OrderViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
}

void OrderViewModels::OnAmountSum()
{
	double sum = 0.0;
	double deliverySum = 0.0;
	for (const auto &productItem : ProductDelivery)
	{
		sum += (productItem->Item->Price * productItem->Item->Count);

		if (productItem->DeliveryPrice != 0.0)
		{
			deliverySum = productItem->DeliveryPrice;
		}
	}

	GlobalPrice = sum + deliverySum;
	PriceDelivery = deliverySum;
}

void OrderViewModels::CommandUpdate(bool is_pickup, bool is_pickupNew, bool is_standart)
{
	IsPickup = is_pickup;
	IsPickupNew = is_pickupNew;
	IsStandart = is_standart;
}

void OrderViewModels::OnDeliveryProductLoaded(ProductGroupDelivery valueType)
{
	if (valueType == ProductGroupDelivery::Standart)
	{
		this->CommandUpdate(false, false, true);
	}
	else if (valueType == ProductGroupDelivery::Pickup)
	{
		this->CommandUpdate(true, false, false);
	}
	else if (valueType == ProductGroupDelivery::PickupUp)
	{
		this->CommandUpdate(false, true, false);
	}

	auto element = this->ProductBasket;
	auto vectProduct = ref new Vector<BasketProductDataModel^>(begin(element), end(element));
	auto deliveryElemenet = ref new DeliveryGroupProductDataModel(vectProduct, OrderCalc);
	concurrency::create_task(deliveryElemenet->ToProductDeliveryAsync(valueType)).then([this, valueType](IObservableVector<ProductDeliveryDataModel^>^ resultDeliveryModel)
	{
		ProductDelivery = resultDeliveryModel;

		this->OnAmountSum();
		ListProductVisibility = Visibility::Visible;
		AddressDeliveryVisibility = valueType == ProductGroupDelivery::Standart ? Visibility::Visible : Visibility::Collapsed;
		PersonalDataVisibility = Visibility::Visible;
	}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
}

void OrderViewModels::OnPickShopItemClick(Object ^sender, Object ^Item)
{
	auto pickControl = dynamic_cast<PickShopControl^>(sender);
	auto shopItem = dynamic_cast<OrderShopListModels^>(Item);

	if (pickControl != nullptr && shopItem != nullptr)
	{
		auto productItem = dynamic_cast<ProductDeliveryDataModel^>(pickControl->Tag);
		if (productItem != nullptr)
		{
			unsigned int size = ProductDelivery->Size;
			for (unsigned int i = 0; i < size; i++)
			{
				auto element = ProductDelivery->GetAt(i);
				if (element->Item->Id == productItem->Item->Id)
				{
					auto productElement = ref new ProductDeliveryDataModel(element->Shop, element->Interval,
						element->DeliveryPrice, element->Id, element->Item, shopItem);

					productElement->DateTimeDelivery = element->DateTimeDelivery;
					productElement->CurrentDateTime = element->CurrentDateTime;
					productElement->CurrentInterval = element->CurrentInterval;

					ProductDelivery->SetAt(i, productElement);
					return;
				}
			}
		}
	}
}

void OrderViewModels::OnPickShop(Object^ parameter)
{
	auto rect = Window::Current->Bounds;
	auto width = rect.Width * 0.80;
	auto height = rect.Height * 0.75;

	auto pickControl = ref new PickShopControl();
	pickControl->Width = width;
	pickControl->Height = height;

	int w = (rect.Width - width) / 2;
	int h = (rect.Height - height) / 2;

	pickControl->Margin = Thickness(w, h, w, h);
	pickControl->PickShopItemClick += ref new PickShopItemClickHandler(this, &OrderViewModels::OnPickShopItemClick);
	pickControl->Tag = parameter;

	auto popup = ref new Popup();
	popup->ChildTransitions = ref new TransitionCollection();
	popup->ChildTransitions->Append(ref new PopupThemeTransition());
	popup->Child = pickControl;
	popup->IsLightDismissEnabled = true;
	popup->IsOpen = true;
}

bool OrderViewModels::OnTextChangedContent()
{
	Windows::UI::Popups::MessageDialog^ message = nullptr;

	if (this->FirstName == nullptr)
	{
		message = ref new Windows::UI::Popups::MessageDialog("Введите имя");
		message->ShowAsync();
		return false;
	}

	if (this->LastName == nullptr)
	{
		message = ref new Windows::UI::Popups::MessageDialog("Введите фамилию");
		message->ShowAsync();
		return false;
	}

	if (this->Phone == nullptr)
	{
		message = ref new Windows::UI::Popups::MessageDialog("Введите телефон");
		message->ShowAsync();
		return false;
	}

	if (this->Email == nullptr)
	{
		message = ref new Windows::UI::Popups::MessageDialog("Введите email");
		message->ShowAsync();
		return false;
	}

	return true;
}

void OrderViewModels::OnPopupCities()
{
	auto rectWindow = Window::Current->Bounds;
	auto width = rectWindow.Width;
	auto height = rectWindow.Height;

	auto citiesControl = ref new CitiesMenuControl();
	citiesControl->Width = width;
	citiesControl->Height = height;
	citiesControl->Tag = height * 0.90;

	auto popupCities = ref new Popup();

	popupCities->ChildTransitions = ref new TransitionCollection();
	popupCities->ChildTransitions->Append(ref new PopupThemeTransition());
	popupCities->Child = citiesControl;
	popupCities->IsLightDismissEnabled = false;
	popupCities->IsOpen = true;
}

void OrderViewModels::OnOrderCompleted(IVector<OrderDeliveryResult^>^ valueOrder)
{
	auto rectWindow = Window::Current->Bounds;
	auto width = rectWindow.Width - 200;
	auto height = rectWindow.Height - 250;

	auto orderControl = ref new OrderCompletedControl();
	orderControl->Width = width;
	orderControl->Height = height;
	orderControl->Margin = Thickness(100, 125, 100, 125);
	orderControl->Tag = valueOrder;

	auto popupCompleted = ref new Popup();

	popupCompleted->ChildTransitions = ref new TransitionCollection();
	popupCompleted->ChildTransitions->Append(ref new PopupThemeTransition());
	popupCompleted->Child = orderControl;
	popupCompleted->IsLightDismissEnabled = false;
	popupCompleted->IsOpen = true;
}

bool OrderViewModels::IsProductBasket(int id)
{
	unsigned int size = ProductBasket->Size;
	for (unsigned int i = 0; i < size; i++)
	{
		auto element = ProductBasket->GetAt(i);
		if (element != nullptr && element->Id == id)
		{
			return true;
		}
	}

	return false;
}

void OrderViewModels::OnRemoveToBasketProduct()
{
	if (ProductBasket == nullptr && ProductBasket->Size == 0) return;

	try
	{
		auto vect = ref new Vector<BasketProductDataModel^>();
		auto serialize = std::shared_ptr<BasketProductSerialize>();
		auto operationOpen = (*serialize).Open();
		concurrency::create_task(operationOpen).then([this, serialize, vect](IVector<BasketProductDataModel^>^ result)
		{
			for (const auto &item : result)
			{
				if (!IsProductBasket(item->Id))
				{
					vect->Append(item);
				}
			}

			(*serialize).Save(vect);
		}).then(TaskException<void>());
	}
	catch (Exception^) { }
}

void OrderViewModels::OnOrderCommand()
{
	//Если не выбран способ доставки
	if (ProductDelivery == nullptr) return;

	//Выбран ли город
	if (!CityTokenStorage::Current->IsCityToken)
	{
		this->OnPopupCities();
		return;
	}

	//Проверка заполнения личных данных
	if (!this->OnTextChangedContent()) return;

	auto geo_id = CityTokenStorage::Current->Id != 0 ? CityTokenStorage::Current->Id : 14974;
	auto token = AutorizationStorage::Current->Token;
	if (token == nullptr && token->Length() == 0) //Проверка авторизации
	{
		auto settings = ref new AutorizationFlyout();
		settings->Width = 500;
		settings->ShowIndependent();
		return;
	}
	else
	{
		std::vector<concurrency::task<OrderDeliveryResult^>> orderTasks;
		auto commandOrder = ref new OrderCommands(token);
		auto orderVect = ref new Vector<OrderQueryField^>();

		auto v = ProductDelivery;
		for (const auto &selectItem : ProductDelivery)
		{

			String^ deliveryDate = selectItem->CurrentDateTime != nullptr ? selectItem->CurrentDateTime : "";
			auto contentOrder = ref new OrderQueryField(1,
				geo_id, 1, 1,
				selectItem->Id,
				deliveryDate,
				selectItem->CurrentInterval->Id,
				selectItem->CurrentShop != nullptr ? selectItem->CurrentShop->Id : -1,
				this->FirstName,
				this->LastName,
				this->Phone,
				this->Email,
				this->AddressStreet,
				this->AddressBuilding,
				this->AddressNumber,
				this->AddressFloor,
				this->AddressApartment);

			auto itemProduct = ref new OrderQueryProduct(selectItem->Item->Id, selectItem->Item->Count);
			contentOrder->Product = itemProduct;

			orderVect->Append(contentOrder);
		}
		
		auto operationOrder = commandOrder->OrderAsync(orderVect);
		concurrency::create_task(operationOrder).then([this](IVector<OrderDeliveryResult^>^ contentResult)
		{
			this->OnOrderCompleted(contentResult);
			this->OnRemoveToBasketProduct();
			Helpers::LogEvent("OrderClient");

		}).then(TaskException<void>());
	}
}

#pragma region Property Binding

OrderCalcModels^ OrderViewModels::OrderCalc::get()
{
	return source_orderCalc;
}

void OrderViewModels::OrderCalc::set(OrderCalcModels^ val)
{
	source_orderCalc = val;
	OnPropertyChanged("OrderCalc");
}

IObservableVector<BasketProductDataModel^>^ OrderViewModels::ProductBasket::get()
{
	return source_ProductBasket;
}

void OrderViewModels::ProductBasket::set(IObservableVector<BasketProductDataModel^>^ val)
{
	source_ProductBasket = val;
	OnPropertyChanged("ProductBasket");
}

IObservableVector<ProductDeliveryDataModel^>^ OrderViewModels::ProductDelivery::get()
{
	return source_productDelivery;
}

void OrderViewModels::ProductDelivery::set(IObservableVector<ProductDeliveryDataModel^>^ val)
{
	source_productDelivery = val;
	OnPropertyChanged("ProductDelivery");
}

double OrderViewModels::PriceDelivery::get()
{
	return source_deliveryPrice;
}

void OrderViewModels::PriceDelivery::set(double val)
{
	source_deliveryPrice = val;
	OnPropertyChanged("PriceDelivery");
}

double OrderViewModels::GlobalPrice::get()
{
	return source_globalPrice;
}

void OrderViewModels::GlobalPrice::set(double val)
{
	source_globalPrice = val;
	OnPropertyChanged("GlobalPrice");
}

bool OrderViewModels::IsPickup::get()
{
	return source_isPickup;
}

void OrderViewModels::IsPickup::set(bool val)
{
	source_isPickup = val;
	OnPropertyChanged("IsPickup");
}

bool OrderViewModels::IsStandart::get()
{
	return source_isStandart;
}

void OrderViewModels::IsStandart::set(bool val)
{
	source_isStandart = val;
	OnPropertyChanged("IsStandart");
}

bool OrderViewModels::IsPickupNew::get()
{
	return source_isPickupNew;
}

void OrderViewModels::IsPickupNew::set(bool val)
{
	source_isPickupNew = val;
	OnPropertyChanged("IsPickupNew");
}

Visibility OrderViewModels::PersonalDataVisibility::get()
{
	return source_visibilityPersonalData;
}

void OrderViewModels::PersonalDataVisibility::set(Visibility val)
{
	source_visibilityPersonalData = val;
	OnPropertyChanged("PersonalDataVisibility");
}

Visibility OrderViewModels::ListProductVisibility::get()
{
	return source_visibilityListProduct;
}

void OrderViewModels::ListProductVisibility::set(Visibility val)
{
	source_visibilityListProduct = val;
	OnPropertyChanged("ListProductVisibility");
}

Visibility OrderViewModels::AddressDeliveryVisibility::get()
{
	return source_visibilityAddressDelivery;
}

void OrderViewModels::AddressDeliveryVisibility::set(Visibility val)
{
	source_visibilityAddressDelivery = val;
	OnPropertyChanged("AddressDeliveryVisibility");
}

String^ OrderViewModels::FirstName::get()
{
	return text_firstName;
}

void OrderViewModels::FirstName::set(String^ val)
{
	text_firstName = val;
	OnPropertyChanged("FirstName");
}

String^ OrderViewModels::LastName::get()
{
	return text_lastName;
}

void OrderViewModels::LastName::set(String^ val)
{
	text_lastName = val;
	OnPropertyChanged("LastName");
}

String^ OrderViewModels::Phone::get()
{
	return text_Phone;
}

void OrderViewModels::Phone::set(String^ val)
{
	text_Phone = val;
	OnPropertyChanged("Phone");
}

String^ OrderViewModels::Email::get()
{
	return text_Email;
}

void OrderViewModels::Email::set(String^ val)
{
	text_Email = val;
	OnPropertyChanged("Email");
}

String^ OrderViewModels::AddressStreet::get()
{
	return text_AddressStreet;
}

void OrderViewModels::AddressStreet::set(String^ val)
{
	text_AddressStreet = val;
	OnPropertyChanged("AddressStreet");
}

String^ OrderViewModels::AddressBuilding::get()
{
	return text_AddressBuilding;
}

void OrderViewModels::AddressBuilding::set(String^ val)
{
	text_AddressBuilding = val;
	OnPropertyChanged("AddressBuilding");
}

String^ OrderViewModels::AddressNumber::get()
{
	return text_AddressNumber;
}

void OrderViewModels::AddressNumber::set(String^ val)
{
	text_AddressNumber = val;
	OnPropertyChanged("AddressNumber");
}

String^ OrderViewModels::AddressFloor::get()
{
	return text_AddressFloor;
}

void OrderViewModels::AddressFloor::set(String^ val)
{
	text_AddressFloor = val;
	OnPropertyChanged("AddressFloor");
}

String^ OrderViewModels::AddressApartment::get()
{
	return text_AddressApartment;
}

void OrderViewModels::AddressApartment::set(String^ val)
{
	text_AddressApartment = val;
	OnPropertyChanged("AddressApartment");
}

#pragma endregion

#pragma region Property RelayCommand

RelayCommand^ OrderViewModels::IsPickupCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		if (IsPickup)
		{
			this->OnDeliveryProductLoaded(ProductGroupDelivery::Pickup);
		}
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ OrderViewModels::IsPickupNewCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		if (IsPickupNew)
		{
			this->OnDeliveryProductLoaded(ProductGroupDelivery::PickupUp);
		}
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ OrderViewModels::IsStandartCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		if (this->IsStandart)
		{
			this->OnDeliveryProductLoaded(ProductGroupDelivery::Standart);
		}
	}, [this](Object^)
	{
		return true;
	});
}

RelayCommand^ OrderViewModels::PickShopCommand::get()
{
	return ref new RelayCommand([this](Object^ parameter)
	{
		auto product = dynamic_cast<ProductDeliveryDataModel^>(parameter);
		if (product != nullptr)
		{
			this->OnPickShop(product);
		}

	}, [this](Object^ parameter)
	{
		return true;
	});
}

RelayCommand^ OrderViewModels::OrderEndCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		this->OnOrderCommand();
	}, [this](Object^)
	{
		return true;
	});
}

#pragma endregion