// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveHostConfig.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct DECLSPEC_UUID("6A0EFDB7-AC1B-4C76-981E-2188297095AD") AdaptiveHostConfig
        : AdaptiveHostConfigT<AdaptiveHostConfig, ITypePeek>
    {
        AdaptiveHostConfig(::AdaptiveCards::HostConfig const& config = {});

        // IAdaptiveHostConfig
        property<hstring> FontFamily;
        property<WinUI3::AdaptiveFontSizesConfig> FontSizes;
        property<WinUI3::AdaptiveFontWeightsConfig> FontWeights;
        property<WinUI3::AdaptiveFontTypesDefinition> FontTypes;
        property<bool> SupportsInteractivity;
        property<hstring> ImageBaseUrl;
        property<WinUI3::AdaptiveContainerStylesDefinition> ContainerStyles;
        property<WinUI3::AdaptiveImageSizesConfig> ImageSizes;
        property<WinUI3::AdaptiveSpacingConfig> Spacing;
        property<WinUI3::AdaptiveSeparatorConfig> Separator;
        property<WinUI3::AdaptiveCardConfig> AdaptiveCard;
        property<WinUI3::AdaptiveImageSetConfig> ImageSet;
        property<WinUI3::AdaptiveImageConfig> Image;
        property<WinUI3::AdaptiveFactSetConfig> FactSet;
        property<WinUI3::AdaptiveActionsConfig> Actions;
        property<WinUI3::AdaptiveMediaConfig> Media;
        property<WinUI3::AdaptiveInputsConfig> Inputs;
        property<WinUI3::AdaptiveTextBlockConfig> TextBlock;
        property<WinUI3::AdaptiveTextStylesConfig> TextStyles;
        property<WinUI3::AdaptiveTableConfig> Table;
        property<bool> OverflowMaxActions;
        property<hstring> OverflowButtonText;
        property<hstring> OverflowButtonAccessibilityText;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        // TODO: weird stuff here
        static WinUI3::AdaptiveHostConfigParseResult FromJsonString(hstring const& hostConfigJson);
        static WinUI3::AdaptiveHostConfigParseResult FromJson(winrt::Windows::Data::Json::JsonObject const& hostConfigJson);

    private:
        static WinUI3::AdaptiveHostConfigParseResult _FromJsonString(const std::string& jsonString);
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveHostConfig : AdaptiveHostConfigT<AdaptiveHostConfig, implementation::AdaptiveHostConfig>
    {
    };
}
