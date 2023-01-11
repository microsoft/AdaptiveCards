// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveTextInput.h"
#include "AdaptiveTextInputParser.h"
#include "AdaptiveTextInputParser.g.cpp"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveCardElement AdaptiveTextInputParser::FromJson(
        winrt::Windows::Data::Json::JsonObject const& inputJson,
        winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveElementParserRegistration const& elementParsers,
        winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveActionParserRegistration const& actionParsers,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveWarning> const& warnings)
    {
        return ::AdaptiveCards::ObjectModel::Xaml_OM::FromJson<implementation::AdaptiveTextInput, ::AdaptiveCards::TextInput, ::AdaptiveCards::TextInputParser>(
                   inputJson, elementParsers, actionParsers, warnings)
            .as<winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveCardElement>();
    }
}
