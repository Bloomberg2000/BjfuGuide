//
// BackStagePage.xaml.cpp
// BackStagePage 类的实现
//

#include "pch.h"
#include "BackStagePage.xaml.h"
#include "MainPage.xaml.h"
#include "ServiceController.h"
#include "AddDialog.xaml.h"

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

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

BackStagePage::BackStagePage()
{
	InitializeComponent();
	UserLogin();
	loadSpotData();
	loadRouteData();
}

bool BjfuGuide::BackStagePage::UserLogin()
{
	if (ServiceController::IsLogin == false) {
		auto dialog = ref new AddDialog;
		dialog->Title = "登录";
		dialog->setTextBox1("账户");
		dialog->setPasswordBox();
		dialog->PrimaryButtonText = "登录";
		dialog->SecondaryButtonText = "取消";
		dialog->PrimaryButtonClick += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Xaml::Controls::ContentDialog ^, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs ^>(this, &BjfuGuide::BackStagePage::loginDialog_PrimaryButtonClick);
		dialog->ShowAsync();
	}
	return true;
}

void BackStagePage::loadSpotData() {
	SpotManagementTable->Children->Clear();
	auto vertexArr = ServiceController::mapService.getV();
	auto table = ref new Grid;
	int rowNum = 0;
	for (int i = 0; i < vertexArr.size(); i++)
	{
		// 创建新行
		auto rowDefinition = ref new RowDefinition;
		SpotManagementTable->RowDefinitions->Append(rowDefinition);

		// 创建表格内容
		auto tableContents = ref new Grid;
		SpotManagementTable->SetRow(tableContents, rowNum++);

		// 设置表格列
		auto columnDefinition1 = ref new ColumnDefinition;
		auto columnDefinition2 = ref new ColumnDefinition;
		auto columnDefinition3 = ref new ColumnDefinition;

		tableContents->ColumnDefinitions->Append(columnDefinition1);
		tableContents->ColumnDefinitions->Append(columnDefinition2);
		tableContents->ColumnDefinitions->Append(columnDefinition3);

		// 设置内容
		auto contentA = ref new TextBlock;
		contentA->Text = UWPHelper::std_str_To_Platform_Str(vertexArr[i].data.get_name().cpp_str());
		contentA->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
		contentA->Width = 100;
		contentA->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left;
		contentA->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
		tableContents->SetColumn(contentA, 0);

		auto contentB = ref new TextBlock;
		contentB->Text = UWPHelper::std_str_To_Platform_Str(vertexArr[i].data.get_info().cpp_str());
		contentB->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
		contentB->Width = 300;
		contentB->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left;
		contentB->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
		tableContents->SetColumn(contentB, 1);

		auto Buttons = ref new RelativePanel;
		auto editButton = ref new Button;
		auto delButton = ref new Button;

		editButton->Content = "编辑";
		editButton->Tag = UWPHelper::std_str_To_Platform_Str(vertexArr[i].data.get_name().cpp_str());
		editButton->Click += ref new Windows::UI::Xaml::RoutedEventHandler(this, &BjfuGuide::BackStagePage::editButton_Click);
		delButton->Content = "删除";
		delButton->Tag = UWPHelper::std_str_To_Platform_Str(vertexArr[i].data.get_name().cpp_str());
		delButton->Click += ref new Windows::UI::Xaml::RoutedEventHandler(this, &BjfuGuide::BackStagePage::delButton_Click);

		Buttons->SetAlignLeftWithPanel(editButton, true);
		Buttons->SetRightOf(delButton, editButton);
		Buttons->Width = 100;

		Buttons->Children->Append(editButton);
		Buttons->Children->Append(delButton);

		tableContents->SetColumn(Buttons, 3);

		//放入列表
		tableContents->Children->Append(contentA);
		tableContents->Children->Append(contentB);
		tableContents->Children->Append(Buttons);

		SpotManagementTable->Children->Append(tableContents);
	}
}

void BjfuGuide::BackStagePage::loadRouteData()
{
	RouteManagementTable->Children->Clear();
	auto bjfuMap = ServiceController::mapService.get_bjfuMap();
	auto table = ref new Grid;
	int rowNum = 0;
	for (int i = 0; i < bjfuMap->vNum; i++) {
		for (int j = i + 1; j < bjfuMap->vNum; j++) {
			if (bjfuMap->exists(i, j)) {
				// 创建新行
				auto rowDefinition = ref new RowDefinition;
				RouteManagementTable->RowDefinitions->Append(rowDefinition);

				// 创建表格内容
				auto tableContents = ref new Grid;
				RouteManagementTable->SetRow(tableContents, rowNum++);

				// 设置表格列
				auto columnDefinition1 = ref new ColumnDefinition;
				auto columnDefinition2 = ref new ColumnDefinition;
				auto columnDefinition3 = ref new ColumnDefinition;
				auto columnDefinition4 = ref new ColumnDefinition;

				tableContents->ColumnDefinitions->Append(columnDefinition1);
				tableContents->ColumnDefinitions->Append(columnDefinition2);
				tableContents->ColumnDefinitions->Append(columnDefinition3);
				tableContents->ColumnDefinitions->Append(columnDefinition4);

				// 设置内容
				auto contentA = ref new TextBlock;
				contentA->Text = UWPHelper::std_str_To_Platform_Str(bjfuMap->vertex(i).get_name().cpp_str());
				contentA->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
				contentA->Width = 120;
				contentA->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left;
				contentA->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
				tableContents->SetColumn(contentA, 0);

				auto contentB = ref new TextBlock;
				contentB->Text = UWPHelper::std_str_To_Platform_Str(bjfuMap->vertex(j).get_name().cpp_str());
				contentB->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
				contentB->Width = 120;
				contentB->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left;
				contentB->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
				tableContents->SetColumn(contentB, 1);


				auto contentC = ref new TextBlock;
				contentC->Text = UWPHelper::std_str_To_Platform_Str(std::to_string(bjfuMap->edge(i, j).get_routeLength()));
				contentC->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
				contentC->Width = 120;
				contentC->HorizontalAlignment = Windows::UI::Xaml::HorizontalAlignment::Left;
				contentC->VerticalAlignment = Windows::UI::Xaml::VerticalAlignment::Top;
				tableContents->SetColumn(contentC, 2);


				auto Buttons = ref new RelativePanel;
				auto delButton = ref new Button;

				delButton->Content = "删除";
				delButton->Tag = UWPHelper::std_str_To_Platform_Str(bjfuMap->vertex(i).get_name().cpp_str()) + " "
					+ UWPHelper::std_str_To_Platform_Str(bjfuMap->vertex(j).get_name().cpp_str());
				delButton->Click += ref new Windows::UI::Xaml::RoutedEventHandler(this, &BjfuGuide::BackStagePage::delRouteButton_Click);

				Buttons->Width = 100;

				Buttons->Children->Append(delButton);

				tableContents->SetColumn(Buttons, 3);

				//放入列表
				tableContents->Children->Append(contentA);
				tableContents->Children->Append(contentB);
				tableContents->Children->Append(contentC);
				tableContents->Children->Append(Buttons);

				RouteManagementTable->Children->Append(tableContents);
			}
		}
	}
}

void BjfuGuide::BackStagePage::loginDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog ^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs ^ args)
{
	auto dialog = dynamic_cast<AddDialog^>(sender);
	ServiceController::userService.login(UWPHelper::Platform_str_to_std_str(dialog->getTextBox1()),
			UWPHelper::Platform_str_to_std_str(dialog->getPasswordBox()));
	
}


void BjfuGuide::BackStagePage::AddSpot_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto dialog = ref new AddDialog;
	auto button = dynamic_cast<Button^>(sender);
	dialog->Title = "添加景点";
	dialog->setTextBox1("景点名称");
	dialog->setTextBox2("景点简介");
	dialog->PrimaryButtonText = "添加";
	dialog->SecondaryButtonText = "取消";
	dialog->PrimaryButtonClick += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Xaml::Controls::ContentDialog ^, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs ^>(this, &BjfuGuide::BackStagePage::addSpotDialog_PrimaryButtonClick);
	dialog->ShowAsync();
}


void BjfuGuide::BackStagePage::AddRoute_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto dialog = ref new AddDialog;
	auto button = dynamic_cast<Button^>(sender);
	dialog->Title = "添加路径";
	dialog->setTextBox1("景点A");
	dialog->setTextBox2("景点B");
	dialog->setTextBox3("距离");
	dialog->PrimaryButtonText = "添加";
	dialog->SecondaryButtonText = "取消";
	dialog->PrimaryButtonClick += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Xaml::Controls::ContentDialog ^, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs ^>(this, &BjfuGuide::BackStagePage::addRouteDialog_PrimaryButtonClick);
	dialog->ShowAsync();
}

void BjfuGuide::BackStagePage::editButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto dialog = ref new AddDialog;
	auto button = dynamic_cast<Button^>(sender);
	auto spotName = button->Tag->ToString();
	auto vArr = ServiceController::mapService.getV();
	dialog->Title = "编辑景点";
	dialog->setTextBox1("景点名称");
	dialog->setTextBox2("景点简介");
	for (int i = 0; i < vArr.size(); i++)
	{
		if (vArr[i].data.get_name() == UWPHelper::Platform_str_to_std_str(spotName))
		{
			dialog->setTextBox1Text(UWPHelper::std_str_To_Platform_Str(vArr[i].data.get_name().cpp_str()), false);
			dialog->setTextBox2Text(UWPHelper::std_str_To_Platform_Str(vArr[i].data.get_info().cpp_str()), true);
			break;
		}
	}
	dialog->PrimaryButtonText = "修改";
	dialog->SecondaryButtonText = "取消";
	dialog->PrimaryButtonClick += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Xaml::Controls::ContentDialog ^, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs ^>(this, &BjfuGuide::BackStagePage::editDialog_PrimaryButtonClick);
	dialog->ShowAsync();
}

void BjfuGuide::BackStagePage::delButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto dialog = ref new ContentDialog;
	auto button = dynamic_cast<Button^>(sender);
	dialog->Title = "删除";
	dialog->Content = "确认要删除" + button->Tag + "吗?";
	dialog->Tag = button->Tag;
	dialog->IsSecondaryButtonEnabled = true;
	dialog->PrimaryButtonText = "确认";
	dialog->SecondaryButtonText = "取消";
	dialog->PrimaryButtonClick += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Xaml::Controls::ContentDialog ^, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs ^>(this, &BjfuGuide::BackStagePage::delDialog_PrimaryButtonClick);
	dialog->ShowAsync();
}

void BjfuGuide::BackStagePage::delRouteButton_Click(Platform::Object ^ sender, Windows::UI::Xaml::RoutedEventArgs ^ e)
{
	auto dialog = ref new ContentDialog;
	auto button = dynamic_cast<Button^>(sender);
	dialog->Title = "删除";
	dialog->Content = "确认要删除这条线路吗?";
	dialog->Tag = button->Tag;
	dialog->IsSecondaryButtonEnabled = true;
	dialog->PrimaryButtonText = "确认";
	dialog->SecondaryButtonText = "取消";
	dialog->PrimaryButtonClick += ref new Windows::Foundation::TypedEventHandler<Windows::UI::Xaml::Controls::ContentDialog ^, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs ^>(this, &BjfuGuide::BackStagePage::delRouteDialog_PrimaryButtonClick);
	dialog->ShowAsync();
}

void BjfuGuide::BackStagePage::addSpotDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog ^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs ^ args)
{
	auto dialog = dynamic_cast<AddDialog^>(sender);
	ServiceController::mapService.createSpot(UWPHelper::Platform_str_to_std_str(dialog->getTextBox1()),
		UWPHelper::Platform_str_to_std_str(dialog->getTextBox2()));
	loadSpotData();
}

void BjfuGuide::BackStagePage::addRouteDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog ^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs ^ args)
{
	auto dialog = dynamic_cast<AddDialog^>(sender);
	auto distance = UWPHelper::Platform_str_to_std_str(dialog->getTextBox3());

	ServiceController::mapService.createRoute(UWPHelper::Platform_str_to_std_str(dialog->getTextBox1()),
		UWPHelper::Platform_str_to_std_str(dialog->getTextBox2()),
		std::stoi(distance));
	loadRouteData();
}

void BjfuGuide::BackStagePage::editDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog ^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs ^ args)
{
	auto spotToEdit = sender->Tag->ToString();
	auto dialog = dynamic_cast<AddDialog^>(sender);

	ServiceController::mapService.editSpot(UWPHelper::Platform_str_to_std_str(dialog->getTextBox1()),
		UWPHelper::Platform_str_to_std_str(dialog->getTextBox2()));
	loadSpotData();
}


void BjfuGuide::BackStagePage::delDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog ^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs ^ args)
{
	auto spotToDel = sender->Tag->ToString();
	ServiceController::mapService.deleteSpot(UWPHelper::Platform_str_to_std_str(spotToDel));
	loadSpotData();
}

void BjfuGuide::BackStagePage::delRouteDialog_PrimaryButtonClick(Windows::UI::Xaml::Controls::ContentDialog ^ sender, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs ^ args)
{
	auto routeToDel = sender->Tag->ToString();
	auto str = UWPHelper::Platform_str_to_std_str(routeToDel);
	std::vector<std::string> dst;
	UWPHelper::StringSplit(dst, str, " ");
	if (dst.size() != 2)
	{
		return;
	}
	ServiceController::mapService.deleteRoute(dst[0], dst[1]);
	loadRouteData();
}