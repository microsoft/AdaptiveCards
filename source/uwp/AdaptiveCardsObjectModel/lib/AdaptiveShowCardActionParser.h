// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveShowCardActionParser.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    struct AdaptiveShowCardActionParser : AdaptiveShowCardActionParserT<AdaptiveShowCardActionParser>
    {
        AdaptiveShowCardActionParser() = default;

        winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement FromJson(
            winrt::Windows::Data::Json::JsonObject const& inputJson,
            winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration const& elementParsers,
            winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration const& actionParsers,
            winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning> const& warnings);
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Uwp::factory_implementation
{
    struct AdaptiveShowCardActionParser
        : AdaptiveShowCardActionParserT<AdaptiveShowCardActionParser, implementation::AdaptiveShowCardActionParser>
    {
    };
}
