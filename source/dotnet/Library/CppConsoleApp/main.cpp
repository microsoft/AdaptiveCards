// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"
#include "iostream"

using namespace winrt;
using namespace Windows::Foundation;

// Sample Test App for AdaptiveCards.Template project which is a C#/WinRT component
int main()
{
    init_apartment();

    winrt::hstring input{
        L"{\"type\": \"AdaptiveCard\",\"body\": [{\"type\": \"TextBlock\",\"text\": \"Hello, ${hi}!\"}]}"};

    winrt::AdaptiveCards::Template::AdaptiveCardTemplate adaptiveCardTemplate{ input };

    winrt::hstring data{ L"{\"hi\": \"world\"}" };
    auto result = adaptiveCardTemplate.Expand(data);

    std::cout << "Expanded: " << winrt::to_string(result) << std::endl;
};
