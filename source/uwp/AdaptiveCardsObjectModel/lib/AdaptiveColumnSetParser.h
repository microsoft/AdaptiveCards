// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ColumnSet.h"
#include "AdaptiveColumnSetParser.g.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct AdaptiveColumnSetParser : AdaptiveColumnSetParserT<AdaptiveColumnSetParser>
    {
        AdaptiveColumnSetParser() = default;

        winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement FromJson(
            winrt::Windows::Data::Json::JsonObject const& inputJson,
            winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration const& elementParsers,
            winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionParserRegistration const& actionParsers,
            winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning> const& warnings);
    };
}
namespace winrt::AdaptiveCards::ObjectModel::WinUI3::factory_implementation
{
    struct AdaptiveColumnSetParser : AdaptiveColumnSetParserT<AdaptiveColumnSetParser, implementation::AdaptiveColumnSetParser>
    {
    };
}
