#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace AdaptiveCards::ObjectModel::WinUI3;
using namespace AdaptiveCards::Rendering::WinUI3;

namespace winrt::BlankApp1::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();

        winrt::hstring k{ L"{ \n    \"type\": \"AdaptiveCard\",\n \"rtl\":false,\n    \"speak\": \"testing weather\",\n    \"body\": [\n        {\n            \"type\": \"ColumnSet\",\n            \"columns\": [\n                {\n                    \"type\": \"Column\",\n                    \"width\": \"120px\",\n                    \"minHeight\": \"100px\",\n                    \"backgroundImage\": {\n                        \"url\": \"https://cdn1.iconfinder.com/data/icons/weather-elements/512/Weather_SunGradient.png\"\n                    },\n                    \"items\": [\n                        {\n                            \"type\": \"Container\",\n                            \"items\": [\n                                {\n                                    \"type\": \"TextBlock\",\n                                    \"id\": \"smallTickerText\",\n                                    \"text\": \"78°F\",\n                                    \"horizontalAlignment\": \"Right\",\n                                    \"fontType\": \"Default\",\n                                    \"weight\": \"Default\"\n                                }\n                            ],\n                            \"id\": \"smallContainer\",\n                            \"minHeight\": \"10px\",\n                            \"verticalContentAlignment\": \"Top\",\n                            \"spacing\": \"None\",\n                            \"horizontalAlignment\": \"Right\",\n                            \"style\": \"accent\"\n                        }\n                    ],\n                    \"horizontalAlignment\": \"Left\",\n                    \"spacing\": \"None\",\n                    \"height\": \"stretch\"\n                },\n                {\n                    \"type\": \"Column\",\n                    \"items\": [\n                        {\n                            \"type\": \"TextBlock\",\n                            \"text\": \"73°F\",\n                            \"id\": \"largeTickerText1\"\n                        },\n                        {\n                            \"type\": \"TextBlock\",\n                            \"text\": \"Light showers\",\n                            \"id\": \"largeTickerText2\"\n                        }\n                    ],\n                    \"width\": \"stretch\"\n                }\n            ],\n            \"spacing\": \"None\",\n            \"separator\": true\n        }\n    ],\n    \"actions\": [\n        {\n            \"type\": \"Action.ToggleVisibility\",\n            \"targetElements\": [\n                {\n                    \"elementId\": \"smallTickerText\",\n                    \"isVisible\": true\n                },\n                {\n                    \"elementId\": \"smallContainer\",\n                    \"isVisible\": true\n                },\n                {\n                    \"elementId\": \"largeTickerText1\",\n                    \"isVisible\": false\n                },\n                {\n                    \"elementId\": \"largeTickerText2\",\n                    \"isVisible\": false\n                }\n            ],\n            \"id\": \"smallTickerAction\",\n            \"title\": \"ShowSmallTicker\",\n            \"style\": \"positive\"\n        },\n        {\n            \"type\": \"Action.ToggleVisibility\",\n            \"targetElements\": [\n                {\n                    \"elementId\": \"smallTickerText\",\n                    \"isVisible\": false\n                },\n                {\n                    \"elementId\": \"smallContainer\",\n                    \"isVisible\": false\n                },\n                {\n                    \"elementId\": \"largeTickerText1\",\n                    \"isVisible\": true\n                },\n                {\n                    \"elementId\": \"largeTickerText2\",\n                    \"isVisible\": true\n                }\n            ],\n            \"id\": \"largeTickerAction\",\n            \"title\": \"ShowLargeTicker\",\n            \"style\": \"positive\"\n        }\n    ],\n    \"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\",\n    \"version\": \"1.3\"\n}" };

        //winrt::hstring  k{ L"{\r\n    \"type\": \"AdaptiveCard\",\r\n    \"body\": [\r\n        {\r\n            \"type\": \"TextBlock\",\r\n            \"size\": \"large\",\r\n            \"weight\": \"bolder\",\r\n            \"text\": \"title\"\r\n        }\r\n    ],\r\n    \"$schema\": \"http:\/\/adaptivecards.io\/schemas\/adaptive-card.json\",\r\n    \"version\": \"1.5\"\r\n}" };
        AdaptiveCardRenderer r{};
        auto m = AdaptiveCard::FromJsonString(k);
        auto sss = r.RenderAdaptiveCard(m.AdaptiveCard());
        if (sss.FrameworkElement() != nullptr)
        {
            myStack().Children().Append(sss.FrameworkElement());
        }
    }

    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

   /* void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }*/
}
