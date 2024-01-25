#include "pch.h"
#include "iostream"

using namespace winrt;
using namespace Windows::Foundation;

int main()
{
    init_apartment();

	//winrt::AdaptiveCards.Templating.CSharp.WinRT::AdaptiveCardTemplate
    winrt::hstring input{
        L"{\"type\": \"AdaptiveCard\",\"body\": [{\"type\": \"TextBlock\",\"text\": \"Hello, ${hi}!\"}]}"};
    winrt::AdaptiveCardsTemplatingCSharpWinRT::AdaptiveCardTemplate adaptiveCardTemplate{ input };

    winrt::hstring data{ L"{\"hi\": \"world\"}" };
    auto result = adaptiveCardTemplate.Expand(data);

    std::wcout << result.c_str() << std::endl;

    //AdaptiveCards.Templating.CSharp.WinRT::AdaptiveCardTemplate template{ L"{\"type\": \"AdaptiveCard\",\"body\": [{\"type\": \"TextBlock\",\"text\": \"Hello, World!\"}]}"};
};
