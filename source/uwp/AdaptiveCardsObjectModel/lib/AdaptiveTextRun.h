// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TextRun.h"
#include "AdaptiveTextElement.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class DECLSPEC_UUID("d37e5b66-2a5e-4a9e-b087-dbef5a1705b1") AdaptiveTextRun
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTextRun,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveTextElement,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInline,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::CloakedIid<AdaptiveCards::ObjectModel::Uwp::AdaptiveTextElement>>
    {
        AdaptiveRuntime(AdaptiveTextRun);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::TextRun>& sharedTextRun) noexcept;

        // IAdaptiveTextRun
        IFACEMETHODIMP get_Highlight(_Out_ boolean* highlight) override;
        IFACEMETHODIMP put_Highlight(boolean highlight) override;

        IFACEMETHODIMP get_SelectAction(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement** action) override;
        IFACEMETHODIMP put_SelectAction(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* action) override;

        IFACEMETHODIMP get_Italic(_Out_ boolean* italic) override;
        IFACEMETHODIMP put_Italic(boolean italic) override;

        IFACEMETHODIMP get_Strikethrough(_Out_ boolean* strikethrough) override;
        IFACEMETHODIMP put_Strikethrough(boolean strikethrough);

        IFACEMETHODIMP get_Underline(_Out_ boolean* underline) override;
        IFACEMETHODIMP put_Underline(boolean underline) override;

        // IAdaptiveTextElement
        IFACEMETHODIMP get_Text(_Outptr_ HSTRING* text) override { return AdaptiveTextElement::get_Text(text); }
        IFACEMETHODIMP put_Text(_In_ HSTRING text) override { return AdaptiveTextElement::put_Text(text); }

        IFACEMETHODIMP get_Size(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextSize>** textSize) override
        {
            return AdaptiveTextElement::get_Size(textSize);
        }
        IFACEMETHODIMP put_Size(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextSize>* textSize) override
        {
            return AdaptiveTextElement::put_Size(textSize);
        }

        IFACEMETHODIMP get_Weight(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight>** textWeight) override
        {
            return AdaptiveTextElement::get_Weight(textWeight);
        }
        IFACEMETHODIMP put_Weight(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight>* textWeight) override
        {
            return AdaptiveTextElement::put_Weight(textWeight);
        }

        IFACEMETHODIMP get_Color(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::ForegroundColor>** textColor) override
        {
            return AdaptiveTextElement::get_Color(textColor);
        }
        IFACEMETHODIMP put_Color(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::ForegroundColor>* textColor) override
        {
            return AdaptiveTextElement::put_Color(textColor);
        }

        IFACEMETHODIMP get_IsSubtle(_Outptr_ ABI::Windows::Foundation::IReference<bool>** isSubtle) override
        {
            return AdaptiveTextElement::get_IsSubtle(isSubtle);
        }
        IFACEMETHODIMP put_IsSubtle(ABI::Windows::Foundation::IReference<bool>* isSubtle) override
        {
            return AdaptiveTextElement::put_IsSubtle(isSubtle);
        }

        IFACEMETHODIMP get_Language(_Outptr_ HSTRING* language) override
        {
            return AdaptiveTextElement::get_Language(language);
        }
        IFACEMETHODIMP put_Language(_In_ HSTRING language) override
        {
            return AdaptiveTextElement::put_Language(language);
        }

        IFACEMETHODIMP get_FontType(_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::FontType>** type) override
        {
            return AdaptiveTextElement::get_FontType(type);
        }
        IFACEMETHODIMP put_FontType(_In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::FontType>* type) override
        {
            return AdaptiveTextElement::put_FontType(type);
        }

        HRESULT GetSharedModel(std::shared_ptr<AdaptiveCards::TextRun>& sharedModel) noexcept;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement> m_selectAction;
        boolean m_highlight;
        boolean m_italic;
        boolean m_strikethrough;
        boolean m_underline;
    };

    ActivatableClass(AdaptiveTextRun);
}
