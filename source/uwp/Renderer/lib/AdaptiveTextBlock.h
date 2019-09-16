// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "TextBlock.h"
#include "AdaptiveCardElement.h"
#include "AdaptiveTextElement.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("0c87566c-a58c-4332-8b3b-79c9714074f6") AdaptiveTextBlock
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveTextBlock,
                                              ABI::AdaptiveNamespace::IAdaptiveTextElement,
                                              ABI::AdaptiveNamespace::IAdaptiveCardElement,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::CloakedIid<AdaptiveNamespace::AdaptiveCardElementBase>,
                                              Microsoft::WRL::CloakedIid<AdaptiveNamespace::AdaptiveTextElement>>
    {
        AdaptiveRuntime(AdaptiveTextBlock);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::TextBlock>& sharedTextBlock);

        // IAdaptiveTextBlock
        IFACEMETHODIMP get_Wrap(_Out_ boolean* wrap);
        IFACEMETHODIMP put_Wrap(boolean wrap);

        IFACEMETHODIMP get_MaxLines(_Out_ UINT32* value);
        IFACEMETHODIMP put_MaxLines(UINT32 value);

        IFACEMETHODIMP get_HorizontalAlignment(_Out_ ABI::AdaptiveNamespace::HAlignment* HorizontalAlignment);
        IFACEMETHODIMP put_HorizontalAlignment(ABI::AdaptiveNamespace::HAlignment HorizontalAlignment);

        // IAdaptiveTextElement
        IFACEMETHODIMP get_Text(_Outptr_ HSTRING* text) { return AdaptiveTextElement::get_Text(text); }
        IFACEMETHODIMP put_Text(_In_ HSTRING text) { return AdaptiveTextElement::put_Text(text); }

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveNamespace::TextSize* textSize)
        {
            return AdaptiveTextElement::get_Size(textSize);
        }
        IFACEMETHODIMP put_Size(ABI::AdaptiveNamespace::TextSize textSize)
        {
            return AdaptiveTextElement::put_Size(textSize);
        }

        IFACEMETHODIMP get_Weight(_Out_ ABI::AdaptiveNamespace::TextWeight* textWeight)
        {
            return AdaptiveTextElement::get_Weight(textWeight);
        }
        IFACEMETHODIMP put_Weight(ABI::AdaptiveNamespace::TextWeight textWeight)
        {
            return AdaptiveTextElement::put_Weight(textWeight);
        }

        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveNamespace::ForegroundColor* textColor)
        {
            return AdaptiveTextElement::get_Color(textColor);
        }
        IFACEMETHODIMP put_Color(ABI::AdaptiveNamespace::ForegroundColor textColor)
        {
            return AdaptiveTextElement::put_Color(textColor);
        }

        IFACEMETHODIMP get_IsSubtle(_Out_ boolean* isSubtle) { return AdaptiveTextElement::get_IsSubtle(isSubtle); }
        IFACEMETHODIMP put_IsSubtle(boolean isSubtle) { return AdaptiveTextElement::put_IsSubtle(isSubtle); }

        IFACEMETHODIMP get_Language(_Outptr_ HSTRING* language) { return AdaptiveTextElement::get_Language(language); }
        IFACEMETHODIMP put_Language(_In_ HSTRING language) { return AdaptiveTextElement::put_Language(language); }

        IFACEMETHODIMP get_FontType(_Out_ ABI::AdaptiveNamespace::FontType* type)
        {
            return AdaptiveTextElement::get_FontType(type);
        }
        IFACEMETHODIMP put_FontType(ABI::AdaptiveNamespace::FontType type)
        {
            return AdaptiveTextElement::put_FontType(type);
        }

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveNamespace::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveNamespace::Spacing* spacing)
        {
            return AdaptiveCardElementBase::get_Spacing(spacing);
        }
        IFACEMETHODIMP put_Spacing(ABI::AdaptiveNamespace::Spacing spacing)
        {
            return AdaptiveCardElementBase::put_Spacing(spacing);
        }

        IFACEMETHODIMP get_Separator(_Out_ boolean* separator)
        {
            return AdaptiveCardElementBase::get_Separator(separator);
        }
        IFACEMETHODIMP put_Separator(boolean separator) { return AdaptiveCardElementBase::put_Separator(separator); }

        IFACEMETHODIMP get_IsVisible(_Out_ boolean* isVisible)
        {
            return AdaptiveCardElementBase::get_IsVisible(isVisible);
        }
        IFACEMETHODIMP put_IsVisible(boolean isVisible) { return AdaptiveCardElementBase::put_IsVisible(isVisible); }

        IFACEMETHODIMP get_Id(_Outptr_ HSTRING* id) { return AdaptiveCardElementBase::get_Id(id); }
        IFACEMETHODIMP put_Id(_In_ HSTRING id) { return AdaptiveCardElementBase::put_Id(id); }

        IFACEMETHODIMP get_FallbackType(_Out_ ABI::AdaptiveNamespace::FallbackType* fallback)
        {
            return AdaptiveCardElementBase::get_FallbackType(fallback);
        }
        IFACEMETHODIMP get_FallbackContent(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** content)
        {
            return AdaptiveCardElementBase::get_FallbackContent(content);
        }

        IFACEMETHODIMP put_FallbackType(ABI::AdaptiveNamespace::FallbackType fallback)
        {
            return AdaptiveCardElementBase::put_FallbackType(fallback);
        }

        IFACEMETHODIMP put_FallbackContent(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* content)
        {
            return AdaptiveCardElementBase::put_FallbackContent(content);
        }

        IFACEMETHODIMP get_ElementTypeString(_Outptr_ HSTRING* value)
        {
            return AdaptiveCardElementBase::get_ElementTypeString(value);
        }

        IFACEMETHODIMP get_AdditionalProperties(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result)
        {
            return AdaptiveCardElementBase::get_AdditionalProperties(result);
        }
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value)
        {
            return AdaptiveCardElementBase::put_AdditionalProperties(value);
        }

        IFACEMETHODIMP get_Requirements(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveRequirement*>** requirements)
        {
            return AdaptiveCardElementBase::get_Requirements(requirements);
        }

        IFACEMETHODIMP ToJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result)
        {
            return AdaptiveCardElementBase::ToJson(result);
        }

        virtual HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel) override;

        IFACEMETHODIMP get_Height(_Out_ ABI::AdaptiveNamespace::HeightType* height)
        {
            return AdaptiveCardElementBase::get_Height(height);
        }
        IFACEMETHODIMP put_Height(ABI::AdaptiveNamespace::HeightType height)
        {
            return AdaptiveCardElementBase::put_Height(height);
        }

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        boolean m_wrap;
        UINT32 m_maxLines;
        ABI::AdaptiveNamespace::HAlignment m_horizontalAlignment;
    };

    ActivatableClass(AdaptiveTextBlock);
}
