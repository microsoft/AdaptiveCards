// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveExecuteActionParser.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
struct AdaptiveExecuteActionParser : AdaptiveExecuteActionParserT<AdaptiveExecuteActionParser>
{
    AdaptiveExecuteActionParser() = default;

    winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement FromJson(
        winrt::Windows::Data::Json::JsonObject const& inputJson,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration const& elementParsers,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration const& actionParsers,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning> const& warnings);
};
} // namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
struct AdaptiveExecuteActionParser : AdaptiveExecuteActionParserT<AdaptiveExecuteActionParser, implementation::AdaptiveExecuteActionParser>
{
};
} // namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
