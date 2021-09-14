// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveChoiceSetInput.h"
#include "AdaptiveChoiceSetInputParser.h"
#include "AdaptiveChoiceSetInputParser.g.cpp"
#include "AdaptiveElementParserRegistration.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement AdaptiveChoiceSetInputParser::FromJson(
        winrt::Windows::Data::Json::JsonObject const& inputJson,
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration const& elementParsers,
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionParserRegistration const& actionParsers,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning> const& warnings)
    {
        return ::AdaptiveCards::ObjectModel::WinUI3::FromJson<implementation::AdaptiveChoiceSetInput, ::AdaptiveCards::ChoiceSetInput, ::AdaptiveCards::ChoiceSetInputParser>(
                   inputJson, elementParsers, actionParsers, warnings)
            .as<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement>();
    }
}
