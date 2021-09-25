// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TimeInput.h"
#include "AdaptiveTimeInputParser.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct AdaptiveTimeInputParser : AdaptiveTimeInputParserT<AdaptiveTimeInputParser>
    {
        AdaptiveTimeInputParser() = default;

        winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement FromJson(
            winrt::Windows::Data::Json::JsonObject const& inputJson,
            winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration const& elementParsers,
            winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration const& actionParsers,
            winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning> const& warnings);
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveTimeInputParser : AdaptiveTimeInputParserT<AdaptiveTimeInputParser, implementation::AdaptiveTimeInputParser>
    {
    };
}
