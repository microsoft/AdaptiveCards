#include "pch.h"
#include "AdaptiveHostConfig.h"
#include "Util.h"
#include "AdaptiveActionsConfig.h"
#include "AdaptiveCardConfig.h"
#include "AdaptiveColorsConfig.h"
#include "AdaptiveContainerConfig.h"
#include "AdaptiveFactSetConfig.h"
#include "AdaptiveFontSizesConfig.h"
#include "AdaptiveImageSetConfig.h"
#include "AdaptiveImageSizesConfig.h"
#include "AdaptiveSpacingConfig.h"
#include "AdaptiveSeparatorThicknessConfig.h"

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
    HRESULT  AdaptiveHostConfig::get_Colors(IAdaptiveColorsConfig** colorsConfig)
    {
        return MakeAndInitialize<AdaptiveColorsConfig>(colorsConfig, m_sharedHostConfig.colors);
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveHostConfig::put_Colors(IAdaptiveColorsConfig* )
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
    HRESULT AdaptiveHostConfig::get_MaxActions(UINT32* maxActions)
    {
        *maxActions = m_sharedHostConfig.maxActions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_MaxActions(UINT32 maxActions)
    {
        m_sharedHostConfig.maxActions = maxActions;
        return S_OK;
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::get_Spacing(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingConfig ** spacingConfig)
    {
        return MakeAndInitialize<AdaptiveSpacingConfig>(spacingConfig, m_sharedHostConfig.spacing);
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::put_Spacing(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingConfig * spacingConfig)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::get_SeparatorThickness(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparatorThicknessConfig ** separatorThicknessConfig)
    {
        return MakeAndInitialize<AdaptiveSeparatorThicknessConfig>(separatorThicknessConfig, m_sharedHostConfig.separatorThickness);
    }

    _Use_decl_annotations_ 
    HRESULT AdaptiveHostConfig::put_SeparatorThickness(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparatorThicknessConfig * separatorThicknessConfig)
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
    HRESULT AdaptiveHostConfig::get_Container(IAdaptiveContainerConfig** containerConfig)
    {
        return MakeAndInitialize<AdaptiveContainerConfig>(containerConfig, m_sharedHostConfig.container);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveHostConfig::put_Container(IAdaptiveContainerConfig* )
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
