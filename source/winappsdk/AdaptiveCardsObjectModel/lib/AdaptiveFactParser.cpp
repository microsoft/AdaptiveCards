// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveFactParser.h"
#include "AdaptiveFactParser.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement AdaptiveFactParser::FromJson(
        winrt::Windows::Data::Json::JsonObject const&,
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration const&,
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionParserRegistration const&,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning> const&)
    {
        throw hresult_not_implemented();
    }
}
