#include "pch.h"
#include "AdaptiveColorsConfig.h"
#include "AdaptiveColorConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveColorsConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveColorsConfig::RuntimeClassInitialize(ColorsConfig colorsConfig) noexcept
    {
        m_sharedColorsConfig = colorsConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Default(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig** defaultColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(defaultColorConfig, m_sharedColorsConfig.defaultColor);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Default(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Accent(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig** accentColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(accentColorConfig, m_sharedColorsConfig.accent);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Accent(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Dark(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig** darkColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(darkColorConfig, m_sharedColorsConfig.dark);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Dark(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Light(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig** lightColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(lightColorConfig, m_sharedColorsConfig.light);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Light(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Good(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig** goodColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(goodColorConfig, m_sharedColorsConfig.good);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Good(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }
    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Warning(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig** warningColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(warningColorConfig, m_sharedColorsConfig.warning);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Warning(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }
    
    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Attention(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig** attentionColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(attentionColorConfig, m_sharedColorsConfig.attention);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Attention(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }
}
}
