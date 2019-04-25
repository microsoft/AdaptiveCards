#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("4BC6640A-8FBE-4DE0-81FD-119BC10877F1") AdaptiveTextElement : public IUnknown
    {
    public:
        IFACEMETHODIMP get_Text(_Outptr_ HSTRING* text);
        IFACEMETHODIMP put_Text(_In_ HSTRING text);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveNamespace::TextSize* textSize);
        IFACEMETHODIMP put_Size(ABI::AdaptiveNamespace::TextSize textSize);

        IFACEMETHODIMP get_Weight(_Out_ ABI::AdaptiveNamespace::TextWeight* textWeight);
        IFACEMETHODIMP put_Weight(ABI::AdaptiveNamespace::TextWeight textWeight);

        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveNamespace::ForegroundColor* textColor);
        IFACEMETHODIMP put_Color(ABI::AdaptiveNamespace::ForegroundColor textColor);

        IFACEMETHODIMP get_IsSubtle(_Out_ boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(boolean isSubtle);

        IFACEMETHODIMP get_Italic(_Out_ boolean* italic);
        IFACEMETHODIMP put_Italic(boolean italic);

        IFACEMETHODIMP get_Strikethrough(_Out_ boolean* strikethrough);
        IFACEMETHODIMP put_Strikethrough(boolean strikethrough);

        IFACEMETHODIMP get_Language(_Outptr_ HSTRING* language);
        IFACEMETHODIMP put_Language(_In_ HSTRING language);

        IFACEMETHODIMP get_FontStyle(_Out_ ABI::AdaptiveNamespace::FontStyle* style);
        IFACEMETHODIMP put_FontStyle(ABI::AdaptiveNamespace::FontStyle style);

    protected:
        template<typename T> HRESULT InitializeTextElement(const std::shared_ptr<T>& sharedModel)
        {
            m_subtle = sharedModel->GetIsSubtle();
            m_italic = sharedModel->GetItalic();
            m_strikethrough = sharedModel->GetStrikethrough();
            m_fontStyle = static_cast<ABI::AdaptiveNamespace::FontStyle>(sharedModel->GetFontStyle());
            m_textSize = static_cast<ABI::AdaptiveNamespace::TextSize>(sharedModel->GetTextSize());
            m_textWeight = static_cast<ABI::AdaptiveNamespace::TextWeight>(sharedModel->GetTextWeight());
            m_foregroundColor = static_cast<ABI::AdaptiveNamespace::ForegroundColor>(sharedModel->GetTextColor());

            RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetText(), m_text.GetAddressOf()));
            RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetLanguage(), m_language.GetAddressOf()));
            return S_OK;
        }

        template<typename T> HRESULT SetTextElementProperties(std::shared_ptr<T> sharedCardElement)
        {
            sharedCardElement->SetIsSubtle(m_subtle);
            sharedCardElement->SetItalic(m_italic);
            sharedCardElement->SetStrikethrough(m_strikethrough);
            sharedCardElement->SetFontStyle(static_cast<AdaptiveSharedNamespace::FontStyle>(m_fontStyle));
            sharedCardElement->SetTextSize(static_cast<AdaptiveSharedNamespace::TextSize>(m_textSize));
            sharedCardElement->SetTextWeight(static_cast<AdaptiveSharedNamespace::TextWeight>(m_textWeight));
            sharedCardElement->SetTextColor(static_cast<AdaptiveSharedNamespace::ForegroundColor>(m_foregroundColor));

            std::string text;
            RETURN_IF_FAILED(HStringToUTF8(m_text.Get(), text));
            sharedCardElement->SetText(text);

            if (!(WindowsIsStringEmpty(m_language.Get())))
            {
                std::string language;
                RETURN_IF_FAILED(HStringToUTF8(m_language.Get(), language));
                sharedCardElement->SetLanguage(language);
            }
            return S_OK;
        }

    private:
        boolean m_subtle;
        boolean m_italic;
        boolean m_strikethrough;
        Microsoft::WRL::Wrappers::HString m_text;
        Microsoft::WRL::Wrappers::HString m_language;
        ABI::AdaptiveNamespace::FontStyle m_fontStyle;
        ABI::AdaptiveNamespace::TextSize m_textSize;
        ABI::AdaptiveNamespace::TextWeight m_textWeight;
        ABI::AdaptiveNamespace::ForegroundColor m_foregroundColor;
    };
}
