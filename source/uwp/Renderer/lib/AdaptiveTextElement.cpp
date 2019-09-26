// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextElement.h"
#include "DateTimeParser.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveTextElement::get_Text(_Outptr_ HSTRING* text) { return m_text.CopyTo(text); }

    HRESULT AdaptiveTextElement::put_Text(_In_ HSTRING text) { return m_text.Set(text); }

    HRESULT AdaptiveTextElement::get_Size(_Out_ ABI::AdaptiveNamespace::TextSize* textSize)
    {
        *textSize = m_textSize;
        return S_OK;
    }

    HRESULT AdaptiveTextElement::put_Size(ABI::AdaptiveNamespace::TextSize textSize)
    {
        m_textSize = textSize;
        return S_OK;
    }

    HRESULT AdaptiveTextElement::get_Weight(_Out_ ABI::AdaptiveNamespace::TextWeight* textWeight)
    {
        *textWeight = m_textWeight;
        return S_OK;
    }

    HRESULT AdaptiveTextElement::put_Weight(ABI::AdaptiveNamespace::TextWeight textWeight)
    {
        m_textWeight = textWeight;
        return S_OK;
    }

    HRESULT AdaptiveTextElement::get_Color(_Out_ ABI::AdaptiveNamespace::ForegroundColor* foregroundColor)
    {
        *foregroundColor = m_foregroundColor;
        return S_OK;
    }

    HRESULT AdaptiveTextElement::put_Color(ABI::AdaptiveNamespace::ForegroundColor foregroundColor)
    {
        m_foregroundColor = foregroundColor;
        return S_OK;
    }

    HRESULT AdaptiveTextElement::get_IsSubtle(_Out_ boolean* isSubtle)
    {
        *isSubtle = m_subtle;
        return S_OK;
    }

    HRESULT AdaptiveTextElement::put_IsSubtle(boolean isSubtle)
    {
        m_subtle = isSubtle;
        return S_OK;
    }

    HRESULT AdaptiveTextElement::get_Language(_Outptr_ HSTRING* language) { return m_language.CopyTo(language); }

    HRESULT AdaptiveTextElement::put_Language(_In_ HSTRING language) { return m_language.Set(language); }

    HRESULT AdaptiveTextElement::get_FontType(_Out_ ABI::AdaptiveNamespace::FontType* fontType)
    {
        *fontType = m_fontType;
        return S_OK;
    }

    HRESULT AdaptiveTextElement::put_FontType(ABI::AdaptiveNamespace::FontType fontType)
    {
        m_fontType = fontType;
        return S_OK;
    }
}
