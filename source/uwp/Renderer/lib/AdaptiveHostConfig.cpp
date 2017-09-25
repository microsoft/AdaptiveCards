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
#include "AdaptiveImageConfig.h"
#include "AdaptiveImageSetConfig.h"
#include "AdaptiveImageSizesConfig.h"
#include "AdaptiveSpacingConfig.h"
#include "AdaptiveSeparatorConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    _Use_decl_annotations_
    HRESULT AdaptiveHostConfigStaticsImpl::CreateHostConfigFromJson(HSTRING adaptiveJson, IAdaptiveHostConfig** config) noexcept try
    {
        *config = nullptr;

        std::string adaptiveJsonString;
        RETURN_IF_FAILED(HStringToUTF8(adaptiveJson, adaptiveJsonString));

        HostConfig sharedHostConfig = HostConfig::DeserializeFromString(adaptiveJsonString);
        return MakeAndInitialize<AdaptiveHostConfig>(config, sharedHostConfig);
    } CATCH_RETURN;

    HRESULT AdaptiveHostConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::RuntimeClassInitialize(const HostConfig& sharedHostConfig)
    {
        RETURN_IF_FAILED(RuntimeClassInitialize());
        m_sharedHostConfig = sharedHostConfig;

        //TODO: Generate projections for HostConfig

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_FontFamily(HSTRING* text)
    {
        return UTF8ToHString(m_sharedHostConfig.fontFamily, text);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_FontFamily(HSTRING text)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(text, out));
        m_sharedHostConfig.fontFamily = out;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_FontSizes(IAdaptiveFontSizesConfig** fontSizesConfig)
    {
        return MakeAndInitialize<AdaptiveFontSizesConfig>(fontSizesConfig, m_sharedHostConfig.fontSizes);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_FontSizes(IAdaptiveFontSizesConfig*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
     HRESULT AdaptiveHostConfig::get_FontWeights(IAdaptiveFontWeightsConfig** fontWeightsConfig)
    {
        return MakeAndInitialize<AdaptiveFontWeightsConfig>(fontWeightsConfig, m_sharedHostConfig.fontWeights);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_FontWeights(IAdaptiveFontWeightsConfig*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_SupportsInteractivity(boolean* supporsInteractivity)
    {
        *supporsInteractivity = m_sharedHostConfig.supportsInteractivity;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_SupportsInteractivity(boolean supportsInteractivity)
    {
        m_sharedHostConfig.supportsInteractivity = Boolify(supportsInteractivity);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_ContainerStyles(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStylesDefinition** value)
    {
        return MakeAndInitialize<AdaptiveContainerStylesDefinition>(value, m_sharedHostConfig.containerStyles);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_ContainerStyles(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStylesDefinition* value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_ImageSizes(IAdaptiveImageSizesConfig** imageSizes)
    {
        return MakeAndInitialize<AdaptiveImageSizesConfig>(imageSizes, m_sharedHostConfig.imageSizes);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_ImageSizes(IAdaptiveImageSizesConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::get_Spacing(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingConfig** spacingConfig)
    {
        return MakeAndInitialize<AdaptiveSpacingConfig>(spacingConfig, m_sharedHostConfig.spacing);
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::put_Spacing(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingConfig* spacingConfig)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::get_Separator(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparatorConfig** separatorConfig)
    {
        return MakeAndInitialize<AdaptiveSeparatorConfig>(separatorConfig, m_sharedHostConfig.separator);
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::put_Separator(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparatorConfig* separatorConfig)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_AdaptiveCard(IAdaptiveCardConfig** adaptiveCardConfig)
    {
        return MakeAndInitialize<AdaptiveCardConfig>(adaptiveCardConfig, m_sharedHostConfig.adaptiveCard);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_AdaptiveCard(IAdaptiveCardConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_ImageSet(IAdaptiveImageSetConfig** imageSetConfig)
    {
        return MakeAndInitialize<AdaptiveImageSetConfig>(imageSetConfig, m_sharedHostConfig.imageSet);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_ImageSet(IAdaptiveImageSetConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_Image(IAdaptiveImageConfig** imageConfig)
    {
        return MakeAndInitialize<AdaptiveImageConfig>(imageConfig, m_sharedHostConfig.image);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_Image(IAdaptiveImageConfig*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_FactSet(IAdaptiveFactSetConfig** factSetConfig)
    {
        return MakeAndInitialize<AdaptiveFactSetConfig>(factSetConfig, m_sharedHostConfig.factSet);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_FactSet(IAdaptiveFactSetConfig* )
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::get_Actions(IAdaptiveActionsConfig** actionsConfig)
    {
        return MakeAndInitialize<AdaptiveActionsConfig>(actionsConfig, m_sharedHostConfig.actions);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_Actions(IAdaptiveActionsConfig* )
    {
        return E_NOTIMPL;
    }
}}
