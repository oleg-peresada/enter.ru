#include "pch.h"
#include "ProductExtensionsViewModels.h"

using namespace Enter;
using namespace Enter::ViewModels;
using namespace Enter::View;
using namespace Enter::Template;
using namespace Enter::DataModel;
using namespace Enter::DataModel::Storage;
using namespace EnterStore::Models;
using namespace EnterStore::Commands;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Notifications;

ProductExtensionsViewModels::ProductExtensionsViewModels(Page^ page)
: ViewModelsBase(page), m_isSelectedOption(false)
{
	ProgressOrContent(true);
}

void ProductExtensionsViewModels::OnLoadState(NavigationEventArgs^ args, LoadStateEventArgs^ state)
{
	Helpers::LogPage("MainPageView/ProductExtensionsView");

	auto modelProduct = dynamic_cast<ProductCardModels^>(args->Parameter);
	if (modelProduct != nullptr)
	{
		OnLoadingContent(modelProduct->Id, false).then([this](void)
		{
			OptionSelected();
		}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
		return;
	}

	auto basketProduct = dynamic_cast<BasketProductDataModel^>(args->Parameter);
	if (basketProduct != nullptr)
	{
		OnLoadingContent(basketProduct->Id, false).then([this](void)
		{
			OptionSelected();
		}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
		return;
	}

	auto id = static_cast<int>(args->Parameter);
	OnLoadingContent(id, false).then([this](void)
	{
		OptionSelected();

	}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
}

//Загрузка данных
concurrency::task<void> ProductExtensionsViewModels::OnLoadingContent(int id, bool isCached)
{
	VisibilityBasket = Visibility::Collapsed;
	VisibilityOption = Visibility::Collapsed;
	VisibilityOptionMore = Visibility::Collapsed;
	DiscountVisibility = Visibility::Collapsed;
	AccessoriesVisibility = Visibility::Collapsed;

	WidthAboutSection = 0;
	WidthReviewSection = 0;
	WidthDescriptionSection = 0;

	Rect windowRect = Window::Current->Bounds;
	WidthAboutSection = windowRect.Width * 0.6555;

	m_isSelectedOption = false;
	int geo_id = CityTokenStorage::Current->Id != 0 ? CityTokenStorage::Current->Id : 14974;
	auto productCommand = ref new ProductExtensionsListCommands(id.ToString(), geo_id, ProductExtensionsType::Id);

	//Результат запроса
	return concurrency::create_task(productCommand->ProductExtensionsAsync(isCached)).then([this, geo_id](ProductExtensionsCardModels^ content)
	{
		ProductCard = content;
		SizeMedia = content->Media != nullptr ? content->Media->Size : 0;
		WidthDescriptionSection = content->Description == nullptr ? 0 : 800;
		int id_current = content->Id;

		if (content->Accessories != nullptr && content->Accessories->Size > 0)
		{
			AccessoriesVisibility = Visibility::Visible;
		}

		if (content->PriceOld > content->Price)
		{
			Discount = ((content->PriceOld - content->Price) * 100) / content->Price;
			DiscountVisibility = Visibility::Visible;
		}
		else
		{
			DiscountVisibility = Visibility::Collapsed;
		}

		return concurrency::create_task(IsProductAndLoadingProduct(id_current)).then([this, content](bool isValue) -> void //Проверка наличия товара
		{
			if (isValue)
			{
				VisibilityBasket = Visibility::Visible;
				IsEnabledProductItem = false;
			}
			else
			{
				VisibilityBasket = Visibility::Collapsed;
				if (content->Stock != nullptr && content->Stock->Quantity > 0)
				{
					IsEnabledProductItem = true;
				}
				else
				{
					IsEnabledProductItem = false;
				}
			}
		}).then([this, content](void)
		{
			//Разбиение свойств товара на группы
			FeaturesProduct = ProductPropertyConvert::PropertyGroupCreate(content->PropertyGroup, content->Property);

			//Получение отзывов к товара
			auto reviewCommand = ref new ReviewsCommands(content->Id, 0, -1, StatusReviews::None);
			auto reviewOperator = reviewCommand->ReviewsListAsync();
			return concurrency::create_task(reviewOperator).then([this](IObservableVector<ReviewModels^>^ contentReview) -> void
			{
				ReviewsProduct = ref new Vector<ReviewModels^>(begin(contentReview), end(contentReview));
				if ((Window::Current->Bounds.Height / 2) > 400.0)
				{
					WidthReviewSection = contentReview->Size == 0 ? 0 : ReviewsProduct->Size == 1 ? 550 : (ReviewsProduct->Size + 1) / 2 * 550;
				}
				else
				{
					WidthReviewSection = contentReview->Size == 0 ? 0 : ReviewsProduct->Size == 1 ? 550 : ReviewsProduct->Size * 550;
				}
			}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
		}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
	}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
}

//Опции выбора дополнительных параметров
void ProductExtensionsViewModels::OptionSelected()
{
	if (ProductCard != nullptr && ProductCard->ModelProperty && ProductCard->ModelProperty->Size > 0 && ProductCard->ModelProperty->GetAt(0)->Option != nullptr)
	{
		if (ProductCard->ModelProperty->Size > 1)
		{
			VisibilityOptionMore = Visibility::Visible;
		}
		else
		{
			VisibilityOptionMore = Visibility::Collapsed;
		}

		VisibilityOption = Visibility::Visible;
		OptionViewExtensions = ProductOptionPropertyDataModel::ToView(ProductCard->ModelProperty, ProductCard->Property);

		if (OptionViewExtensions != nullptr && OptionViewExtensions->Size == 0)
		{
			VisibilityOption = Visibility::Collapsed;
			m_isSelectedOption = true;
			ProgressOrContent(false);
			return;
		}
		else
		{
			//Поиск текущего товара во всех доступных опциях
			unsigned int size = ProductCard->ModelProperty->Size;
			for (unsigned int index = 0; index < size; index++)
			{
				auto elem = ProductCard->ModelProperty->GetAt(index);
				if (elem != nullptr)
				{
					unsigned int optionSize = elem->Option->Size;
					for (unsigned int iOption = 0; iOption < optionSize; iOption++)
					{
						auto optionElem = elem->Option->GetAt(iOption);
						if (optionElem->Product->Id == ProductCard->Id)
						{
							OptionViewExtensions->SetAt(0, ref new Enter::DataModel::ProductOptionPropertyDataModel(optionElem, elem->Option, elem));
							m_isSelectedOption = true;
							ProgressOrContent(false);
							return;
						}
					}
				}
			}
		}
	}
	else
	{
		VisibilityOption = Visibility::Collapsed;
		m_isSelectedOption = true;
		ProgressOrContent(false);
	}
}

void ProductExtensionsViewModels::OnSaveState(NavigationEventArgs^ args, SaveStateEventArgs^ state)
{
}

void ProductExtensionsViewModels::OnHubSectionHeader(Object^ headerName)
{
	String^ name = dynamic_cast<String^>(headerName);
	if (name == "Изображения продукта")
	{
		ViewFrame->Navigate(ProductExtensionsPhotoView::typeid, ProductCard);
	}
}

void ProductExtensionsViewModels::AddProductToPushCommand()
{
	if (ProductCard == nullptr) return;

	auto vect = ref new Vector<BasketProductDataModel^>(begin(BasketProduct), end(BasketProduct));

	auto basket = std::shared_ptr<BasketProductSerialize>();
	auto product = ref new BasketProductDataModel(ProductCard->Id,
		ProductCard->Article,
		ProductCard->Token,
		ProductCard->Name,
		ProductCard->MediaImage,
		1,
		ProductCard->Stock->Quantity,
		ProductCard->Price);

	vect->Append(product);
	(*basket).Save(vect);
	BasketProduct = vect;

	VisibilityBasket = Visibility::Visible;
	IsEnabledProductItem = false;

	auto toast = ref new ToastNotification(ToastNotificationCore::ToastText02("Товар добавлен в корзину", ProductCard->Name));
	auto manager = ToastNotificationManager::CreateToastNotifier();
	manager->Show(toast);
}

void ProductExtensionsViewModels::RemoveProductPushCommand()
{
	if (ProductCard == nullptr && ProductCard->Stock->Quantity == 0) return;

	auto vect = ref new Vector<BasketProductDataModel^>(begin(BasketProduct), end(BasketProduct));
	unsigned int size = vect->Size;

	for (unsigned int i = 0; i < size; i++)
	{
		if (ProductCard->Id == vect->GetAt(i)->Id)
		{
			vect->RemoveAt(i);

			VisibilityBasket = Visibility::Collapsed;
			IsEnabledProductItem = true;

			auto toast = ref new ToastNotification(ToastNotificationCore::ToastText02("Товар удален из корзины", ProductCard->Name));
			auto manager = ToastNotificationManager::CreateToastNotifier();
			manager->Show(toast);

			auto basket = std::shared_ptr<BasketProductSerialize>();
			(*basket).Save(vect);
			BasketProduct = vect;

			return;
		}
	}
}

void ProductExtensionsViewModels::OnOptionSelectedChanged(Object^ sender, SelectionChangedEventArgs^ e)
{
	if (m_isSelectedOption)
	{
		auto element = dynamic_cast<ComboBox^>(sender);
		if (element != nullptr)
		{
			if (e->AddedItems != nullptr && e->AddedItems->Size > 0)
			{
				auto element = dynamic_cast<OptionViewTypeModel^>(e->AddedItems->GetAt(0));
				if (element != nullptr)
				{
					OnLoadingContent(element->Product->Id, false).then([this, element](void)
					{
						this->OptionSelected();
					});
				}
			}
		}
	}
}

void ProductExtensionsViewModels::OnPropertyChangedSelected(Object^ sender, SelectionChangedEventArgs^ e)
{
	auto box = dynamic_cast<ComboBox^>(sender);
	if (box != nullptr)
	{
		m_modelSelectedProduct = box->SelectedItem;
	}
}

//Поиск товара добавленных в корзину
concurrency::task<bool> ProductExtensionsViewModels::IsProductAndLoadingProduct(int productId)
{
	auto basketProduct = std::shared_ptr<BasketProductSerialize>();
	return concurrency::create_task((*basketProduct).Open()).then([this, productId](IVector<BasketProductDataModel^>^ valContent) -> bool
	{
		BasketProduct = valContent;
		for (const auto &item : valContent)
		{
			if (item->Id == productId)
			{
				return true;
			}
		}

		return false;
	}).then(TaskException<bool>(), concurrency::task_continuation_context::use_current());
}

void ProductExtensionsViewModels::ProgressOrContent(bool state)
{
	if (state)
	{
		ProgressPanel = Visibility::Visible;
		ContentPanel = Visibility::Collapsed;
	}
	else
	{
		ProgressPanel = Visibility::Collapsed;
		ContentPanel = Visibility::Visible;
	}
}

ProductExtensionsCardModels^ ProductExtensionsViewModels::ProductCard::get()
{
	return m_productCard;
}

void ProductExtensionsViewModels::ProductCard::set(ProductExtensionsCardModels^ val)
{
	m_productCard = val;
	OnPropertyChanged("ProductCard");
}

IVector<BasketProductDataModel^>^ ProductExtensionsViewModels::BasketProduct::get()
{
	return m_basketProduct;
}

void ProductExtensionsViewModels::BasketProduct::set(IVector<BasketProductDataModel^>^ val)
{
	m_basketProduct = val;
	OnPropertyChanged("BasketProduct");
}

IVector<ProductPropertyDataModel^>^ ProductExtensionsViewModels::FeaturesProduct::get()
{
	return m_FeaturesProduct;
}

void ProductExtensionsViewModels::FeaturesProduct::set(IVector<ProductPropertyDataModel^>^ value)
{
	m_FeaturesProduct = value;
	OnPropertyChanged("FeaturesProduct");
}

IObservableVector<ReviewModels^>^ ProductExtensionsViewModels::ReviewsProduct::get()
{
	return m_reviewsProduct;
}

void ProductExtensionsViewModels::ReviewsProduct::set(IObservableVector<ReviewModels^>^ value)
{
	m_reviewsProduct = value;
	OnPropertyChanged("ReviewsProduct");
}

IVector<ProductOptionPropertyDataModel^>^ ProductExtensionsViewModels::OptionViewExtensions::get()
{
	return m_optionViewExtensions;
}

void ProductExtensionsViewModels::OptionViewExtensions::set(IVector<ProductOptionPropertyDataModel^>^ value)
{
	m_optionViewExtensions = value;
	OnPropertyChanged("OptionViewExtensions");
}

Visibility ProductExtensionsViewModels::VisibilityBasket::get()
{
	return m_VisibilityBasket;
}

void ProductExtensionsViewModels::VisibilityBasket::set(Visibility val)
{
	m_VisibilityBasket = val;
	OnPropertyChanged("VisibilityBasket");
}

bool ProductExtensionsViewModels::IsEnabledProductItem::get()
{
	return m_isEnabledItemProduct;
}

void ProductExtensionsViewModels::IsEnabledProductItem::set(bool val)
{
	m_isEnabledItemProduct = val;
	OnPropertyChanged("IsEnabledProductItem");
}

double ProductExtensionsViewModels::WidthReviewSection::get()
{
	return m_width_reviewSection;
}

void ProductExtensionsViewModels::WidthReviewSection::set(double value)
{
	m_width_reviewSection = value;
	OnPropertyChanged("WidthReviewSection");
}

double ProductExtensionsViewModels::WidthDescriptionSection::get()
{
	return m_width_descriptionSection;
}

void ProductExtensionsViewModels::WidthDescriptionSection::set(double value)
{
	m_width_descriptionSection = value;
	OnPropertyChanged("WidthDescriptionSection");
}

double ProductExtensionsViewModels::WidthAboutSection::get()
{
	return m_widthAboutSection;
}

void ProductExtensionsViewModels::WidthAboutSection::set(double value)
{
	m_widthAboutSection = value;
	OnPropertyChanged("WidthAboutSection");
}

Visibility ProductExtensionsViewModels::VisibilityOption::get()
{
	return m_visibilityOption;
}

void ProductExtensionsViewModels::VisibilityOption::set(Visibility value)
{
	m_visibilityOption = value;
	OnPropertyChanged("VisibilityOption");
}

Visibility ProductExtensionsViewModels::VisibilityOptionMore::get()
{
	return m_visibilityOptionMore;
}

void ProductExtensionsViewModels::VisibilityOptionMore::set(Visibility value)
{
	m_visibilityOptionMore = value;
	OnPropertyChanged("VisibilityOptionMore");
}

Visibility ProductExtensionsViewModels::ProgressPanel::get()
{
	return m_progressPanel;
}

void ProductExtensionsViewModels::ProgressPanel::set(Visibility value)
{
	m_progressPanel = value;
	OnPropertyChanged("ProgressPanel");
}

Visibility ProductExtensionsViewModels::ContentPanel::get()
{
	return m_contentPanel;
}

void ProductExtensionsViewModels::ContentPanel::set(Visibility value)
{
	m_contentPanel = value;
	OnPropertyChanged("ContentPanel");
}

Visibility ProductExtensionsViewModels::DiscountVisibility::get()
{
	return m_visibilityDiscount;
}

void ProductExtensionsViewModels::DiscountVisibility::set(Visibility value)
{
	m_visibilityDiscount = value;
	OnPropertyChanged("DiscountVisibility");
}

Visibility ProductExtensionsViewModels::AccessoriesVisibility::get()
{
	return m_accessoriesVisibility;
}

void ProductExtensionsViewModels::AccessoriesVisibility::set(Visibility value)
{
	m_accessoriesVisibility = value;
	OnPropertyChanged("AccessoriesVisibility");
}

int ProductExtensionsViewModels::Discount::get()
{
	return m_discount;
}

void ProductExtensionsViewModels::Discount::set(int value)
{
	m_discount = value;
	OnPropertyChanged("Discount");
}

int32 ProductExtensionsViewModels::SizeMedia::get()
{
	return m_sizeMedia;
}

void ProductExtensionsViewModels::SizeMedia::set(int32 value)
{
	m_sizeMedia = value;
	OnPropertyChanged("SizeMedia");
}

ICommand^ ProductExtensionsViewModels::BasketCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		ViewFrame->Navigate(BasketView::typeid);
	}, [this](Object^)
	{
		return ViewFrame != nullptr;
	});
}

ICommand^ ProductExtensionsViewModels::RemoveProduct::get()
{
	return ref new RelayCommand([this](Object^)
	{
		RemoveProductPushCommand();
	}, [this](Object^)
	{
		return true;
	});
}

ICommand^ ProductExtensionsViewModels::AddProduct::get()
{
	return ref new RelayCommand([this](Object^)
	{
		AddProductToPushCommand();
	}, [this](Object^)
	{
		return true;
	});
}

ICommand^ ProductExtensionsViewModels::ShopCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		ViewFrame->Navigate(AboutShopView::typeid);
	}, [this](Object^)
	{
		return true;
	});
}

ICommand^ ProductExtensionsViewModels::FlyoutMoreCommand::get()
{
	return ref new RelayCommand([this](Object^ parameter)
	{
		if (m_modelSelectedProduct != nullptr)
		{
			auto element = dynamic_cast<OptionViewTypeModel^>(m_modelSelectedProduct);
			if (element != nullptr)
			{
				OnLoadingContent(element->Product->Id, false).then([this, element](void)
				{
					this->OptionSelected();
				});
			}
		}
	}, [this](Object^)
	{
		return true;
	});
}

ICommand^ ProductExtensionsViewModels::SizeMediaCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		ViewFrame->Navigate(ProductExtensionsPhotoView::typeid, ProductCard);
	}, [this](Object^)
	{
		return true;
	});
}

ICommand^ ProductExtensionsViewModels::SettingCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		ViewFrame->Navigate(AccountView::typeid, nullptr);
	}, [this](Object^)
	{
		return true;
	});
}

ICommand^ ProductExtensionsViewModels::AccessoriesCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		ViewFrame->Navigate(AccessoriesView::typeid, ProductCard);
	}, [this](Object^)
	{
		return true;
	});
}

ICommand^ ProductExtensionsViewModels::RefreshCommand::get()
{
	return ref new RelayCommand([this](Object^)
	{
		if (ProductCard == nullptr) return;

		ProgressOrContent(true);
		int id = ProductCard->Id;
		OnLoadingContent(id, true).then([this](void)
		{
			OptionSelected();

		}).then(TaskException<void>(), concurrency::task_continuation_context::use_current());
	}, [this](Object^)
	{
		return true;
	});
}