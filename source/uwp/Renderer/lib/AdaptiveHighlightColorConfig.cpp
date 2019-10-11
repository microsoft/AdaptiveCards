// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveHighlightColorConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveHighlightColorConfig::RuntimeClassInitialize() noexcept
    try
    {
        HighlightColorConfig colorConfig;
        return RuntimeClassInitialize(colorConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveHighlightColorConfig::RuntimeClassInitialize(HighlightColorConfig colorConfig) noexcept
    {
        RETURN_IF_FAILED(GetColorFromString(colorConfig.defaultColor, &m_defaultColor));
        RETURN_IF_FAILED(GetColorFromString(colorConfig.subtleColor, &m_subtleColor));
        return S_OK;
    }

    HRESULT AdaptiveHighlightColorConfig::get_Default(_Out_ ABI::Windows::UI::Color* value)
    {
        *value = m_defaultColor;
        return S_OK;
    }

    HRESULT AdaptiveHighlightColorConfig::put_Default(ABI::Windows::UI::Color color)
    {
        m_defaultColor = color;
        return S_OK;
    }

    HRESULT AdaptiveHighlightColorConfig::get_Subtle(_Out_ ABI::Windows::UI::Color* value)
    {
        *value = m_subtleColor;
        return S_OK;
    }

    HRESULT AdaptiveHighlightColorConfig::put_Subtle(ABI::Windows::UI::Color color)
    {
        m_subtleColor = color;
        return S_OK;
    }
}
