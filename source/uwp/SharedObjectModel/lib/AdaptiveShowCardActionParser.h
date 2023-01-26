// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveShowCardActionParser.g.h"

namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::implementation
{
    struct AdaptiveShowCardActionParser : AdaptiveShowCardActionParserT<AdaptiveShowCardActionParser>
    {
        AdaptiveShowCardActionParser() = default;

        winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveActionElement FromJson(
            winrt::Windows::Data::Json::JsonObject const& inputJson,
            winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveElementParserRegistration const& elementParsers,
            winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveActionParserRegistration const& actionParsers,
            winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Xaml_OM::AdaptiveWarning> const& warnings);
    };
}
namespace winrt::AdaptiveCards::ObjectModel::Xaml_OM::factory_implementation
{
    struct AdaptiveShowCardActionParser
        : AdaptiveShowCardActionParserT<AdaptiveShowCardActionParser, implementation::AdaptiveShowCardActionParser>
    {
    };
}
