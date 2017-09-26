#include "pch.h"
#include "AdaptiveColorsConfig.h"
#include "AdaptiveColorConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Uwp;

namespace AdaptiveCards { namespace Uwp
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
    HRESULT AdaptiveColorsConfig::get_Default(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** defaultColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(defaultColorConfig, m_sharedColorsConfig.defaultColor);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Default(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Accent(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** accentColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(accentColorConfig, m_sharedColorsConfig.accent);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Accent(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Dark(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** darkColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(darkColorConfig, m_sharedColorsConfig.dark);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Dark(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Light(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** lightColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(lightColorConfig, m_sharedColorsConfig.light);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Light(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Good(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** goodColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(goodColorConfig, m_sharedColorsConfig.good);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Good(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }
    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Warning(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** warningColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(warningColorConfig, m_sharedColorsConfig.warning);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Warning(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }
    
    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Attention(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** attentionColorConfig)
    {
        return MakeAndInitialize<AdaptiveColorConfig>(attentionColorConfig, m_sharedColorsConfig.attention);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Attention(ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* /*value*/)
    {
        return E_NOTIMPL;
    }
}
}
