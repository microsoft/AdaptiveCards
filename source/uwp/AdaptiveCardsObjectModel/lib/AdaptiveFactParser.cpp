// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveFactParser.h"
#include "AdaptiveFactParser.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement AdaptiveFactParser::FromJson(
        winrt::Windows::Data::Json::JsonObject const&,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration const&,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration const&,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning> const&)
    {
        throw hresult_not_implemented();
    }
}
