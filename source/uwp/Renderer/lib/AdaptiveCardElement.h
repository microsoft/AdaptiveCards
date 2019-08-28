// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "SemanticVersion.h"
#include "BaseElement.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("49496982-18E7-48A8-9D16-99E389BE9133") AdaptiveCardElementBase : public IUnknown
    {
    public:
        InternalId GetInternalId() { return m_internalId; }

    protected:
        HRESULT InitializeBaseElement(const std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement>& sharedModel);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveNamespace::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(ABI::AdaptiveNamespace::Spacing spacing);

        IFACEMETHODIMP get_Separator(_Out_ boolean* separator);
        IFACEMETHODIMP put_Separator(boolean separator);

        IFACEMETHODIMP get_Id(_Outptr_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_IsVisible(_Out_ boolean* separator);
        IFACEMETHODIMP put_IsVisible(boolean separator);

        IFACEMETHODIMP get_FallbackType(_Out_ ABI::AdaptiveNamespace::FallbackType* fallback);
        IFACEMETHODIMP put_FallbackType(ABI::AdaptiveNamespace::FallbackType fallback);
        IFACEMETHODIMP get_FallbackContent(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardElement** content);
        IFACEMETHODIMP put_FallbackContent(_In_ ABI::AdaptiveNamespace::IAdaptiveCardElement* content);

        IFACEMETHODIMP get_ElementTypeString(_Outptr_ HSTRING* type);

        IFACEMETHODIMP get_AdditionalProperties(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* jsonObject);

        IFACEMETHODIMP get_Height(_Out_ ABI::AdaptiveNamespace::HeightType* height);
        IFACEMETHODIMP put_Height(ABI::AdaptiveNamespace::HeightType height);

        IFACEMETHODIMP get_Requirements(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveRequirement*>** requirements);

        IFACEMETHODIMP ToJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT SetSharedElementProperties(std::shared_ptr<AdaptiveSharedNamespace::BaseCardElement> sharedCardElement);

        virtual HRESULT GetSharedModel(std::shared_ptr<BaseCardElement>& sharedModel) = 0;

    private:
        boolean m_separator;
        boolean m_isVisible;
        Microsoft::WRL::Wrappers::HString m_id;
        ABI::AdaptiveNamespace::Spacing m_spacing;
        Microsoft::WRL::ComPtr<ABI::Windows::Data::Json::IJsonObject> m_additionalProperties;
        Microsoft::WRL::Wrappers::HString m_typeString;
        ABI::AdaptiveNamespace::HeightType m_height;
        InternalId m_internalId;
        ABI::AdaptiveNamespace::FallbackType m_fallbackType;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardElement> m_fallbackContent;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveRequirement*>> m_requirements;
    };
}
