// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace winrt::AdaptiveCards::ObjectModel::WinUI3::implementation
{
    struct AdaptiveActionElementBase
    {
        property<hstring> Id;
        property<hstring> Title;
        property<hstring> IconUrl;
        property<hstring> Style;
        property<hstring> Tooltip;
        property<uint32_t> InternalId;
        property<winrt::Windows::Data::Json::JsonObject> AdditionalProperties;

        property<IAdaptiveActionElement> FallbackContent;
        property<ActionMode> Mode;
        property<hstring> ActionTypeString;
        property<bool> IsEnabled;

        virtual std::shared_ptr<::AdaptiveCards::BaseActionElement> GetSharedModel() = 0;

        winrt::Windows::Data::Json::JsonObject ToJson() { return StringToJsonObject(GetSharedModel()->Serialize()); }

        void CopySharedElementProperties(::AdaptiveCards::BaseActionElement& sharedCardElement)
        {
            sharedCardElement.SetId(HStringToUTF8(Id));
            sharedCardElement.SetTitle(HStringToUTF8(Title));
            sharedCardElement.SetIconUrl(HStringToUTF8(IconUrl));
            sharedCardElement.SetStyle(HStringToUTF8(Style));
            sharedCardElement.SetTooltip(HStringToUTF8(Tooltip));
            sharedCardElement.SetFallbackType(MapWinUI3FallbackTypeToShared(m_fallbackType));
            sharedCardElement.SetIsEnabled(IsEnabled.get());
            sharedCardElement.SetMode(static_cast<::AdaptiveCards::Mode>(Mode.get()));

            if (m_fallbackType == FallbackType::Content)
            {
                auto fallbackSharedModel = GenerateSharedAction(FallbackContent);
                sharedCardElement.SetFallbackContent(std::static_pointer_cast<::AdaptiveCards::BaseElement>(fallbackSharedModel));
            }

            if (AdditionalProperties.get() != nullptr)
            {
                sharedCardElement.SetAdditionalProperties(JsonObjectToJsonCpp(AdditionalProperties));
            }
        }

        void InitializeBaseElement(const std::shared_ptr<::AdaptiveCards::BaseActionElement>& sharedModel)
        {
            Id = UTF8ToHString(sharedModel->GetId());
            Title = UTF8ToHString(sharedModel->GetTitle());

            AdditionalProperties = JsonCppToJsonObject(sharedModel->GetAdditionalProperties());
            ActionTypeString = UTF8ToHString(sharedModel->GetElementTypeString());

            IconUrl = UTF8ToHString(sharedModel->GetIconUrl());
            Style = UTF8ToHString(sharedModel->GetStyle());
            Tooltip = UTF8ToHString(sharedModel->GetTooltip());
            Mode = static_cast<WinUI3::ActionMode>(sharedModel->GetMode());

            IsEnabled = sharedModel->GetIsEnabled();

            InternalId = sharedModel->GetInternalId().Hash();
            m_fallbackType = static_cast<WinUI3::FallbackType>(MapSharedFallbackTypeToWinUI3(sharedModel->GetFallbackType()));
            if (m_fallbackType == WinUI3::FallbackType::Content)
            {
                if (auto fallback = std::static_pointer_cast<::AdaptiveCards::BaseActionElement>(sharedModel->GetFallbackContent()))
                {
                    FallbackContent = GenerateActionProjection(fallback);
                }
            }
        }

        WinUI3::FallbackType FallbackType() { return m_fallbackType; }
        void FallbackType(WinUI3::FallbackType const& fallback)
        {
            if (fallback != WinUI3::FallbackType::Content)
            {
                FallbackContent = nullptr;
            }
            m_fallbackType = fallback;
        }

        WinUI3::FallbackType m_fallbackType;
    };
}

namespace AdaptiveCards::ObjectModel::WinUI3
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

        IFACEMETHODIMP get_FallbackType(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::FallbackType* fallback);
        IFACEMETHODIMP put_FallbackType(ABI::AdaptiveCards::ObjectModel::WinUI3::FallbackType fallback);
        IFACEMETHODIMP get_FallbackContent(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement** content);
        IFACEMETHODIMP put_FallbackContent(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* content);

        IFACEMETHODIMP get_IconUrl(_Outptr_ HSTRING* iconUrl);
        IFACEMETHODIMP put_IconUrl(_In_ HSTRING iconUrl);

        IFACEMETHODIMP get_Style(_Outptr_ HSTRING* style);
        IFACEMETHODIMP put_Style(_In_ HSTRING style);

        IFACEMETHODIMP get_Tooltip(_Outptr_ HSTRING* tooltip);
        IFACEMETHODIMP put_Tooltip(_In_ HSTRING tooltip);

        IFACEMETHODIMP get_IsEnabled(_Out_ boolean* isEnabled);
        IFACEMETHODIMP put_IsEnabled(boolean isEnabled);

        IFACEMETHODIMP get_Mode(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::ActionMode* mode);
        IFACEMETHODIMP put_Mode(ABI::AdaptiveCards::ObjectModel::WinUI3::ActionMode mode);

        IFACEMETHODIMP get_AdditionalProperties(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value);

        IFACEMETHODIMP ToJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT CopySharedElementProperties(AdaptiveCards::BaseActionElement& sharedCardElement);

        virtual std::shared_ptr<BaseActionElement> GetSharedModel() = 0;

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
        ABI::AdaptiveCards::ObjectModel::WinUI3::FallbackType m_fallbackType;
        winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement m_fallbackContent;
        ABI::AdaptiveCards::ObjectModel::WinUI3::ActionMode m_mode;
    };
}
