//
// AddDialog.xaml.h
// AddDialog 类的声明
//

#pragma once

#include "AddDialog.g.h"

namespace BjfuGuide
{
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class AddDialog sealed
	{	
	public:
		AddDialog();
		void setTextBox1(Platform::String^ text);
		void setTextBox2(Platform::String^ text);
		void setTextBox3(Platform::String^ text);
		void setTextBox1Text(Platform::String^ text, bool IsEnable);
		void setTextBox2Text(Platform::String^ text, bool IsEnable);
		void setTextBox3Text(Platform::String^ text, bool IsEnable);
		void setPasswordBox();
		Platform::String^ getTextBox1();
		Platform::String^ getTextBox2();
		Platform::String^ getTextBox3();
		Platform::String^ getPasswordBox();
		bool isComplete();
		void setComplete(bool complete);
	private:
		bool complete;
		void ContentDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
		void ContentDialog_SecondaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args);
	};
}
