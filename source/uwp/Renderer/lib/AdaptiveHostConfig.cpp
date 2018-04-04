#include "pch.h"
#include "AdaptiveHostConfig.h"
#include "Util.h"
#include "AdaptiveActionsConfig.h"
#include "AdaptiveCardConfig.h"
#include "AdaptiveColorsConfig.h"
#include "AdaptiveContainerStylesDefinition.h"
#include "AdaptiveFactSetConfig.h"
#include "AdaptiveFontSizesConfig.h"
#include "AdaptiveFontWeightsConfig.h"
#include "AdaptiveHostConfigParseResult.h"
#include "AdaptiveImageConfig.h"
#include "AdaptiveImageSetConfig.h"
#include "AdaptiveImageSizesConfig.h"
#include "AdaptiveSpacingConfig.h"
#include "AdaptiveSeparatorConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;

AdaptiveNamespaceStart
    _Use_decl_annotations_
    HRESULT AdaptiveHostConfigStaticsImpl::FromJsonString(HSTRING adaptiveJson, IAdaptiveHostConfigParseResult** parseResult) noexcept try
    {
        *parseResult = nullptr;

        std::string adaptiveJsonString;
        RETURN_IF_FAILED(HStringToUTF8(adaptiveJson, adaptiveJsonString));
        return FromJsonString(adaptiveJsonString, parseResult);

    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfigStaticsImpl::FromJson(IJsonObject* adaptiveJson, IAdaptiveHostConfigParseResult** parseResult) noexcept try
    {
        *parseResult = nullptr;

        std::string adaptiveJsonString;
        RETURN_IF_FAILED(JsonObjectToString(adaptiveJson, adaptiveJsonString));

        return FromJsonString(adaptiveJsonString, parseResult);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfigStaticsImpl::FromJsonString(const std::string jsonString, IAdaptiveHostConfigParseResult** parseResult)
    {
        HostConfig sharedHostConfig = HostConfig::DeserializeFromString(jsonString);

        ComPtr<IAdaptiveHostConfig> config;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveHostConfig>(&config, sharedHostConfig));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveHostConfigParseResult>(parseResult, config.Get()));

        return S_OK;
    }

    HRESULT AdaptiveHostConfig::RuntimeClassInitialize() noexcept try
    {
        HostConfig sharedHostConfig;
        return RuntimeClassInitialize(sharedHostConfig);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::RuntimeClassInitialize(const HostConfig& sharedHostConfig)
    {
        m_supportsInteractivity = sharedHostConfig.supportsInteractivity;
        RETURN_IF_FAILED(UTF8ToHString(sharedHostConfig.fontFamily, m_fontFamily.GetAddressOf()));

        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontSizesConfig>(m_fontSizes.GetAddressOf(), sharedHostConfig.fontSizes));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFontWeightsConfig>(m_fontWeights.GetAddressOf(), sharedHostConfig.fontWeights));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveContainerStylesDefinition>(m_containerStyles.GetAddressOf(), sharedHostConfig.containerStyles));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveImageSizesConfig>(m_imageSizes.GetAddressOf(), sharedHostConfig.imageSizes));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveSpacingConfig>(m_spacing.GetAddressOf(), sharedHostConfig.spacing));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveSeparatorConfig>(m_separator.GetAddressOf(), sharedHostConfig.separator));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveCardConfig>(m_adaptiveCard.GetAddressOf(), sharedHostConfig.adaptiveCard));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveImageSetConfig>(m_imageSet.GetAddressOf(), sharedHostConfig.imageSet));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFactSetConfig>(m_factSet.GetAddressOf(), sharedHostConfig.factSet));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveActionsConfig>(m_actions.GetAddressOf(), sharedHostConfig.actions));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveImageConfig>(m_image.GetAddressOf(), sharedHostConfig.image));

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_FontFamily(HSTRING* text)
    {
        return m_fontFamily.CopyTo(text);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_FontFamily(HSTRING text)
    {
        return m_fontFamily.Set(text);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_FontSizes(IAdaptiveFontSizesConfig** fontSizesConfig)
    {
        return m_fontSizes.CopyTo(fontSizesConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_FontSizes(IAdaptiveFontSizesConfig* fontSizes)
    {
        m_fontSizes = fontSizes;
        return S_OK;
    }

    _Use_decl_annotations_
     HRESULT AdaptiveHostConfig::get_FontWeights(IAdaptiveFontWeightsConfig** fontWeightsConfig)
    {
        return m_fontWeights.CopyTo(fontWeightsConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_FontWeights(IAdaptiveFontWeightsConfig* fontWeights)
    {
        m_fontWeights = fontWeights;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_SupportsInteractivity(boolean* supporsInteractivity)
    {
        *supporsInteractivity = m_supportsInteractivity;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_SupportsInteractivity(boolean supportsInteractivity)
    {
        m_supportsInteractivity = supportsInteractivity;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_ContainerStyles(ABI::AdaptiveNamespace::IAdaptiveContainerStylesDefinition** value)
    {
        return m_containerStyles.CopyTo(value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_ContainerStyles(ABI::AdaptiveNamespace::IAdaptiveContainerStylesDefinition* containerStylesDefinition)
    {
        m_containerStyles = containerStylesDefinition;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_ImageSizes(IAdaptiveImageSizesConfig** imageSizes)
    {
        return m_imageSizes.CopyTo(imageSizes);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_ImageSizes(IAdaptiveImageSizesConfig* imageSizes)
    {
        m_imageSizes = imageSizes;
        return S_OK;
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::get_Spacing(ABI::AdaptiveNamespace::IAdaptiveSpacingConfig** spacingConfig)
    {
        return m_spacing.CopyTo(spacingConfig);
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::put_Spacing(ABI::AdaptiveNamespace::IAdaptiveSpacingConfig* spacingConfig)
    {
        m_spacing = spacingConfig;
        return S_OK;
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::get_Separator(ABI::AdaptiveNamespace::IAdaptiveSeparatorConfig** separatorConfig)
    {
        return m_separator.CopyTo(separatorConfig);
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::put_Separator(ABI::AdaptiveNamespace::IAdaptiveSeparatorConfig* separatorConfig)
    {
        m_separator = separatorConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_AdaptiveCard(IAdaptiveCardConfig** adaptiveCardConfig)
    {
        return m_adaptiveCard.CopyTo(adaptiveCardConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_AdaptiveCard(IAdaptiveCardConfig* adaptiveCardConfig)
    {
        m_adaptiveCard = adaptiveCardConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_ImageSet(IAdaptiveImageSetConfig** imageSetConfig)
    {
        return m_imageSet.CopyTo(imageSetConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_ImageSet(IAdaptiveImageSetConfig* imageSetConfig)
    {
        m_imageSet = imageSetConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_Image(IAdaptiveImageConfig** imageConfig)
    {
        return m_image.CopyTo(imageConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_Image(IAdaptiveImageConfig* imageConfig)
    {
        m_image = imageConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_FactSet(IAdaptiveFactSetConfig** factSetConfig)
    {
        return m_factSet.CopyTo(factSetConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_FactSet(IAdaptiveFactSetConfig* factSetConfig)
    {
        m_factSet = factSetConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_Actions(IAdaptiveActionsConfig** actionsConfig)
    {
        return m_actions.CopyTo(actionsConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_Actions(IAdaptiveActionsConfig* actionsConfig)
    {
        m_actions = actionsConfig;
        return S_OK;
    }
AdaptiveNamespaceEnd
