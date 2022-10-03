//
// MainPage.xaml.cpp
// MainPage 类的实现。
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "HomePage.xaml.h"
#include "FrontStagePage.xaml.h"
#include "BackStagePage.xaml.h"

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
using namespace Windows::UI::Xaml::Interop;

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

MainPage::MainPage()
{
	InitializeComponent();
}


void BjfuGuide::MainPage::NavView_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	contentFrame->Navigate(TypeName(HomePage::typeid));
}


void BjfuGuide::MainPage::NavView_ItemInvoked(Windows::UI::Xaml::Controls::NavigationView^ sender, Windows::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs^ args)
{
	auto navItemTag = args->InvokedItemContainer->Tag->ToString();
	if (navItemTag == "home")
	{	
		contentFrame->Navigate(TypeName(HomePage::typeid));
		NavView->Header = "北林自助导游及信息服务系统";
	}
	if (navItemTag == "frontstage")
	{
		contentFrame->Navigate(TypeName(FrontStagePage::typeid));
		NavView->Header = "前台服务";
	}
	if (navItemTag == "backstage")
	{
		contentFrame->Navigate(TypeName(BackStagePage::typeid));
		NavView->Header = "后台管理";
	}
}