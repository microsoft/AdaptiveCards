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
        property<winrt::render_xaml::AdaptiveFontSizesConfig> FontSizes;
        property<winrt::render_xaml::AdaptiveFontWeightsConfig> FontWeights;
        property<winrt::render_xaml::AdaptiveFontTypesDefinition> FontTypes;
        property<bool> SupportsInteractivity;
        property<hstring> ImageBaseUrl;
        property<winrt::render_xaml::AdaptiveContainerStylesDefinition> ContainerStyles;
        property<winrt::render_xaml::AdaptiveImageSizesConfig> ImageSizes;
        property<winrt::render_xaml::AdaptiveSpacingConfig> Spacing;
        property<winrt::render_xaml::AdaptiveSeparatorConfig> Separator;
        property<winrt::render_xaml::AdaptiveCardConfig> AdaptiveCard;
        property<winrt::render_xaml::AdaptiveImageSetConfig> ImageSet;
        property<winrt::render_xaml::AdaptiveImageConfig> Image;
        property<winrt::render_xaml::AdaptiveFactSetConfig> FactSet;
        property<winrt::render_xaml::AdaptiveActionsConfig> Actions;
        property<winrt::render_xaml::AdaptiveMediaConfig> Media;
        property<winrt::render_xaml::AdaptiveInputsConfig> Inputs;
        property<winrt::render_xaml::AdaptiveTextBlockConfig> TextBlock;
        property<winrt::render_xaml::AdaptiveTextStylesConfig> TextStyles;
        property<winrt::render_xaml::AdaptiveTableConfig> Table;
        property<bool> OverflowMaxActions;
        property<hstring> OverflowButtonText;
        property<hstring> OverflowButtonAccessibilityText;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        static winrt::render_xaml::AdaptiveHostConfigParseResult FromJsonString(hstring const& hostConfigJson);
        static winrt::render_xaml::AdaptiveHostConfigParseResult FromJson(winrt::JsonObject const& hostConfigJson);

    private:
        static winrt::render_xaml::AdaptiveHostConfigParseResult _FromJsonString(const std::string& jsonString);
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveHostConfig : AdaptiveHostConfigT<AdaptiveHostConfig, implementation::AdaptiveHostConfig>
    {
    };
}
