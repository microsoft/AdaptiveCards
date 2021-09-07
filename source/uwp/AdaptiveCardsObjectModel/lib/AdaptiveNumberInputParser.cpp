// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveNumberInput.h"
#include "AdaptiveNumberInputParser.h"
#include "AdaptiveNumberInputParser.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement AdaptiveNumberInputParser::FromJson(
        winrt::Windows::Data::Json::JsonObject const& inputJson,
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration const& elementParsers,
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionParserRegistration const& actionParsers,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning> const& warnings)
    {
        return ::AdaptiveCards::ObjectModel::WinUI3::FromJson<implementation::AdaptiveNumberInput, ::AdaptiveCards::NumberInput, ::AdaptiveCards::NumberInputParser>(
                   inputJson, elementParsers, actionParsers, warnings)
            .as<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement>();
    }
}
