// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveColorsConfig.h"
#include "AdaptiveColorConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveColorsConfig::RuntimeClassInitialize() noexcept
    try
    {
        ColorsConfig colorsConfig;
        return RuntimeClassInitialize(colorsConfig);
    }
    CATCH_RETURN;

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

    HRESULT AdaptiveColorsConfig::get_Default(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** defaultColorConfig)
    {
        return m_default.CopyTo(defaultColorConfig);
    }

    HRESULT AdaptiveColorsConfig::put_Default(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* colorConfig)
    {
        m_default = colorConfig;
        return S_OK;
    }

    HRESULT AdaptiveColorsConfig::get_Accent(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** accentColorConfig)
    {
        return m_accent.CopyTo(accentColorConfig);
    }

    HRESULT AdaptiveColorsConfig::put_Accent(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* colorConfig)
    {
        m_accent = colorConfig;
        return S_OK;
    }

    HRESULT AdaptiveColorsConfig::get_Dark(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** darkColorConfig)
    {
        return m_dark.CopyTo(darkColorConfig);
    }

    HRESULT AdaptiveColorsConfig::put_Dark(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* colorConfig)
    {
        m_dark = colorConfig;
        return S_OK;
    }

    HRESULT AdaptiveColorsConfig::get_Light(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** lightColorConfig)
    {
        return m_light.CopyTo(lightColorConfig);
    }

    HRESULT AdaptiveColorsConfig::put_Light(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* colorConfig)
    {
        m_light = colorConfig;
        return S_OK;
    }

    HRESULT AdaptiveColorsConfig::get_Good(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** goodColorConfig)
    {
        return m_good.CopyTo(goodColorConfig);
    }

    HRESULT AdaptiveColorsConfig::put_Good(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* colorConfig)
    {
        m_good = colorConfig;
        return S_OK;
    }
    HRESULT AdaptiveColorsConfig::get_Warning(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** warningColorConfig)
    {
        return m_warning.CopyTo(warningColorConfig);
    }

    HRESULT AdaptiveColorsConfig::put_Warning(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* colorConfig)
    {
        m_warning = colorConfig;
        return S_OK;
    }

    HRESULT AdaptiveColorsConfig::get_Attention(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** attentionColorConfig)
    {
        return m_attention.CopyTo(attentionColorConfig);
    }

    HRESULT AdaptiveColorsConfig::put_Attention(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* colorConfig)
    {
        m_attention = colorConfig;
        return S_OK;
    }
}
