// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveExecuteAction.h"
#include "AdaptiveExecuteActionParser.h"
#include "AdaptiveExecuteActionParser.g.cpp"
#include "AdaptiveElementParserRegistration.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveActionElement AdaptiveExecuteActionParser::FromJson(
        winrt::Windows::Data::Json::JsonObject const& inputJson,
        winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveElementParserRegistration const& elementParsers,
        winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveActionParserRegistration const& actionParsers,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveWarning> const& warnings)
    {
        return ::AdaptiveCards::ObjectModel::Xaml_OM::FromJson<implementation::AdaptiveExecuteAction, ::AdaptiveCards::ExecuteAction, ::AdaptiveCards::ExecuteActionParser>(
                   inputJson, elementParsers, actionParsers, warnings)
            .as<winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveActionElement>();
    }
}
