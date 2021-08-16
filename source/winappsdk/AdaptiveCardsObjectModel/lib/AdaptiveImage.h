// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Image.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class DECLSPEC_UUID("c940ac19-5faa-47f3-9d4b-f4d8e7d6ec1d") AdaptiveImage
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveImage,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::CloakedIid<AdaptiveCards::ObjectModel::Uwp::AdaptiveCardElementBase>>
    {
        AdaptiveRuntime(AdaptiveImage);

    public:
        AdaptiveImage();
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Image>& sharedImage);

        // IAdaptiveImage
        IFACEMETHODIMP get_Url(_Outptr_ HSTRING* uri) override;
        IFACEMETHODIMP put_Url(_In_ HSTRING uri) override;

        IFACEMETHODIMP get_BackgroundColor(_Outptr_ HSTRING* backgroundColor) override;
        IFACEMETHODIMP put_BackgroundColor(_In_ HSTRING backgroundColor) override;

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ImageStyle* imageStyle) override;
        IFACEMETHODIMP put_Style(ABI::AdaptiveCards::ObjectModel::Uwp::ImageStyle imageStyle) override;

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize* imageSize) override;
        IFACEMETHODIMP put_Size(ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize imageSize) override;

        IFACEMETHODIMP get_PixelWidth(_Out_ UINT32* Width) override;
        IFACEMETHODIMP put_PixelWidth(UINT32 Width) override;

        IFACEMETHODIMP get_PixelHeight(_Out_ UINT32* Height) override;
        IFACEMETHODIMP put_PixelHeight(UINT32 Height) override;

        IFACEMETHODIMP get_AltText(_Outptr_ HSTRING* text) override;
        IFACEMETHODIMP put_AltText(_In_ HSTRING text) override;

        IFACEMETHODIMP get_HorizontalAlignment(
            _COM_Outptr_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>** horizontalAlignment) override;
        IFACEMETHODIMP put_HorizontalAlignment(
            _In_ ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>* horizontalAlignment) override;

        IFACEMETHODIMP get_SelectAction(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement** action) override;
        IFACEMETHODIMP put_SelectAction(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* action) override;

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
        Microsoft::WRL::Wrappers::HString m_url;
        Microsoft::WRL::Wrappers::HString m_backgroundColor;
        ABI::AdaptiveCards::ObjectModel::Uwp::ImageStyle m_imageStyle;
        ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize m_imageSize;
        Microsoft::WRL::Wrappers::HString m_altText;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IReference<ABI::AdaptiveCards::ObjectModel::Uwp::HAlignment>> m_horizontalAlignment;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement> m_selectAction;
        UINT32 m_pixelWidth;
        UINT32 m_pixelHeight;
    };

    ActivatableClass(AdaptiveImage);
}
