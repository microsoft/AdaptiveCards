// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveHostConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct DECLSPEC_UUID("6A0EFDB7-AC1B-4C76-981E-2188297095AD") AdaptiveHostConfig
        : AdaptiveHostConfigT<AdaptiveHostConfig, ITypePeek>
    {
        AdaptiveHostConfig(::AdaptiveCards::HostConfig const& config = {});

        // IAdaptiveHostConfig
        property<hstring> FontFamily;
        property<Uwp::AdaptiveFontSizesConfig> FontSizes;
        property<Uwp::AdaptiveFontWeightsConfig> FontWeights;
        property<Uwp::AdaptiveFontTypesDefinition> FontTypes;
        property<bool> SupportsInteractivity;
        property<hstring> ImageBaseUrl;
        property<Uwp::AdaptiveContainerStylesDefinition> ContainerStyles;
        property<Uwp::AdaptiveImageSizesConfig> ImageSizes;
        property<Uwp::AdaptiveSpacingConfig> Spacing;
        property<Uwp::AdaptiveSeparatorConfig> Separator;
        property<Uwp::AdaptiveCardConfig> AdaptiveCard;
        property<Uwp::AdaptiveImageSetConfig> ImageSet;
        property<Uwp::AdaptiveImageConfig> Image;
        property<Uwp::AdaptiveFactSetConfig> FactSet;
        property<Uwp::AdaptiveActionsConfig> Actions;
        property<Uwp::AdaptiveMediaConfig> Media;
        property<Uwp::AdaptiveInputsConfig> Inputs;
        property<Uwp::AdaptiveTextBlockConfig> TextBlock;
        property<Uwp::AdaptiveTextStylesConfig> TextStyles;
        property<Uwp::AdaptiveTableConfig> Table;
        property<bool> OverflowMaxActions;
        property<hstring> OverflowButtonText;
        property<hstring> OverflowButtonAccessibilityText;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        // TODO: weird stuff here
        static Uwp::AdaptiveHostConfigParseResult FromJsonString(hstring const& hostConfigJson);
        static Uwp::AdaptiveHostConfigParseResult FromJson(winrt::JsonObject const& hostConfigJson);

    private:
        static Uwp::AdaptiveHostConfigParseResult _FromJsonString(const std::string& jsonString);
    };
}
namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveHostConfig : AdaptiveHostConfigT<AdaptiveHostConfig, implementation::AdaptiveHostConfig>
    {
    };
}
