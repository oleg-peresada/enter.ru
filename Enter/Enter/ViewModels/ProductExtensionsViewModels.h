#pragma once

#include "ViewModelsBase.h"
#include "LoadStateEventArgs.h"
#include "RelayCommand.h"

#include "View\ProductExtensionsPhotoView.xaml.h"
#include "View\AccountView.xaml.h"
#include "View\BasketView.xaml.h"
#include "View\AccessoriesView.xaml.h"

#include "DataModel\BasketProductSerialize.h"
#include "DataModel\GroupCategorySource.h"
#include "DataModel\Storage\AutorizationStorage.h"

#include "Template\ToastNotificationCore.h"

using namespace Enter;
using namespace Enter::DataModel;
using namespace EnterStore::Models;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;

namespace Enter
{
	namespace ViewModels
	{
		[Windows::UI::Xaml::Data::Bindable]
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class ProductExtensionsViewModels sealed : public ViewModelsBase
		{
		public:
			property ProductExtensionsCardModels^ ProductCard
			{
				ProductExtensionsCardModels^ get();
				void set(ProductExtensionsCardModels^ val);
			}

			property IVector<BasketProductDataModel^>^ BasketProduct
			{
				IVector<BasketProductDataModel^>^ get();
				void set(IVector<BasketProductDataModel^>^ val);
			}

			property IVector<ProductPropertyDataModel^>^ FeaturesProduct
			{
				IVector<ProductPropertyDataModel^>^ get();
				void set(IVector<ProductPropertyDataModel^>^ value);
			}

			property IObservableVector<ReviewModels^>^ ReviewsProduct
			{
				IObservableVector<ReviewModels^>^ get();
				void set(IObservableVector<ReviewModels^>^ value);
			}

			property IVector<ProductOptionPropertyDataModel^>^ OptionViewExtensions
			{
				IVector<ProductOptionPropertyDataModel^>^ get();
				void set(IVector<ProductOptionPropertyDataModel^>^ value);
			}

			property Visibility VisibilityBasket
			{
				Visibility get();
				void set(Visibility val);
			}

			property bool IsEnabledProductItem
			{
				bool get();
				void set(bool val);
			}

			property double WidthReviewSection
			{
				double get();
				void set(double value);
			}

			property double WidthDescriptionSection
			{
				double get();
				void set(double value);
			}

			property double WidthAboutSection
			{
				double get();
				void set(double value);
			}

			property Visibility VisibilityOption
			{
				Visibility get();
				void set(Visibility value);
			}

			property Visibility VisibilityOptionMore
			{
				Visibility get();
				void set(Visibility value);
			}

			property Visibility ProgressPanel
			{
				Visibility get();
				void set(Visibility value);
			}

			property Visibility ContentPanel
			{
				Visibility get();
				void set(Visibility value);
			}

			property Visibility DiscountVisibility
			{
				Visibility get();
				void set(Visibility value);
			}

			property Visibility AccessoriesVisibility
			{
				Visibility get();
				void set(Visibility value);
			}

			property int Discount
			{
				int get();
				void set(int value);
			}

			property int32 SizeMedia
			{
				int32 get();
				void set(int32 value);
			}

			property ICommand^ BasketCommand
			{
				ICommand^ get();
			}

			property ICommand^ RemoveProduct
			{
				ICommand^ get();
			}

			property ICommand^ AddProduct
			{
				ICommand^ get();
			}

			property ICommand^ ShopCommand
			{
				ICommand^ get();
			}

			property ICommand^ FlyoutMoreCommand
			{
				ICommand^ get();
			}

			property ICommand^ SizeMediaCommand
			{
				ICommand^ get();
			}

			property ICommand^ SettingCommand
			{
				ICommand^ get();
			}

			property ICommand^ AccessoriesCommand
			{
				ICommand^ get();
			}

			property ICommand^ RefreshCommand
			{
				ICommand^ get();
			}
		internal:
			ProductExtensionsViewModels(Windows::UI::Xaml::Controls::Page^ page);
			concurrency::task<void> OnLoadingContent(int id, bool isCached);
			void OptionSelected();
			void OnHubSectionHeader(Object^ headerName);
			void AddProductToPushCommand();
			void RemoveProductPushCommand();
			void OnOptionSelectedChanged(Object^ sender, SelectionChangedEventArgs^ e);
			concurrency::task<bool> IsProductAndLoadingProduct(int productId);
			void OnPropertyChangedSelected(Platform::Object^ sender, Windows::UI::Xaml::Controls::SelectionChangedEventArgs^ e);
			void ProgressOrContent(bool state);
		private:
			ProductExtensionsCardModels^ m_productCard;
			IVector<BasketProductDataModel^>^ m_basketProduct;
			IVector<ProductPropertyDataModel^>^ m_FeaturesProduct;
			IVector<ProductOptionPropertyDataModel^>^ m_optionViewExtensions;
			IObservableVector<ReviewModels^>^ m_reviewsProduct;
			Visibility m_VisibilityBasket;
			bool m_isEnabledItemProduct;
			double m_width_reviewSection;
			double m_width_descriptionSection;
			Object^ m_modelSelectedProduct;
			bool m_isSelectedOption;
			Visibility m_visibilityOption;
			Visibility m_visibilityOptionMore;
			Visibility m_progressPanel;
			Visibility m_contentPanel;
			Visibility m_visibilityDiscount;
			Visibility m_accessoriesVisibility;
			double m_widthAboutSection;
			double m_heightAboutSection;
			int32 m_sizeMedia;
			int m_discount;
		protected:
			virtual void OnLoadState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::LoadStateEventArgs^ state) override;
			virtual void OnSaveState(Windows::UI::Xaml::Navigation::NavigationEventArgs^ args, Enter::SaveStateEventArgs^ state) override;
		};
	}
}