#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <collection.h>
#include <array>

#include "LoadStateEventArgs.h"
#include "ViewModelsBase.h"

#include "DataModel\BasketProductSerialize.h"
#include "DataModel\Storage\AutorizationStorage.h"

#include "Controls\PickShopControl.xaml.h"
#include "Controls\CitiesMenuControl.xaml.h"
#include "Controls\OrderCompletedControl.xaml.h"

#include "View\Settings\AutorizationFlyout.xaml.h"

using namespace Enter;
using namespace Enter::DataModel;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace Enter
{
	namespace ViewModels
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class OrderViewModels sealed : public ViewModelsBase
		{
		public:
			virtual ~OrderViewModels();
			property OrderCalcModels^ OrderCalc
			{
				OrderCalcModels^ get();
				void set(OrderCalcModels^ val);
			}

			property IObservableVector<BasketProductDataModel^>^ ProductBasket
			{
				IObservableVector<BasketProductDataModel^>^ get();
				void set(IObservableVector<BasketProductDataModel^>^ val);
			}

			property IObservableVector<ProductDeliveryDataModel^>^ ProductDelivery
			{
				IObservableVector<ProductDeliveryDataModel^>^ get();
				void set(IObservableVector<ProductDeliveryDataModel^>^ val);
			}

			property double PriceDelivery
			{
				double get();
				void set(double val);
			}

			property double GlobalPrice
			{
				double get();
				void set(double val);
			}

			property bool IsPickup
			{
				bool get();
				void set(bool val);
			}

			property bool IsStandart
			{
				bool get();
				void set(bool val);
			}

			property bool IsPickupNew
			{
				bool get();
				void set(bool val);
			}

			property Visibility PersonalDataVisibility
			{
				Visibility get();
				void set(Visibility val);
			}

			property Visibility ListProductVisibility
			{
				Visibility get();
				void set(Visibility val);
			}

			property Visibility AddressDeliveryVisibility
			{
				Visibility get();
				void set(Visibility val);
			}

			property String^ FirstName
			{
				String^ get();
				void set(String^ val);
			}

			property String^ LastName
			{
				String^ get();
				void set(String^ val);
			}

			property String^ Phone
			{
				String^ get();
				void set(String^ val);
			}

			property String^ Email
			{
				String^ get();
				void set(String^ val);
			}

			property String^ AddressStreet
			{
				String^ get();
				void set(String^ val);
			}

			property String^ AddressBuilding
			{
				String^ get();
				void set(String^ val);
			}

			property String^ AddressNumber
			{
				String^ get();
				void set(String^ val);
			}

			property String^ AddressFloor
			{
				String^ get();
				void set(String^ val);
			}

			property String^ AddressApartment
			{
				String^ get();
				void set(String^ val);
			}

			property RelayCommand^ IsPickupCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ IsStandartCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ IsPickupNewCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ PickShopCommand
			{
				RelayCommand^ get();
			}

			property RelayCommand^ OrderEndCommand
			{
				RelayCommand^ get();
			}
		internal:
			OrderViewModels(Windows::UI::Xaml::Controls::Page^ page);
			void OnAmountSum();
			void CommandUpdate(bool is_pickup, bool is_pickupNew, bool is_standart);
			void OnDeliveryProductLoaded(ProductGroupDelivery valueType);
			void OnPickShop(Object^ parameter);
			void OnPickShopItemClick(Object ^sender, Object ^Item);
			bool OnTextChangedContent();
			void OnPopupCities();
			void OnOrderCompleted(IVector<OrderDeliveryResult^>^ valueOrder);
			bool IsProductBasket(int id);
			void OnRemoveToBasketProduct();
			void OnOrderCommand();
		private:
			OrderCalcModels^ source_orderCalc;
			IObservableVector<BasketProductDataModel^>^ source_ProductBasket;
			IObservableVector<ProductDeliveryDataModel^>^ source_productDelivery;
			bool source_isPickup;
			bool source_isStandart;
			bool source_isPickupNew;
			double source_globalPrice;
			double source_deliveryPrice;
			Visibility source_visibilityListProduct;
			Visibility source_visibilityPersonalData;
			Visibility source_visibilityAddressDelivery;

			String^ text_firstName;
			String^ text_lastName;
			String^ text_Phone;
			String^ text_Email;
			String^ text_AddressStreet;
			String^ text_AddressBuilding;
			String^ text_AddressNumber;
			String^ text_AddressFloor;
			String^ text_AddressApartment;
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
		};
	}
}