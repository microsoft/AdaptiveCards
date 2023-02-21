// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveActionSetParser.h"
#include "AdaptiveActionSetParser.g.cpp"

#include "AdaptiveActionSet.h"
#include "AdaptiveElementParserRegistration.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveCardElement AdaptiveActionSetParser::FromJson(
        winrt::Windows::Data::Json::JsonObject const& inputJson,
        winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveElementParserRegistration const& elementParsers,
        winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveActionParserRegistration const& actionParsers,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveWarning> const& warnings)
    {
        return ::AdaptiveCards::ObjectModel::Xaml_OM::FromJson<implementation::AdaptiveActionSet, ::AdaptiveCards::ActionSet, ::AdaptiveCards::ActionSetParser>(
            inputJson, elementParsers, actionParsers, warnings).as<winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveCardElement>();
    }
}
