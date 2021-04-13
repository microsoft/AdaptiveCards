// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("4BC6640A-8FBE-4DE0-81FD-119BC10877F1") AdaptiveTextElement : public IUnknown
    {
    public:
        IFACEMETHODIMP get_Text(_Outptr_ HSTRING* text);
        IFACEMETHODIMP put_Text(_In_ HSTRING text);

        IFACEMETHODIMP get_Size(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::TextSize>** textSize);
        IFACEMETHODIMP put_Size(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::TextSize>* textSize);

        IFACEMETHODIMP get_Weight(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::TextWeight>** textWeight);
        IFACEMETHODIMP put_Weight(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::TextWeight>* textWeight);

        IFACEMETHODIMP get_Color(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::ForegroundColor>** textColor);
        IFACEMETHODIMP put_Color(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::ForegroundColor>* textColor);

        IFACEMETHODIMP get_IsSubtle(_Outptr_ ABI::Windows::Foundation::IReference<bool>** isSubtle);
        IFACEMETHODIMP put_IsSubtle(_In_ ABI::Windows::Foundation::IReference<bool>* isSubtle);

        IFACEMETHODIMP get_Language(_Outptr_ HSTRING* language);
        IFACEMETHODIMP put_Language(_In_ HSTRING language);

        IFACEMETHODIMP get_FontType(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::FontType>** fontType);
        IFACEMETHODIMP put_FontType(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::FontType>* fontType);

    protected:
        template<typename T> HRESULT InitializeTextElement(const std::shared_ptr<T>& sharedModel)
        {
            if (sharedModel->GetIsSubtle().has_value())
            {
                m_subtle = winrt::box_value(sharedModel->GetIsSubtle().value())
                               .as<ABI::Windows::Foundation::IReference<bool>>()
                               .get();
            }

            if (sharedModel->GetFontType().has_value())
            {
                m_fontType =
                    winrt::box_value(static_cast<winrt::AdaptiveNamespace::FontType>(sharedModel->GetFontType().value()))
                        .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::Rendering::Uwp::FontType>>()
                        .get();
            }

            if (sharedModel->GetTextSize().has_value())
            {
                m_textSize =
                    winrt::box_value(static_cast<winrt::AdaptiveNamespace::TextSize>(sharedModel->GetTextSize().value()))
                        .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::TextSize>>()
                        .get();
            }

            if (sharedModel->GetTextWeight().has_value())
            {
                m_textWeight =
                    winrt::box_value(static_cast<winrt::AdaptiveNamespace::TextWeight>(sharedModel->GetTextWeight().value()))
                        .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::TextWeight>>()
                        .get();
            }

            if (sharedModel->GetTextColor().has_value())
            {
                m_foregroundColor =
                    winrt::box_value(static_cast<winrt::AdaptiveNamespace::ForegroundColor>(sharedModel->GetTextColor().value()))
                        .as<ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::ForegroundColor>>()
                        .get();
            }

            RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetText(), m_text.GetAddressOf()));
            RETURN_IF_FAILED(UTF8ToHString(sharedModel->GetLanguage(), m_language.GetAddressOf()));
            return S_OK;
        }

        template<typename T> HRESULT CopyTextElementProperties(T& sharedCardElement)
        {
            if (m_subtle != nullptr)
            {
                sharedCardElement.SetIsSubtle(m_subtle);
            }

            if (m_fontType != nullptr)
            {
                ABI::AdaptiveNamespace::FontType fontTypeValue;
                RETURN_IF_FAILED(m_fontType->get_Value(&fontTypeValue));
                sharedCardElement.SetFontType(static_cast<AdaptiveSharedNamespace::FontType>(fontTypeValue));
            }

            if (m_textSize != nullptr)
            {
                ABI::AdaptiveNamespace::TextSize textSizeValue;
                RETURN_IF_FAILED(m_textSize->get_Value(&textSizeValue));
                sharedCardElement.SetTextSize(static_cast<AdaptiveSharedNamespace::TextSize>(textSizeValue));
            }

            if (m_textWeight != nullptr)
            {
                ABI::AdaptiveNamespace::TextWeight textWeightValue;
                RETURN_IF_FAILED(m_textWeight->get_Value(&textWeightValue));
                sharedCardElement.SetTextWeight(static_cast<AdaptiveSharedNamespace::TextWeight>(textWeightValue));
            }

            if (m_foregroundColor != nullptr)
            {
                ABI::AdaptiveNamespace::ForegroundColor foregroundColorValue;
                RETURN_IF_FAILED(m_foregroundColor->get_Value(&foregroundColorValue));
                sharedCardElement.SetTextColor(static_cast<AdaptiveSharedNamespace::ForegroundColor>(foregroundColorValue));
            }

            std::string text;
            RETURN_IF_FAILED(HStringToUTF8(m_text.Get(), text));
            sharedCardElement.SetText(text);

            if (!(WindowsIsStringEmpty(m_language.Get())))
            {
                std::string language;
                RETURN_IF_FAILED(HStringToUTF8(m_language.Get(), language));
                sharedCardElement.SetLanguage(language);
            }
            return S_OK;
        }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<bool>> m_subtle;
        Microsoft::WRL::Wrappers::HString m_text;
        Microsoft::WRL::Wrappers::HString m_language;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::FontType>> m_fontType;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::TextSize>> m_textSize;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::TextWeight>> m_textWeight;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveNamespace::ForegroundColor>> m_foregroundColor;
    };
}
