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
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Data::Json;

namespace AdaptiveCards { namespace Uwp
{
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
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::RuntimeClassInitialize(const HostConfig& sharedHostConfig)
    {
        RETURN_IF_FAILED(RuntimeClassInitialize());

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
        ComPtr<IAdaptiveFontSizesConfig> localFontSizes = m_fontSizes;
        *fontSizesConfig = localFontSizes.Detach();
        return S_OK;
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
        ComPtr<IAdaptiveFontWeightsConfig> localFontWeights = m_fontWeights;
        *fontWeightsConfig = localFontWeights.Detach();
        return S_OK;
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
    HRESULT AdaptiveHostConfig::get_ContainerStyles(ABI::AdaptiveCards::Uwp::IAdaptiveContainerStylesDefinition** value)
    {
        ComPtr<IAdaptiveContainerStylesDefinition> styleDefinition = m_containerStyles;
        *value = styleDefinition.Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_ContainerStyles(ABI::AdaptiveCards::Uwp::IAdaptiveContainerStylesDefinition* containerStylesDefinition)
    {
        m_containerStyles = containerStylesDefinition;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_ImageSizes(IAdaptiveImageSizesConfig** imageSizes)
    {
        ComPtr<IAdaptiveImageSizesConfig> localImageSizes = m_imageSizes;
        *imageSizes = localImageSizes.Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_ImageSizes(IAdaptiveImageSizesConfig* imageSizes)
    {
        m_imageSizes = imageSizes;
        return S_OK;
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::get_Spacing(ABI::AdaptiveCards::Uwp::IAdaptiveSpacingConfig** spacingConfig)
    {
        ComPtr<IAdaptiveSpacingConfig> localSpacing = m_spacing;
        *spacingConfig = localSpacing.Detach();
        return S_OK;
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::put_Spacing(ABI::AdaptiveCards::Uwp::IAdaptiveSpacingConfig* spacingConfig)
    {
        m_spacing = spacingConfig;
        return S_OK;
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::get_Separator(ABI::AdaptiveCards::Uwp::IAdaptiveSeparatorConfig** separatorConfig)
    {
        ComPtr<IAdaptiveSeparatorConfig> localSeparator = m_separator;
        *separatorConfig = localSeparator.Detach();
        return S_OK;
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::put_Separator(ABI::AdaptiveCards::Uwp::IAdaptiveSeparatorConfig* separatorConfig)
    {
        m_separator = separatorConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_AdaptiveCard(IAdaptiveCardConfig** adaptiveCardConfig)
    {
        ComPtr<IAdaptiveCardConfig> localAdaptiveCard = m_adaptiveCard;
        *adaptiveCardConfig = localAdaptiveCard.Detach();
        return S_OK;
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
        ComPtr<IAdaptiveImageSetConfig> localImageSet = m_imageSet;
        *imageSetConfig = localImageSet.Detach();
        return S_OK;
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
        ComPtr<IAdaptiveImageConfig> localImage = m_image;
        *imageConfig = localImage.Detach();
        return S_OK;
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
        ComPtr<IAdaptiveFactSetConfig> localFactSet = m_factSet;
        *factSetConfig = localFactSet.Detach();
        return S_OK;
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
        ComPtr<IAdaptiveActionsConfig> localActions = m_actions;
        *actionsConfig = localActions.Detach();
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_Actions(IAdaptiveActionsConfig* actionsConfig)
    {
        m_actions = actionsConfig;
        return S_OK;
    }
}}
