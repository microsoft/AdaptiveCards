// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Util.h"
#include "AdaptiveTextConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveTextConfig::RuntimeClassInitialize() noexcept try
    {
        TextConfig textConfig;
        return RuntimeClassInitialize(textConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextConfig::RuntimeClassInitialize(TextConfig textConfig) noexcept
    {
        m_textWeight = static_cast<ABI::AdaptiveNamespace::TextWeight>(textConfig.weight);
        m_textSize = static_cast<ABI::AdaptiveNamespace::TextSize>(textConfig.size);
        m_textColor = static_cast<ABI::AdaptiveNamespace::ForegroundColor>(textConfig.color);
        m_isSubtle = textConfig.isSubtle;
        m_wrap = textConfig.wrap;
        m_maxWidth = textConfig.maxWidth;

        return S_OK;
    }

    HRESULT AdaptiveTextConfig::get_Size(_Out_ ABI::AdaptiveNamespace::TextSize* textSize)
    {
        *textSize = m_textSize;
        return S_OK;
    }

    HRESULT AdaptiveTextConfig::put_Size(ABI::AdaptiveNamespace::TextSize textSize)
    {
        m_textSize = textSize;
        return S_OK;
    }

    HRESULT AdaptiveTextConfig::get_Weight(_Out_ ABI::AdaptiveNamespace::TextWeight* textWeight)
    {
        *textWeight = m_textWeight;
        return S_OK;
    }

    HRESULT AdaptiveTextConfig::put_Weight(ABI::AdaptiveNamespace::TextWeight textWeight)
    {
        m_textWeight = textWeight;
        return S_OK;
    }

    HRESULT AdaptiveTextConfig::get_Color(_Out_ ABI::AdaptiveNamespace::ForegroundColor* textColor)
    {
        *textColor = m_textColor;
        return S_OK;
    }

    HRESULT AdaptiveTextConfig::put_Color(ABI::AdaptiveNamespace::ForegroundColor textColor)
    {
        m_textColor = textColor;
        return S_OK;
    }

    HRESULT AdaptiveTextConfig::get_IsSubtle(_Out_ boolean* isSubtle)
    {
        *isSubtle = m_isSubtle;
        return S_OK;
    }

    HRESULT AdaptiveTextConfig::put_IsSubtle(boolean isSubtle)
    {
        m_isSubtle = isSubtle;
        return S_OK;
    }

    HRESULT AdaptiveTextConfig::get_Wrap(_Out_ boolean* wrap)
    {
        *wrap = m_wrap;
        return S_OK;
    }
    HRESULT AdaptiveTextConfig::put_Wrap(boolean wrap)
    {
        m_wrap = wrap;
        return S_OK;
    }
    HRESULT AdaptiveTextConfig::get_MaxWidth(_Out_ UINT32* maxWidth)
    {
        *maxWidth = m_maxWidth;
        return S_OK;
    }
    HRESULT AdaptiveTextConfig::put_MaxWidth(UINT32 maxWidth)
    {
        m_maxWidth = maxWidth;
        return S_OK;
    }
}
