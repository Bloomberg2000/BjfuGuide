//
// AddDialog.xaml.cpp
// AddDialog 类的实现
//

#include "pch.h"
#include "AddDialog.xaml.h"
#include "Util/UWPHelper.h"

using namespace BjfuGuide;

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

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“内容对话框”项模板

BjfuGuide::AddDialog::AddDialog()
{
	complete = false;
	InitializeComponent();
}

void BjfuGuide::AddDialog::setTextBox1(Platform::String^ text)
{
	TextBox1->Visibility = Windows::UI::Xaml::Visibility::Visible;
	Text1->Text = text;
	Text1->Visibility = Windows::UI::Xaml::Visibility::Visible;
}

void BjfuGuide::AddDialog::setTextBox2(Platform::String^ text)
{
	TextBox2->Visibility = Windows::UI::Xaml::Visibility::Visible;
	Text2->Text = text;
	Text2->Visibility = Windows::UI::Xaml::Visibility::Visible;
}

void BjfuGuide::AddDialog::setTextBox3(Platform::String^ text)
{
	TextBox3->Visibility = Windows::UI::Xaml::Visibility::Visible;
	Text3->Text = text;
	Text3->Visibility = Windows::UI::Xaml::Visibility::Visible;
}

void BjfuGuide::AddDialog::setTextBox1Text(Platform::String ^ text, bool IsEnable)
{
	TextBox1->Text = text;
	TextBox1->IsEnabled = IsEnable;
}

void BjfuGuide::AddDialog::setTextBox2Text(Platform::String ^ text, bool IsEnable)
{
	TextBox2->Text = text;
	TextBox2->IsEnabled = IsEnable;
}

void BjfuGuide::AddDialog::setTextBox3Text(Platform::String ^ text, bool IsEnable)
{
	TextBox3->Text = text;
	TextBox3->IsEnabled = IsEnable;
}

void BjfuGuide::AddDialog::setPasswordBox()
{
	PasswordBox->Visibility = Windows::UI::Xaml::Visibility::Visible;
	password->Visibility = Windows::UI::Xaml::Visibility::Visible;
}

Platform::String^ BjfuGuide::AddDialog::getTextBox1()
{
	return TextBox1->Text->ToString();
}

Platform::String^ BjfuGuide::AddDialog::getTextBox2()
{
	return TextBox2->Text->ToString();
}

Platform::String^ BjfuGuide::AddDialog::getTextBox3()
{
	return TextBox3->Text->ToString();
}

Platform::String^ BjfuGuide::AddDialog::getPasswordBox()
{
	return PasswordBox->Password;
}

bool BjfuGuide::AddDialog::isComplete()
{
	return complete;
}

void BjfuGuide::AddDialog::setComplete(bool complete)
{
	this->complete = complete;
}

void BjfuGuide::AddDialog::ContentDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args)
{
}

void BjfuGuide::AddDialog::ContentDialog_SecondaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^ args)
{
}
