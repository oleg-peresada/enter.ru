//
// PickShopControl.xaml.cpp
// Реализация класса PickShopControl
//

#include "pch.h"
#include "PickShopControl.xaml.h"

using namespace Enter;
using namespace Enter::Controls;
using namespace Enter::DataModel;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Media::Animation;

PickShopControl::PickShopControl()
{
	InitializeComponent();
}


void PickShopControl::OnItemClickShop(Object^ sender, ItemClickEventArgs^ e)
{
	auto shopItem = dynamic_cast<OrderShopListModels^>(e->ClickedItem);
	if (shopItem != nullptr)
	{
		map->Center = ref new Bing::Maps::Location(shopItem->CoordLat, shopItem->CoordLong);
		map->SetZoomLevel(17);
		popupContent->Content = shopItem;
		popupContent->ContentTemplate = safe_cast<DataTemplate^>(Resources->Lookup("ContentPopupDataTemplate"));
		mapLayer->SetPosition(popupContent, ref new Bing::Maps::Location(shopItem->CoordLat, shopItem->CoordLong));
	}
}

void PickShopControl::OnLoaded(Object^ sender, RoutedEventArgs^ e)
{
	auto product_tag = dynamic_cast<ProductDeliveryDataModel^>(this->Tag);
	if (product_tag != nullptr && product_tag->Shop != nullptr && product_tag->Shop->Size > 0)
	{
		auto firstElement = product_tag->Shop->GetAt(0);
		map->Center = ref new Bing::Maps::Location(firstElement->CoordLat, firstElement->CoordLong);

		unsigned size = product_tag->Shop->Size;
		for (unsigned int i = 0; i < size; i++)
		{
			auto geoItem = product_tag->Shop->GetAt(i);

			auto pushPin = ref new ContentControl();
			auto stylePin = dynamic_cast<Windows::UI::Xaml::Style^>(this->Resources->Lookup("PushPinStyle"));
			if (stylePin != nullptr)
			{
				pushPin->Style = stylePin;
			}

			pushPin->Tag = geoItem;
			pushPin->Content = (i + 1).ToString();
			pushPin->Tapped += ref new TappedEventHandler(this, &PickShopControl::OnTappedPushPin);

			mapLayer->SetPosition(pushPin, ref new Bing::Maps::Location(geoItem->CoordLat, geoItem->CoordLong));
			map->Children->Append(pushPin);
		}
	}

	popupContent = ref new ContentControl();
	map->Children->Append(popupContent);
}

void PickShopControl::OnMapTapped(Object^ sender, TappedRoutedEventArgs^ e)
{
	auto d = e->GetPosition(map);
	
	auto s = "";
}

void PickShopControl::OnTappedPushPin(Object ^sender, TappedRoutedEventArgs ^args)
{
	auto element = dynamic_cast<ContentControl^>(sender);
	if (element != nullptr)
	{
		auto shop = safe_cast<OrderShopListModels^>(element->Tag);
		popupContent->Content = shop;
		map->Center = ref new Bing::Maps::Location(shop->CoordLat, shop->CoordLong);
		popupContent->ContentTemplate = safe_cast<DataTemplate^>(Resources->Lookup("ContentPopupDataTemplate"));
		mapLayer->SetPosition(popupContent, ref new Bing::Maps::Location(shop->CoordLat, shop->CoordLong));
		map->SetZoomLevel(17);
	}
}

void PickShopControl::OnSelectedPush(Object^ sender, RoutedEventArgs^ e)
{
	auto currentButton = dynamic_cast<Button^>(sender);
	if (currentButton != nullptr)
	{
		auto popup = dynamic_cast<Popup^>(this->Parent);
		if (popup != nullptr)
		{
			this->PickShopItemClick(this, currentButton->Tag);
			popup->IsOpen = false;
		}
	}
}

void PickShopControl::OnUnloaded(Object^ sender, RoutedEventArgs^ e)
{
}