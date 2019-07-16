// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveFontSizesConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveFontSizesConfig::RuntimeClassInitialize() noexcept try
    {
        FontSizesConfig fontSizesConfig;
        return RuntimeClassInitialize(fontSizesConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveFontSizesConfig::RuntimeClassInitialize(FontSizesConfig fontSizesConfig) noexcept
    {
        m_default = fontSizesConfig.GetFontSize(AdaptiveCards::TextSize::Default);
        m_small = fontSizesConfig.GetFontSize(AdaptiveCards::TextSize::Small);
        m_medium = fontSizesConfig.GetFontSize(AdaptiveCards::TextSize::Medium);
        m_large = fontSizesConfig.GetFontSize(AdaptiveCards::TextSize::Large);
        m_extraLarge = fontSizesConfig.GetFontSize(AdaptiveCards::TextSize::ExtraLarge);

        return S_OK;
    }

    HRESULT AdaptiveFontSizesConfig::get_Small(_Out_ UINT32* smallFontSize)
    {
        *smallFontSize = m_small;
        return S_OK;
    }

    HRESULT AdaptiveFontSizesConfig::put_Small(UINT32 smallFontSize)
    {
        m_small = smallFontSize;
        return S_OK;
    }

    HRESULT AdaptiveFontSizesConfig::get_Default(_Out_ UINT32* defaultFontSize)
    {
        *defaultFontSize = m_default;
        return S_OK;
    }

    HRESULT AdaptiveFontSizesConfig::put_Default(UINT32 defaultFontSize)
    {
        m_default = defaultFontSize;
        return S_OK;
    }

    HRESULT AdaptiveFontSizesConfig::get_Medium(_Out_ UINT32* mediumFontSize)
    {
        *mediumFontSize = m_medium;
        return S_OK;
    }

    HRESULT AdaptiveFontSizesConfig::put_Medium(UINT32 mediumFontSize)
    {
        m_medium = mediumFontSize;
        return S_OK;
    }

    HRESULT AdaptiveFontSizesConfig::get_Large(_Out_ UINT32* largeFontSize)
    {
        *largeFontSize = m_large;
        return S_OK;
    }

    HRESULT AdaptiveFontSizesConfig::put_Large(UINT32 largeFontSize)
    {
        m_large = largeFontSize;
        return S_OK;
    }

    HRESULT AdaptiveFontSizesConfig::get_ExtraLarge(_Out_ UINT32* extraLargeFontSize)
    {
        *extraLargeFontSize = m_extraLarge;
        return S_OK;
    }

    HRESULT AdaptiveFontSizesConfig::put_ExtraLarge(UINT32 extraLargeFontSize)
    {
        m_extraLarge = extraLargeFontSize;
        return S_OK;
    }
}
