// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveHostConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct DECLSPEC_UUID("6A0EFDB7-AC1B-4C76-981E-2188297095AD") AdaptiveHostConfig
        : AdaptiveHostConfigT<AdaptiveHostConfig, ITypePeek>
    {
        AdaptiveHostConfig(::AdaptiveCards::HostConfig const& config = {});

        // IAdaptiveHostConfig
        property<hstring> FontFamily;
        property<winrt::AdaptiveFontSizesConfig> FontSizes;
        property<winrt::AdaptiveFontWeightsConfig> FontWeights;
        property<winrt::AdaptiveFontTypesDefinition> FontTypes;
        property<bool> SupportsInteractivity;
        property<hstring> ImageBaseUrl;
        property<winrt::AdaptiveContainerStylesDefinition> ContainerStyles;
        property<winrt::AdaptiveImageSizesConfig> ImageSizes;
        property<winrt::AdaptiveSpacingConfig> Spacing;
        property<winrt::AdaptiveSeparatorConfig> Separator;
        property<winrt::AdaptiveCardConfig> AdaptiveCard;
        property<winrt::AdaptiveImageSetConfig> ImageSet;
        property<winrt::AdaptiveImageConfig> Image;
        property<winrt::AdaptiveFactSetConfig> FactSet;
        property<winrt::AdaptiveActionsConfig> Actions;
        property<winrt::AdaptiveMediaConfig> Media;
        property<winrt::AdaptiveInputsConfig> Inputs;
        property<winrt::AdaptiveTextBlockConfig> TextBlock;
        property<winrt::AdaptiveTextStylesConfig> TextStyles;
        property<winrt::AdaptiveTableConfig> Table;
        property<bool> OverflowMaxActions;
        property<hstring> OverflowButtonText;
        property<hstring> OverflowButtonAccessibilityText;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        static winrt::AdaptiveHostConfigParseResult FromJsonString(hstring const& hostConfigJson);
        static winrt::AdaptiveHostConfigParseResult FromJson(winrt::JsonObject const& hostConfigJson);

    private:
        static winrt::AdaptiveHostConfigParseResult _FromJsonString(const std::string& jsonString);
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveHostConfig : AdaptiveHostConfigT<AdaptiveHostConfig, implementation::AdaptiveHostConfig>
    {
    };
}
