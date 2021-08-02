// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::ObjectModel::Uwp
{
    class DECLSPEC_UUID("CDCCC115-7C53-4A04-9F5B-754BBC00C80E") AdaptiveActionElementBase : public IUnknown
    {
    protected:
        HRESULT InitializeBaseElement(const std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedModel);

        IFACEMETHODIMP get_InternalId(_Out_ UINT32* id);

        IFACEMETHODIMP get_ActionTypeString(_Outptr_ HSTRING* value);

        IFACEMETHODIMP get_Title(_Outptr_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);

        IFACEMETHODIMP get_Id(_Outptr_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_FallbackType(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType* fallback);
        IFACEMETHODIMP put_FallbackType(ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType fallback);
        IFACEMETHODIMP get_FallbackContent(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement** content);
        IFACEMETHODIMP put_FallbackContent(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* content);

        IFACEMETHODIMP get_IconUrl(_Outptr_ HSTRING* iconUrl);
        IFACEMETHODIMP put_IconUrl(_In_ HSTRING iconUrl);

        IFACEMETHODIMP get_Style(_Outptr_ HSTRING* style);
        IFACEMETHODIMP put_Style(_In_ HSTRING style);

        IFACEMETHODIMP get_Tooltip(_Outptr_ HSTRING* tooltip);
        IFACEMETHODIMP put_Tooltip(_In_ HSTRING tooltip);

        IFACEMETHODIMP get_IsEnabled(_Out_ boolean* isEnabled);
        IFACEMETHODIMP put_IsEnabled(boolean isEnabled);

        IFACEMETHODIMP get_AdditionalProperties(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value);

        IFACEMETHODIMP ToJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT CopySharedElementProperties(AdaptiveCards::BaseActionElement& sharedCardElement);

        virtual HRESULT GetSharedModel(std::shared_ptr<BaseActionElement>& sharedModel) = 0;

    private:
        Microsoft::WRL::Wrappers::HString m_id;
        Microsoft::WRL::Wrappers::HString m_title;
        Microsoft::WRL::Wrappers::HString m_iconUrl;
        Microsoft::WRL::Wrappers::HString m_style;
        Microsoft::WRL::Wrappers::HString m_tooltip;
        Microsoft::WRL::ComPtr<ABI::Windows::Data::Json::IJsonObject> m_additionalProperties;
        Microsoft::WRL::Wrappers::HString m_typeString;
        boolean m_isEnabled;
        UINT32 m_internalId;
        ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType m_fallbackType;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement> m_fallbackContent;
    };
}
