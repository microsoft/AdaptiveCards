// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveToggleInput.h"
#include "AdaptiveToggleInputParser.h"
#include "AdaptiveToggleInputParser.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement AdaptiveToggleInputParser::FromJson(
        winrt::Windows::Data::Json::JsonObject const& inputJson,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration const& elementParsers,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration const& actionParsers,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning> const& warnings)
    {
        return ::AdaptiveCards::ObjectModel::Uwp::FromJson<implementation::AdaptiveToggleInput, ::AdaptiveCards::ToggleInput, ::AdaptiveCards::ToggleInputParser>(
                   inputJson, elementParsers, actionParsers, warnings)
            .as<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement>();
    }
}
