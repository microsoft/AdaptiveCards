// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRichTextBlock.h"
#include "AdaptiveRichTextBlockParser.h"
#include "AdaptiveRichTextBlockParser.g.cpp"
#include "AdaptiveElementParserRegistration.h"

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement AdaptiveRichTextBlockParser::FromJson(
        winrt::Windows::Data::Json::JsonObject const& inputJson,
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveElementParserRegistration const& elementParsers,
        winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveActionParserRegistration const& actionParsers,
        winrt::Windows::Foundation::Collections::IVector<winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning> const& warnings)
    {
        return ::AdaptiveCards::ObjectModel::WinUI3::FromJson<implementation::AdaptiveRichTextBlock, ::AdaptiveCards::RichTextBlock, ::AdaptiveCards::RichTextBlockParser>(
                   inputJson, elementParsers, actionParsers, warnings)
            .as<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement>();
    }
}
