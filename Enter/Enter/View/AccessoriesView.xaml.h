//
// AccessoriesView.xaml.h
// Объявление класса AccessoriesView
//

#pragma once

#include "View\AccessoriesView.g.h"
#include "ViewModels\AccessoriesViewModels.h"

namespace Enter
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AccessoriesView sealed
	{
	public:
		AccessoriesView();
	private:
		Enter::ViewModels::AccessoriesViewModels^ accessoriesView;
		void OnItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
	};
}
