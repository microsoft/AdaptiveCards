// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageParser.h"
#include "AdaptiveImageParser.g.cpp"

#include "AdaptiveElementParserRegistration.h"
#include "AdaptiveImage.h"

namespace winrt::AdaptiveCards::ObjectModel::Uwp::implementation
{
    winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement AdaptiveImageParser::FromJson(
        winrt::Windows::Data::Json::JsonObject const& inputJson,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveElementParserRegistration const& elementParsers,
        winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveActionParserRegistration const& actionParsers,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning> const& warnings)
    {
        return ::AdaptiveCards::ObjectModel::Uwp::FromJson<implementation::AdaptiveImage, ::AdaptiveCards::Image, ::AdaptiveCards::ImageParser>(
                   inputJson, elementParsers, actionParsers, warnings)
            .as<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement>();
    }
}
