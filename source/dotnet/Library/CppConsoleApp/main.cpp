// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;

// Sample Test App for AdaptiveCards.Template project which is a C#/WinRT component
int main()
{
    init_apartment();

    hstring input{
        L"{\"type\": \"AdaptiveCard\",\"body\": [{\"type\": \"TextBlock\",\"text\": \"Hello, ${hi}!\"}]}"};

    AdaptiveCards::Template::AdaptiveCardTemplate adaptiveCardTemplate{ input };

    hstring data{ L"{\"hi\": \"world\"}" };
    auto result = adaptiveCardTemplate.Expand(data);

    std::cout << "Expanded: " << to_string(result) << std::endl;

    return 0;
};
