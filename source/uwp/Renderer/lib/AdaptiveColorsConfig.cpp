#include "pch.h"
#include "AdaptiveColorsConfig.h"
#include "AdaptiveColorConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespaceRef;

AdaptiveNamespaceStart
    HRESULT AdaptiveColorsConfig::RuntimeClassInitialize() noexcept try
    {
        ColorsConfig colorsConfig;
        return RuntimeClassInitialize(colorsConfig);
    } CATCH_RETURN;

    HRESULT AdaptiveColorsConfig::RuntimeClassInitialize(ColorsConfig colorsConfig) noexcept
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveColorConfig>(m_default.GetAddressOf(), colorsConfig.defaultColor));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveColorConfig>(m_accent.GetAddressOf(), colorsConfig.accent));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveColorConfig>(m_attention.GetAddressOf(), colorsConfig.attention));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveColorConfig>(m_dark.GetAddressOf(), colorsConfig.dark));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveColorConfig>(m_good.GetAddressOf(), colorsConfig.good));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveColorConfig>(m_light.GetAddressOf(), colorsConfig.light));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveColorConfig>(m_warning.GetAddressOf(), colorsConfig.warning));

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Default(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig** defaultColorConfig)
    {
        return m_default.CopyTo(defaultColorConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Default(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig* colorConfig)
    {
        m_default = colorConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Accent(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig** accentColorConfig)
    {
        return m_accent.CopyTo(accentColorConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Accent(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig* colorConfig)
    {
        m_accent = colorConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Dark(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig** darkColorConfig)
    {
        return m_dark.CopyTo(darkColorConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Dark(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig* colorConfig)
    {
        m_dark = colorConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Light(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig** lightColorConfig)
    {
        return m_light.CopyTo(lightColorConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Light(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig* colorConfig)
    {
        m_light = colorConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Good(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig** goodColorConfig)
    {
        return m_good.CopyTo(goodColorConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Good(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig* colorConfig)
    {
        m_good = colorConfig;
        return S_OK;
    }
    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Warning(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig** warningColorConfig)
    {
        return m_warning.CopyTo(warningColorConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Warning(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig* colorConfig)
    {
        m_warning = colorConfig;
        return S_OK;
    }
    
    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::get_Attention(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig** attentionColorConfig)
    {
        return m_attention.CopyTo(attentionColorConfig);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorsConfig::put_Attention(ABI::AdaptiveNamespaceRef::IAdaptiveColorConfig* colorConfig)
    {
        m_attention = colorConfig;
        return S_OK;
    }
AdaptiveNamespaceEnd
