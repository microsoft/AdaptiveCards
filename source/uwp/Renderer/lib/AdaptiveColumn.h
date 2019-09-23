// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveBackgroundImage.h"
#include "Column.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("d674610a-a76b-4283-bd09-b5a25c41433d") AdaptiveColumn
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveColumn,
                                              ABI::AdaptiveNamespace::IAdaptiveContainerBase,
                                              ABI::AdaptiveNamespace::IAdaptiveCardElement,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::CloakedIid<AdaptiveNamespace::AdaptiveCardElementBase>>
    {
        AdaptiveRuntime(AdaptiveColumn);

    public:
        AdaptiveColumn();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Column>& sharedColumn);

        // IAdaptiveColumn
        IFACEMETHODIMP get_Width(_Outptr_ HSTRING* width);
        IFACEMETHODIMP put_Width(_In_ HSTRING width);

        IFACEMETHODIMP get_PixelWidth(_Out_ UINT32* pixelWidth);
        IFACEMETHODIMP put_PixelWidth(UINT32 pixelWidth);

        IFACEMETHODIMP get_Items(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>** items);

        IFACEMETHODIMP get_VerticalContentAlignment(_Out_ ABI::AdaptiveNamespace::VerticalContentAlignment* verticalAlignment);
        IFACEMETHODIMP put_VerticalContentAlignment(ABI::AdaptiveNamespace::VerticalContentAlignment verticalAlignment);

        IFACEMETHODIMP get_BackgroundImage(_Outptr_ ABI::AdaptiveNamespace::IAdaptiveBackgroundImage** backgroundImage);
        IFACEMETHODIMP put_BackgroundImage(_In_ ABI::AdaptiveNamespace::IAdaptiveBackgroundImage* backgroundImage);

        // IAdaptiveContainerBase
        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveNamespace::ContainerStyle* style);
        IFACEMETHODIMP put_Style(ABI::AdaptiveNamespace::ContainerStyle style);

        IFACEMETHODIMP get_SelectAction(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** action);
        IFACEMETHODIMP put_SelectAction(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* action);

        IFACEMETHODIMP get_Bleed(_Out_ boolean* bleed);
        IFACEMETHODIMP put_Bleed(boolean bleed);

        IFACEMETHODIMP get_BleedDirection(_Out_ ABI::AdaptiveNamespace::BleedDirection* bleedDirection);

        IFACEMETHODIMP get_MinHeight(_Out_ UINT32* minHeight);
        IFACEMETHODIMP put_MinHeight(UINT32 minHeight);

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

        IFACEMETHODIMP MeetsRequirements(_In_ ABI::AdaptiveNamespace::IAdaptiveFeatureRegistration* featureRegistration,
                                         _Out_ boolean* value)
        {
            return AdaptiveCardElementBase::MeetsRequirements(featureRegistration, value);
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
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::IAdaptiveCardElement*>> m_items;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveActionElement> m_selectAction;

        Microsoft::WRL::Wrappers::HString m_width;
        UINT32 m_pixelWidth;
        ABI::AdaptiveNamespace::ContainerStyle m_style;
        ABI::AdaptiveNamespace::VerticalContentAlignment m_verticalAlignment;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveBackgroundImage> m_backgroundImage;
        UINT32 m_minHeight;
        boolean m_bleed;
        ABI::AdaptiveNamespace::BleedDirection m_bleedDirection;
    };

    ActivatableClass(AdaptiveColumn);
}
