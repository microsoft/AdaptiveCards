// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveBackgroundImage.h"
#include "Column.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class DECLSPEC_UUID("d674610a-a76b-4283-bd09-b5a25c41433d") AdaptiveColumn
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveColumn,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveContainerBase,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::CloakedIid<AdaptiveCards::ObjectModel::Uwp::AdaptiveCardElementBase>>
    {
        AdaptiveRuntime(AdaptiveColumn);

    public:
        AdaptiveColumn();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Column>& sharedColumn);

        // IAdaptiveColumn
        IFACEMETHODIMP get_Width(_Outptr_ HSTRING* width) override;
        IFACEMETHODIMP put_Width(_In_ HSTRING width) override;

        IFACEMETHODIMP get_PixelWidth(_Out_ UINT32* pixelWidth) override;
        IFACEMETHODIMP put_PixelWidth(UINT32 pixelWidth) override;

        IFACEMETHODIMP get_Items(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement*>** items) override;

        IFACEMETHODIMP get_VerticalContentAlignment(
            _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>** verticalAlignment) override;
        IFACEMETHODIMP put_VerticalContentAlignment(
            _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>* verticalAlignment) override;

        IFACEMETHODIMP get_BackgroundImage(_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveBackgroundImage** backgroundImage) override;
        IFACEMETHODIMP put_BackgroundImage(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveBackgroundImage* backgroundImage) override;

        IFACEMETHODIMP get_Rtl(_COM_Outptr_ ABI::Windows::Foundation::IReference<bool>** value) override;
        IFACEMETHODIMP put_Rtl(_In_ ABI::Windows::Foundation::IReference<bool>* value) override;

        // IAdaptiveContainerBase
        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle* style) override;
        IFACEMETHODIMP put_Style(ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle style) override;

        IFACEMETHODIMP get_SelectAction(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement** action) override;
        IFACEMETHODIMP put_SelectAction(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* action) override;

        IFACEMETHODIMP get_Bleed(_Out_ boolean* bleed) override;
        IFACEMETHODIMP put_Bleed(boolean bleed) override;

        IFACEMETHODIMP get_BleedDirection(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection* bleedDirection) override;

        IFACEMETHODIMP get_MinHeight(_Out_ UINT32* minHeight) override;
        IFACEMETHODIMP put_MinHeight(UINT32 minHeight) override;

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

        IFACEMETHODIMP get_FallbackType(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType* fallback) override
        {
            return AdaptiveCardElementBase::get_FallbackType(fallback);
        }
        IFACEMETHODIMP get_FallbackContent(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement** content) override
        {
            return AdaptiveCardElementBase::get_FallbackContent(content);
        }

        IFACEMETHODIMP put_FallbackType(ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType fallback) override
        {
            return AdaptiveCardElementBase::put_FallbackType(fallback);
        }

        IFACEMETHODIMP put_FallbackContent(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* content) override
        {
            return AdaptiveCardElementBase::put_FallbackContent(content);
        }

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

        IFACEMETHODIMP get_Requirements(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveRequirement*>** requirements) override
        {
            return AdaptiveCardElementBase::get_Requirements(requirements);
        }

        IFACEMETHODIMP ToJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result) override
        {
            return AdaptiveCardElementBase::ToJson(result);
        }

        virtual HRESULT GetSharedModel(std::shared_ptr<AdaptiveCards::BaseCardElement>& sharedModel) override;

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
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement*>> m_items;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement> m_selectAction;

        Microsoft::WRL::Wrappers::HString m_width;
        UINT32 m_pixelWidth;
        ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle m_style;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::VerticalContentAlignment>> m_verticalContentAlignment;

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveBackgroundImage> m_backgroundImage;
        UINT32 m_minHeight;
        boolean m_bleed;
        ABI::AdaptiveCards::ObjectModel::Uwp::BleedDirection m_bleedDirection;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<bool>> m_rtl;
    };

    ActivatableClass(AdaptiveColumn);
}
