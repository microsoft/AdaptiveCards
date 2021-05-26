// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "RichTextBlock.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class DECLSPEC_UUID("0c87566c-a58c-4332-8b3b-79c9714074f6") AdaptiveRichTextBlock
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRichTextBlock,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::CloakedIid<AdaptiveCards::Rendering::Uwp::AdaptiveCardElementBase>>
    {
        AdaptiveRuntime(AdaptiveRichTextBlock);

    public:
        AdaptiveRichTextBlock();

        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::RichTextBlock>& sharedRichTextBlock) noexcept;

        // IAdaptiveRichTextBlock
        IFACEMETHODIMP get_HorizontalAlignment(
            _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::Rendering::Uwp::HAlignment>** horizontalAlignment) override;
        IFACEMETHODIMP put_HorizontalAlignment(
            _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::Rendering::Uwp::HAlignment>* horizontalAlignment) override;

        IFACEMETHODIMP get_Inlines(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInline*>** inlines);

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ElementType* elementType);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::Rendering::Uwp::Spacing* spacing)
        {
            return AdaptiveCardElementBase::get_Spacing(spacing);
        }
        IFACEMETHODIMP put_Spacing(ABI::AdaptiveCards::Rendering::Uwp::Spacing spacing)
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

        IFACEMETHODIMP get_FallbackType(_Out_ ABI::AdaptiveCards::Rendering::Uwp::FallbackType* fallback)
        {
            return AdaptiveCardElementBase::get_FallbackType(fallback);
        }
        IFACEMETHODIMP put_FallbackType(ABI::AdaptiveCards::Rendering::Uwp::FallbackType fallback)
        {
            return AdaptiveCardElementBase::put_FallbackType(fallback);
        }

        IFACEMETHODIMP get_FallbackContent(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement** content)
        {
            return AdaptiveCardElementBase::get_FallbackContent(content);
        }
        IFACEMETHODIMP put_FallbackContent(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement* content)
        {
            return AdaptiveCardElementBase::put_FallbackContent(content);
        }

        IFACEMETHODIMP get_Requirements(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveRequirement*>** requirements)
        {
            return AdaptiveCardElementBase::get_Requirements(requirements);
        }

        IFACEMETHODIMP ToJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result)
        {
            return AdaptiveCardElementBase::ToJson(result);
        }

        virtual HRESULT GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel) noexcept override;

        IFACEMETHODIMP get_Height(_Out_ ABI::AdaptiveCards::Rendering::Uwp::HeightType* height)
        {
            return AdaptiveCardElementBase::get_Height(height);
        }
        IFACEMETHODIMP put_Height(ABI::AdaptiveCards::Rendering::Uwp::HeightType height)
        {
            return AdaptiveCardElementBase::put_Height(height);
        }

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::Rendering::Uwp::HAlignment>> m_horizontalAlignment;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInline*>> m_inlines;
    };

    ActivatableClass(AdaptiveRichTextBlock);
}
