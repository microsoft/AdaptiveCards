// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveActionsConfig.h"
#include "AdaptiveCardConfig.h"
#include "AdaptiveColorsConfig.h"
#include "AdaptiveContainerStylesDefinition.h"
#include "AdaptiveFactSetConfig.h"
#include "AdaptiveFontSizesConfig.h"
#include "AdaptiveFontTypeDefinition.h"
#include "AdaptiveFontTypesDefinition.h"
#include "AdaptiveFontWeightsConfig.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveHostConfigParseResult.h"
#include "AdaptiveImageConfig.h"
#include "AdaptiveImageSetConfig.h"
#include "AdaptiveImageSizesConfig.h"
#include "AdaptiveInputsConfig.h"
#include "AdaptiveMediaConfig.h"
#include "AdaptiveSeparatorConfig.h"
#include "AdaptiveSpacingConfig.h"
#include "AdaptiveTableConfig.h"
#include "AdaptiveTextBlockConfig.h"
#include "AdaptiveTextStylesConfig.h"
#include "AdaptiveHostConfig.g.cpp"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    winrt::AdaptiveHostConfigParseResult AdaptiveHostConfig::FromJsonString(hstring const& hostConfigJson)
    {
        std::string adaptiveJsonString = HStringToUTF8(hostConfigJson);
        return AdaptiveHostConfig::_FromJsonString(adaptiveJsonString);
    }

    winrt::AdaptiveHostConfigParseResult AdaptiveHostConfig::FromJson(winrt::JsonObject const& hostConfigJson)
    {
        std::string adaptiveJsonString = JsonObjectToString(hostConfigJson);
        return AdaptiveHostConfig::_FromJsonString(adaptiveJsonString);
    }

    winrt::AdaptiveHostConfigParseResult AdaptiveHostConfig::_FromJsonString(std::string const& adaptiveJson)
    {
        auto sharedHostConfig = ::AdaptiveCards::HostConfig::DeserializeFromString(adaptiveJson);
        auto parseResult = winrt::make<implementation::AdaptiveHostConfig>(sharedHostConfig);
        return winrt::make<implementation::AdaptiveHostConfigParseResult>(parseResult);
    }

    AdaptiveHostConfig::AdaptiveHostConfig(::AdaptiveCards::HostConfig const& sharedHostConfig) :
        SupportsInteractivity{sharedHostConfig.GetSupportsInteractivity()}, FontFamily{UTF8ToHString(sharedHostConfig.GetFontFamily())},
        ImageBaseUrl{UTF8ToHString(sharedHostConfig.GetImageBaseUrl())}, FontSizes{winrt::make<implementation::AdaptiveFontSizesConfig>(
                                                                             sharedHostConfig.GetFontSizes())},
        FontWeights{winrt::make<implementation::AdaptiveFontWeightsConfig>(sharedHostConfig.GetFontWeights())},
        FontTypes{winrt::make<implementation::AdaptiveFontTypesDefinition>(sharedHostConfig.GetFontTypes())},
        ContainerStyles{winrt::make<implementation::AdaptiveContainerStylesDefinition>(sharedHostConfig.GetContainerStyles())},
        ImageSizes{winrt::make<implementation::AdaptiveImageSizesConfig>(sharedHostConfig.GetImageSizes())},
        Spacing{winrt::make<implementation::AdaptiveSpacingConfig>(sharedHostConfig.GetSpacing())},
        Separator{winrt::make<implementation::AdaptiveSeparatorConfig>(sharedHostConfig.GetSeparator())},
        AdaptiveCard{winrt::make<implementation::AdaptiveCardConfig>(sharedHostConfig.GetAdaptiveCard())},
        ImageSet{winrt::make<implementation::AdaptiveImageSetConfig>(sharedHostConfig.GetImageSet())},
        FactSet{winrt::make<implementation::AdaptiveFactSetConfig>(sharedHostConfig.GetFactSet())},
        Actions{winrt::make<implementation::AdaptiveActionsConfig>(sharedHostConfig.GetActions())},
        Image{winrt::make<implementation::AdaptiveImageConfig>(sharedHostConfig.GetImage())},
        Media{winrt::make<implementation::AdaptiveMediaConfig>(sharedHostConfig.GetMedia())},
        Inputs{winrt::make<implementation::AdaptiveInputsConfig>(sharedHostConfig.GetInputs())},
        TextBlock{winrt::make<implementation::AdaptiveTextBlockConfig>(sharedHostConfig.GetTextBlock())},
        TextStyles{winrt::make<implementation::AdaptiveTextStylesConfig>(sharedHostConfig.GetTextStyles())},
        Table{winrt::make<implementation::AdaptiveTableConfig>(sharedHostConfig.GetTable())}, OverflowMaxActions{false},
        OverflowButtonText{L"..."}, OverflowButtonAccessibilityText{L"More Actions"}
    {
    }
}
