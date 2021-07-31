// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextElement.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveTextElement::get_Text(_Outptr_ HSTRING* text) { return m_text.CopyTo(text); }

    HRESULT AdaptiveTextElement::put_Text(_In_ HSTRING text) { return m_text.Set(text); }

    HRESULT AdaptiveTextElement::get_Size(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextSize>** textSize)
    {
        return m_textSize.CopyTo(textSize);
    }

    HRESULT AdaptiveTextElement::put_Size(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextSize>* textSize)
    {
        m_textSize = textSize;
        return S_OK;
    }

    HRESULT AdaptiveTextElement::get_Weight(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight>** textWeight)
    {
        return m_textWeight.CopyTo(textWeight);
    }

    HRESULT AdaptiveTextElement::put_Weight(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight>* textWeight)
    {
        m_textWeight = textWeight;
        return S_OK;
    }

    HRESULT AdaptiveTextElement::get_Color(
        _Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::ForegroundColor>** foregroundColor)
    {
        return m_foregroundColor.CopyTo(foregroundColor);
    }

    HRESULT AdaptiveTextElement::put_Color(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::ForegroundColor>* foregroundColor)
    {
        m_foregroundColor = foregroundColor;
        return S_OK;
    }

    HRESULT AdaptiveTextElement::get_IsSubtle(_Outptr_ ABI::Windows::Foundation::IReference<bool>** isSubtle)
    {
        return m_subtle.CopyTo(isSubtle);
    }

    HRESULT AdaptiveTextElement::put_IsSubtle(_In_ ABI::Windows::Foundation::IReference<bool>* isSubtle)
    {
        m_subtle = isSubtle;
        return S_OK;
    }

    HRESULT AdaptiveTextElement::get_Language(_Outptr_ HSTRING* language) { return m_language.CopyTo(language); }

    HRESULT AdaptiveTextElement::put_Language(_In_ HSTRING language) { return m_language.Set(language); }

    HRESULT AdaptiveTextElement::get_FontType(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::FontType>** fontType)
    {
        return m_fontType.CopyTo(fontType);
    }

    HRESULT AdaptiveTextElement::put_FontType(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::FontType>* fontType)
    {
        m_fontType = fontType;
        return S_OK;
    }
}
