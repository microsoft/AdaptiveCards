// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Util.h"
#include "AdaptiveColorConfig.h"
#include "AdaptiveHighlightColorConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveColorConfig::RuntimeClassInitialize() noexcept
    try
    {
        ColorConfig colorConfig;
        return RuntimeClassInitialize(colorConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveColorConfig::RuntimeClassInitialize(ColorConfig colorConfig) noexcept
    {
        RETURN_IF_FAILED(GetColorFromString(colorConfig.defaultColor, &m_defaultColor));
        RETURN_IF_FAILED(GetColorFromString(colorConfig.subtleColor, &m_subtleColor));

        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveHighlightColorConfig>(m_highlightColors.GetAddressOf(), colorConfig.highlightColors));

        return S_OK;
    }

    HRESULT AdaptiveColorConfig::get_Default(_Out_ ABI::Windows::UI::Color* value)
    {
        *value = m_defaultColor;
        return S_OK;
    }

    HRESULT AdaptiveColorConfig::put_Default(ABI::Windows::UI::Color color)
    {
        m_defaultColor = color;
        return S_OK;
    }

    HRESULT AdaptiveColorConfig::get_Subtle(_Out_ ABI::Windows::UI::Color* value)
    {
        *value = m_subtleColor;
        return S_OK;
    }

    HRESULT AdaptiveColorConfig::put_Subtle(ABI::Windows::UI::Color color)
    {
        m_subtleColor = color;
        return S_OK;
    }

    HRESULT AdaptiveColorConfig::get_HighlightColors(_COM_Outptr_ IAdaptiveHighlightColorConfig** highlightColors)
    {
        return m_highlightColors.CopyTo(highlightColors);
    }

    HRESULT AdaptiveColorConfig::put_HighlightColors(_In_ IAdaptiveHighlightColorConfig* highlightColors)
    {
        m_highlightColors = highlightColors;
        return S_OK;
    }
}
