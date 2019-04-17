//
// FrontStagePage.xaml.h
// FrontStagePage 类的声明
//

#pragma once

#include "FrontStagePage.g.h"

namespace BjfuGuide
{
	/// <summary>
	/// 可用于自身或导航至 Frame 内部的空白页。
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class FrontStagePage sealed
	{
	public:
		FrontStagePage();
	private:
		Platform::String^ SearchType;
		void RadioButton_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void SearchBar_TextChanged(Windows::UI::Xaml::Controls::AutoSuggestBox^ sender, Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs^ args);
		void SearchBar_QuerySubmitted(Windows::UI::Xaml::Controls::AutoSuggestBox^ sender, Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs^ args);
		void SearchBar_SuggestionChosen(Windows::UI::Xaml::Controls::AutoSuggestBox^ sender, Windows::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs^ args);
		void GetRoute_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void DesignRoute_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
