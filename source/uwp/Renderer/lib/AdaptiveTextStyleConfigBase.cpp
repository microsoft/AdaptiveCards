// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextStyleConfigBase.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveTextStyleConfigBase::InitializeTextStyleConfig(TextStyleConfig textStyleConfig)
    {
        m_textWeight = static_cast<ABI::AdaptiveNamespace::TextWeight>(textStyleConfig.weight);
        m_textSize = static_cast<ABI::AdaptiveNamespace::TextSize>(textStyleConfig.size);
        m_textColor = static_cast<ABI::AdaptiveNamespace::ForegroundColor>(textStyleConfig.color);
        m_isSubtle = textStyleConfig.isSubtle;
        m_fontType = static_cast<ABI::AdaptiveNamespace::FontType>(textStyleConfig.fontType);

        return S_OK;
    }

    HRESULT AdaptiveTextStyleConfigBase::get_Size(_Out_ ABI::AdaptiveNamespace::TextSize* textSize)
    {
        *textSize = m_textSize;
        return S_OK;
    }

    HRESULT AdaptiveTextStyleConfigBase::put_Size(ABI::AdaptiveNamespace::TextSize textSize)
    {
        m_textSize = textSize;
        return S_OK;
    }

    HRESULT AdaptiveTextStyleConfigBase::get_Weight(_Out_ ABI::AdaptiveNamespace::TextWeight* textWeight)
    {
        *textWeight = m_textWeight;
        return S_OK;
    }

    HRESULT AdaptiveTextStyleConfigBase::put_Weight(ABI::AdaptiveNamespace::TextWeight textWeight)
    {
        m_textWeight = textWeight;
        return S_OK;
    }

    HRESULT AdaptiveTextStyleConfigBase::get_Color(_Out_ ABI::AdaptiveNamespace::ForegroundColor* textColor)
    {
        *textColor = m_textColor;
        return S_OK;
    }

    HRESULT AdaptiveTextStyleConfigBase::put_Color(ABI::AdaptiveNamespace::ForegroundColor textColor)
    {
        m_textColor = textColor;
        return S_OK;
    }

    HRESULT AdaptiveTextStyleConfigBase::get_IsSubtle(_Out_ boolean* isSubtle)
    {
        *isSubtle = m_isSubtle;
        return S_OK;
    }

    HRESULT AdaptiveTextStyleConfigBase::put_IsSubtle(boolean isSubtle)
    {
        m_isSubtle = isSubtle;
        return S_OK;
    }

    HRESULT AdaptiveTextStyleConfigBase::get_FontType(ABI::AdaptiveNamespace::FontType* fontType)
    {
        *fontType = m_fontType;
        return S_OK;
    }

    HRESULT AdaptiveTextStyleConfigBase::put_FontType(ABI::AdaptiveNamespace::FontType fontType)
    {
        m_fontType = fontType;
        return S_OK;
    }
}
