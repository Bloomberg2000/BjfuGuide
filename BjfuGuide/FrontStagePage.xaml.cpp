//
// FrontStagePage.xaml.cpp
// FrontStagePage 类的实现
//

#include "pch.h"
#include "FrontStagePage.xaml.h"
#include "MainPage.xaml.h"
#include "ServiceController.h"
#include "Util/UWPHelper.h"
#include "Library/Stack.h"

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

FrontStagePage::FrontStagePage()
{
	InitializeComponent();
}


void BjfuGuide::FrontStagePage::RadioButton_Checked(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	auto rb = dynamic_cast<RadioButton^>(sender);
	auto searchType = rb->Tag->ToString();
	if (searchType == "searchByName")
	{
		SearchBar->PlaceholderText = "请输入要查询的景点名称";
		SearchType = "searchByName";
	}
	if (searchType == "searchByFunction")
	{
		SearchBar->PlaceholderText = "请输入要查询的功能";
		SearchType = "searchByFunction";
	}

}


void BjfuGuide::FrontStagePage::SearchBar_TextChanged(Windows::UI::Xaml::Controls::AutoSuggestBox^ sender, Windows::UI::Xaml::Controls::AutoSuggestBoxTextChangedEventArgs^ args)
{
	if (args->Reason == AutoSuggestionBoxTextChangeReason::UserInput) {

	}
}


void BjfuGuide::FrontStagePage::SearchBar_QuerySubmitted(Windows::UI::Xaml::Controls::AutoSuggestBox^ sender, Windows::UI::Xaml::Controls::AutoSuggestBoxQuerySubmittedEventArgs^ args)
{
	auto userInput = args->QueryText;
	SearchResultText->Children->Clear();
	TextBlock^ newTextBlock;
	if (SearchType == "searchByName")
	{
		auto resultArr = ServiceController::mapService.getSpotInfoByName(Structure::String(UWPHelper::Platform_str_to_std_str(userInput)));
		for (int i = 0; i < resultArr.size(); i++)
		{
			std::string temp = resultArr[i].get_name().cpp_str() + " " + resultArr[i].get_info().cpp_str();
			newTextBlock = ref new TextBlock();
			newTextBlock->Text = UWPHelper::std_str_To_Platform_Str(temp);
			newTextBlock->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
			SearchResultText->Children->Append(newTextBlock);
		}
		if (resultArr.size() == 0)
		{
			newTextBlock = ref new TextBlock();
			newTextBlock->Text = "未找到" + userInput + "相关信息";
			newTextBlock->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
			SearchResultText->Children->Append(newTextBlock);
		}
		SearchResult->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
	if (SearchType == "searchByFunction")
	{
		auto resultArr = ServiceController::mapService.getSpotListByFunction(Structure::String(UWPHelper::Platform_str_to_std_str(userInput)));
		for (int i = 0; i < resultArr.size(); i++)
		{
			std::string temp = resultArr[i].get_name().cpp_str() + " " + resultArr[i].get_info().cpp_str();
			newTextBlock = ref new TextBlock();
			newTextBlock->Text = UWPHelper::std_str_To_Platform_Str(temp);
			newTextBlock->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
			SearchResultText->Children->Append(newTextBlock);
		}
		if (resultArr.size() == 0)
		{
			newTextBlock = ref new TextBlock();
			newTextBlock->Text = "未找到" + userInput + "相关信息";
			newTextBlock->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
			SearchResultText->Children->Append(newTextBlock);
		}
		SearchResult->Visibility = Windows::UI::Xaml::Visibility::Visible;
	}
}


void BjfuGuide::FrontStagePage::SearchBar_SuggestionChosen(Windows::UI::Xaml::Controls::AutoSuggestBox^ sender, Windows::UI::Xaml::Controls::AutoSuggestBoxSuggestionChosenEventArgs^ args)
{

}


void BjfuGuide::FrontStagePage::GetRoute_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	ShortestPathResultText->Children->Clear();
	AllPathResultText->Children->Clear();

	auto startPos = startPoint->Text;
	auto endPos = endPoint->Text;
	auto startPosName = Structure::String(UWPHelper::Platform_str_to_std_str(startPos));
	auto endPosName = Structure::String(UWPHelper::Platform_str_to_std_str(endPos));
	int shortestlength = 0;
	auto shortestPath = ServiceController::mapService.getShortestPath(startPosName, endPosName, shortestlength);

	TextBlock^ newTextBlock;
	String^ shortestPathResultText = "全长" + (shortestlength == INT_MAX ? 0 : shortestlength) + "米";

	newTextBlock = ref new TextBlock();
	newTextBlock->Text = shortestPathResultText;
	newTextBlock->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
	ShortestPathResultText->Children->Append(newTextBlock);

	shortestPathResultText = "";
	while (!shortestPath.empty())
	{
		shortestPathResultText += (UWPHelper::std_str_To_Platform_Str(shortestPath.pop().get_name().cpp_str()) + " ");
	}
	ShortestPathResult->Visibility = Windows::UI::Xaml::Visibility::Visible;

	newTextBlock = ref new TextBlock();
	newTextBlock->Text = shortestPathResultText;
	ShortestPathResultText->Children->Append(newTextBlock);

	auto temp = ServiceController::mapService.getAllPath(startPosName, endPosName);

	String^ allPathResultText = "共" + temp.size() + "条路径";
	newTextBlock = ref new TextBlock();
	newTextBlock->Text = allPathResultText;
	newTextBlock->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
	AllPathResultText->Children->Append(newTextBlock);

	for (int i = 0; i < temp.size(); i++) {
		allPathResultText = "";
		Structure::Vector<ScenicSpot> test = temp[i];
		for (int j = 0; j < test.size(); j++) {
			allPathResultText += (UWPHelper::std_str_To_Platform_Str(test[j].get_name().cpp_str()) + " ");
		}
		newTextBlock = ref new TextBlock();
		newTextBlock->Text = allPathResultText;
		newTextBlock->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
		AllPathResultText->Children->Append(newTextBlock);
	}
	AllPathResult->Visibility = Windows::UI::Xaml::Visibility::Visible;
}



void BjfuGuide::FrontStagePage::DesignRoute_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	RouteDesignText->Children->Clear();
	String^ ResultText = "需要铺设的线路有：";
	TextBlock^ newTextBlock;
	newTextBlock = ref new TextBlock();
	newTextBlock->Text = ResultText;
	newTextBlock->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
	RouteDesignText->Children->Append(newTextBlock);

	auto _bjfuMap = ServiceController::mapService.OptimalRouteDesign();
	for (int i = 0; i < _bjfuMap->vNum; i++) {
		for (int j = 0; j < _bjfuMap->vNum; j++) {
			if (_bjfuMap->exists(i, j) && _bjfuMap->type(i, j) == Structure::TREE) {
				ResultText = "";
				ResultText += ("从" + UWPHelper::std_str_To_Platform_Str(_bjfuMap->vertex(i).get_name().cpp_str()) +
					"至" + UWPHelper::std_str_To_Platform_Str(_bjfuMap->vertex(j).get_name().cpp_str()) +
					"，线路长度为" + _bjfuMap->edge(i, j).get_routeLength() + "米");
				newTextBlock = ref new TextBlock();
				newTextBlock->Text = ResultText;
				newTextBlock->TextWrapping = Windows::UI::Xaml::TextWrapping::Wrap;
				RouteDesignText->Children->Append(newTextBlock);
			}
		}
	}
	RouteDesignResult->Visibility = Windows::UI::Xaml::Visibility::Visible;
}
