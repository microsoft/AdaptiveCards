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
#include "AdaptiveMediaConfig.h"
#include "AdaptiveSeparatorConfig.h"
#include "AdaptiveSpacingConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveHostConfigStaticsImpl::FromJsonString(_In_ HSTRING adaptiveJson,
                                                          _COM_Outptr_ IAdaptiveHostConfigParseResult** parseResult) noexcept
    try
    {
        *parseResult = nullptr;

        std::string adaptiveJsonString;
        RETURN_IF_FAILED(HStringToUTF8(adaptiveJson, adaptiveJsonString));
        return _FromJsonString(adaptiveJsonString, parseResult);
    }
    CATCH_RETURN;

    HRESULT AdaptiveHostConfigStaticsImpl::FromJson(_In_ IJsonObject* adaptiveJson,
                                                    _COM_Outptr_ IAdaptiveHostConfigParseResult** parseResult) noexcept
    try
    {
        *parseResult = nullptr;

        std::string adaptiveJsonString;
        RETURN_IF_FAILED(JsonObjectToString(adaptiveJson, adaptiveJsonString));

        return _FromJsonString(adaptiveJsonString, parseResult);
    }
    CATCH_RETURN;

    HRESULT AdaptiveHostConfigStaticsImpl::_FromJsonString(const std::string& jsonString,
                                                           _COM_Outptr_ IAdaptiveHostConfigParseResult** parseResult)
    {
        HostConfig sharedHostConfig = HostConfig::DeserializeFromString(jsonString);

        ComPtr<IAdaptiveHostConfig> config;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveHostConfig>(&config, sharedHostConfig));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveHostConfigParseResult>(parseResult, config.Get()));

        return S_OK;
    }

    HRESULT AdaptiveHostConfig::RuntimeClassInitialize() noexcept
    try
    {
        HostConfig sharedHostConfig;
        return RuntimeClassInitialize(sharedHostConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveHostConfig::RuntimeClassInitialize(const HostConfig& sharedHostConfig)
    {
        m_supportsInteractivity = sharedHostConfig.GetSupportsInteractivity();
        RETURN_IF_FAILED(UTF8ToHString(sharedHostConfig.GetFontFamily(), m_fontFamily.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(sharedHostConfig.GetImageBaseUrl(), m_imageBaseUrl.GetAddressOf()));

        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontSizesConfig>(m_fontSizes.GetAddressOf(), sharedHostConfig.GetFontSizes()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontWeightsConfig>(m_fontWeights.GetAddressOf(),
                                                                      sharedHostConfig.GetFontWeights()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontTypesDefinition>(m_fontTypes.GetAddressOf(), sharedHostConfig.GetFontTypes()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveContainerStylesDefinition>(m_containerStyles.GetAddressOf(),
                                                                              sharedHostConfig.GetContainerStyles()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveImageSizesConfig>(m_imageSizes.GetAddressOf(), sharedHostConfig.GetImageSizes()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveSpacingConfig>(m_spacing.GetAddressOf(), sharedHostConfig.GetSpacing()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveSeparatorConfig>(m_separator.GetAddressOf(), sharedHostConfig.GetSeparator()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCardConfig>(m_adaptiveCard.GetAddressOf(), sharedHostConfig.GetAdaptiveCard()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveImageSetConfig>(m_imageSet.GetAddressOf(), sharedHostConfig.GetImageSet()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFactSetConfig>(m_factSet.GetAddressOf(), sharedHostConfig.GetFactSet()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveActionsConfig>(m_actions.GetAddressOf(), sharedHostConfig.GetActions()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveImageConfig>(m_image.GetAddressOf(), sharedHostConfig.GetImage()));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveMediaConfig>(m_media.GetAddressOf(), sharedHostConfig.GetMedia()));

        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_FontFamily(_Outptr_ HSTRING* text) { return m_fontFamily.CopyTo(text); }

    HRESULT AdaptiveHostConfig::put_FontFamily(_In_ HSTRING text) { return m_fontFamily.Set(text); }

    HRESULT AdaptiveHostConfig::get_FontSizes(_COM_Outptr_ IAdaptiveFontSizesConfig** fontSizesConfig)
    {
        return m_fontSizes.CopyTo(fontSizesConfig);
    }

    HRESULT AdaptiveHostConfig::put_FontSizes(_In_ IAdaptiveFontSizesConfig* fontSizes)
    {
        m_fontSizes = fontSizes;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_FontWeights(_COM_Outptr_ IAdaptiveFontWeightsConfig** fontWeightsConfig)
    {
        return m_fontWeights.CopyTo(fontWeightsConfig);
    }

    HRESULT AdaptiveHostConfig::put_FontWeights(_In_ IAdaptiveFontWeightsConfig* fontWeights)
    {
        m_fontWeights = fontWeights;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_SupportsInteractivity(_Out_ boolean* supportsInteractivity)
    {
        *supportsInteractivity = m_supportsInteractivity;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::put_SupportsInteractivity(boolean supportsInteractivity)
    {
        m_supportsInteractivity = supportsInteractivity;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_ImageBaseUrl(_Outptr_ HSTRING* imageBaseUrl)
    {
        return m_imageBaseUrl.CopyTo(imageBaseUrl);
    }

    HRESULT AdaptiveHostConfig::put_ImageBaseUrl(_In_ HSTRING imageBaseUrl) { return m_imageBaseUrl.Set(imageBaseUrl); }

    HRESULT AdaptiveHostConfig::get_ContainerStyles(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveContainerStylesDefinition** value)
    {
        return m_containerStyles.CopyTo(value);
    }

    HRESULT AdaptiveHostConfig::put_ContainerStyles(_In_ ABI::AdaptiveNamespace::IAdaptiveContainerStylesDefinition* containerStylesDefinition)
    {
        m_containerStyles = containerStylesDefinition;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_ImageSizes(_COM_Outptr_ IAdaptiveImageSizesConfig** imageSizes)
    {
        return m_imageSizes.CopyTo(imageSizes);
    }

    HRESULT AdaptiveHostConfig::put_ImageSizes(_In_ IAdaptiveImageSizesConfig* imageSizes)
    {
        m_imageSizes = imageSizes;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_Spacing(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveSpacingConfig** spacingConfig)
    {
        return m_spacing.CopyTo(spacingConfig);
    }

    HRESULT AdaptiveHostConfig::put_Spacing(_In_ ABI::AdaptiveNamespace::IAdaptiveSpacingConfig* spacingConfig)
    {
        m_spacing = spacingConfig;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_Separator(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveSeparatorConfig** separatorConfig)
    {
        return m_separator.CopyTo(separatorConfig);
    }

    HRESULT AdaptiveHostConfig::put_Separator(_In_ ABI::AdaptiveNamespace::IAdaptiveSeparatorConfig* separatorConfig)
    {
        m_separator = separatorConfig;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_AdaptiveCard(_COM_Outptr_ IAdaptiveCardConfig** adaptiveCardConfig)
    {
        return m_adaptiveCard.CopyTo(adaptiveCardConfig);
    }

    HRESULT AdaptiveHostConfig::put_AdaptiveCard(_In_ IAdaptiveCardConfig* adaptiveCardConfig)
    {
        m_adaptiveCard = adaptiveCardConfig;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_ImageSet(_COM_Outptr_ IAdaptiveImageSetConfig** imageSetConfig)
    {
        return m_imageSet.CopyTo(imageSetConfig);
    }

    HRESULT AdaptiveHostConfig::put_ImageSet(_In_ IAdaptiveImageSetConfig* imageSetConfig)
    {
        m_imageSet = imageSetConfig;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_Image(_COM_Outptr_ IAdaptiveImageConfig** imageConfig)
    {
        return m_image.CopyTo(imageConfig);
    }

    HRESULT AdaptiveHostConfig::put_Image(_In_ IAdaptiveImageConfig* imageConfig)
    {
        m_image = imageConfig;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_FactSet(_COM_Outptr_ IAdaptiveFactSetConfig** factSetConfig)
    {
        return m_factSet.CopyTo(factSetConfig);
    }

    HRESULT AdaptiveHostConfig::put_FactSet(_In_ IAdaptiveFactSetConfig* factSetConfig)
    {
        m_factSet = factSetConfig;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_Actions(_COM_Outptr_ IAdaptiveActionsConfig** actionsConfig)
    {
        return m_actions.CopyTo(actionsConfig);
    }

    HRESULT AdaptiveHostConfig::put_Actions(_In_ IAdaptiveActionsConfig* actionsConfig)
    {
        m_actions = actionsConfig;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_Media(_COM_Outptr_ IAdaptiveMediaConfig** mediaConfig)
    {
        return m_media.CopyTo(mediaConfig);
    }

    HRESULT AdaptiveHostConfig::put_Media(_In_ IAdaptiveMediaConfig* mediaConfig)
    {
        m_media = mediaConfig;
        return S_OK;
    }

    HRESULT AdaptiveHostConfig::get_FontTypes(_COM_Outptr_ IAdaptiveFontTypesDefinition** value)
    {
        return m_fontTypes.CopyTo(value);
    }

    HRESULT AdaptiveHostConfig::put_FontTypes(_In_ IAdaptiveFontTypesDefinition* value)
    {
        m_fontTypes = value;
        return S_OK;
    }
}
