// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ToggleInput.h"
#include "AdaptiveToggleInputParser.g.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct AdaptiveToggleInputParser : AdaptiveToggleInputParserT<AdaptiveToggleInputParser>
    {
        AdaptiveToggleInputParser() = default;

        winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement FromJson(
            winrt::Windows::Data::Json::JsonObject const& inputJson,
            winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration const& elementParsers,
            winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionParserRegistration const& actionParsers,
            winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning> const& warnings);
    };
}
namespace winrt::AdaptiveCards::ObjectModel::WinUI3::factory_implementation
{
    struct AdaptiveToggleInputParser : AdaptiveToggleInputParserT<AdaptiveToggleInputParser, implementation::AdaptiveToggleInputParser>
    {
    };
}
