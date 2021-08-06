// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "RichTextBlock.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class DECLSPEC_UUID("0c87566c-a58c-4332-8b3b-79c9714074f6") AdaptiveRichTextBlock
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveRichTextBlock,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::CloakedIid<AdaptiveCards::ObjectModel::Uwp::AdaptiveCardElementBase>>
    {
        AdaptiveRuntime(AdaptiveRichTextBlock);

    public:
        AdaptiveRichTextBlock();

        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::RichTextBlock>& sharedRichTextBlock) noexcept;

        // IAdaptiveRichTextBlock
        IFACEMETHODIMP get_HorizontalAlignment(
            _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>** horizontalAlignment) override;
        IFACEMETHODIMP put_HorizontalAlignment(
            _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>* horizontalAlignment) override;

        IFACEMETHODIMP get_Inlines(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInline*>** inlines) override;

        // IAdaptiveCardElement
        IFACEMETHODIMP get_ElementType(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ElementType* elementType) override;

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::Spacing* spacing) override
        {
            return AdaptiveCardElementBase::get_Spacing(spacing);
        }
        IFACEMETHODIMP put_Spacing(ABI::AdaptiveCards::ObjectModel::Uwp::Spacing spacing) override
        {
            return AdaptiveCardElementBase::put_Spacing(spacing);
        }

        IFACEMETHODIMP get_Separator(_Out_ boolean* separator) override
        {
            return AdaptiveCardElementBase::get_Separator(separator);
        }
        IFACEMETHODIMP put_Separator(boolean separator) override
        {
            return AdaptiveCardElementBase::put_Separator(separator);
        }

        IFACEMETHODIMP get_IsVisible(_Out_ boolean* isVisible) override
        {
            return AdaptiveCardElementBase::get_IsVisible(isVisible);
        }
        IFACEMETHODIMP put_IsVisible(boolean isVisible) override
        {
            return AdaptiveCardElementBase::put_IsVisible(isVisible);
        }

        IFACEMETHODIMP get_Id(_Outptr_ HSTRING* id) override { return AdaptiveCardElementBase::get_Id(id); }
        IFACEMETHODIMP put_Id(_In_ HSTRING id) override { return AdaptiveCardElementBase::put_Id(id); }

        IFACEMETHODIMP get_ElementTypeString(_Outptr_ HSTRING* value) override
        {
            return AdaptiveCardElementBase::get_ElementTypeString(value);
        }

        IFACEMETHODIMP get_AdditionalProperties(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result) override
        {
            return AdaptiveCardElementBase::get_AdditionalProperties(result);
        }
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value) override
        {
            return AdaptiveCardElementBase::put_AdditionalProperties(value);
        }

        IFACEMETHODIMP get_FallbackType(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType* fallback) override
        {
            return AdaptiveCardElementBase::get_FallbackType(fallback);
        }
        IFACEMETHODIMP put_FallbackType(ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType fallback) override
        {
            return AdaptiveCardElementBase::put_FallbackType(fallback);
        }

        IFACEMETHODIMP get_FallbackContent(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement** content) override
        {
            return AdaptiveCardElementBase::get_FallbackContent(content);
        }
        IFACEMETHODIMP put_FallbackContent(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* content) override
        {
            return AdaptiveCardElementBase::put_FallbackContent(content);
        }

        IFACEMETHODIMP get_Requirements(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveRequirement*>** requirements) override
        {
            return AdaptiveCardElementBase::get_Requirements(requirements);
        }

        IFACEMETHODIMP ToJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result) override
        {
            return AdaptiveCardElementBase::ToJson(result);
        }

        virtual HRESULT GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel) noexcept override;

        IFACEMETHODIMP get_Height(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::HeightType* height) override
        {
            return AdaptiveCardElementBase::get_Height(height);
        }
        IFACEMETHODIMP put_Height(ABI::AdaptiveCards::ObjectModel::Uwp::HeightType height) override
        {
            return AdaptiveCardElementBase::put_Height(height);
        }

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>> m_horizontalAlignment;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveInline*>> m_inlines;
    };

    ActivatableClass(AdaptiveRichTextBlock);
}
