// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ShowCardAction.h"
#include "AdaptiveActionElement.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class DECLSPEC_UUID("429d6be9-a5f4-44dc-8dc3-3fe9b633ff1c") AdaptiveShowCardAction
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveShowCardAction,
                                              ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::CloakedIid<AdaptiveCards::ObjectModel::Uwp::AdaptiveActionElementBase>>
    {
        AdaptiveRuntime(AdaptiveShowCardAction);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ShowCardAction>& sharedShowCardAction);

        // IAdaptiveShowCardAction
        IFACEMETHODIMP get_Card(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard** card) override;
        IFACEMETHODIMP put_Card(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard* card) override;

        // IAdaptiveActionElement
        IFACEMETHODIMP get_ActionType(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ActionType* actionType) override;
        IFACEMETHODIMP get_ActionTypeString(_Outptr_ HSTRING* value) override
        {
            return AdaptiveActionElementBase::get_ActionTypeString(value);
        }

        IFACEMETHODIMP get_Title(_Outptr_ HSTRING* title) override
        {
            return AdaptiveActionElementBase::get_Title(title);
        }
        IFACEMETHODIMP put_Title(_In_ HSTRING title) override { return AdaptiveActionElementBase::put_Title(title); }

        IFACEMETHODIMP get_Id(_Outptr_ HSTRING* id) override { return AdaptiveActionElementBase::get_Id(id); }
        IFACEMETHODIMP put_Id(_In_ HSTRING id) override { return AdaptiveActionElementBase::put_Id(id); }

        IFACEMETHODIMP get_InternalId(_Out_ UINT32* id) override
        {
            return AdaptiveActionElementBase::get_InternalId(id);
        }

        IFACEMETHODIMP get_FallbackType(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType* fallback) override
        {
            return AdaptiveActionElementBase::get_FallbackType(fallback);
        }

        IFACEMETHODIMP get_FallbackContent(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement** content) override
        {
            return AdaptiveActionElementBase::get_FallbackContent(content);
        }

        IFACEMETHODIMP put_FallbackType(ABI::AdaptiveCards::ObjectModel::Uwp::FallbackType fallback) override
        {
            return AdaptiveActionElementBase::put_FallbackType(fallback);
        }

        IFACEMETHODIMP put_FallbackContent(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* content) override
        {
            return AdaptiveActionElementBase::put_FallbackContent(content);
        }

        IFACEMETHODIMP get_IconUrl(_Outptr_ HSTRING* iconUrl) override
        {
            return AdaptiveActionElementBase::get_IconUrl(iconUrl);
        }
        IFACEMETHODIMP put_IconUrl(_In_ HSTRING iconUrl) override
        {
            return AdaptiveActionElementBase::put_IconUrl(iconUrl);
        }

        IFACEMETHODIMP get_Style(_Outptr_ HSTRING* style) override
        {
            return AdaptiveActionElementBase::get_Style(style);
        }
        IFACEMETHODIMP put_Style(_In_ HSTRING style) override { return AdaptiveActionElementBase::put_Style(style); }

        IFACEMETHODIMP get_Tooltip(_Outptr_ HSTRING* tooltip) override
        {
            return AdaptiveActionElementBase::get_Tooltip(tooltip);
        }
        IFACEMETHODIMP put_Tooltip(_In_ HSTRING tooltip) override
        {
            return AdaptiveActionElementBase::put_Tooltip(tooltip);
        }

        IFACEMETHODIMP put_IsEnabled(boolean isEnabled) override
        {
            return AdaptiveActionElementBase::put_IsEnabled(isEnabled);
        }
        IFACEMETHODIMP get_IsEnabled(_Out_ boolean* isEnabled) override
        {
            return AdaptiveActionElementBase::get_IsEnabled(isEnabled);
        }

        IFACEMETHODIMP get_AdditionalProperties(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result) override
        {
            return AdaptiveActionElementBase::get_AdditionalProperties(result);
        }
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value) override
        {
            return AdaptiveActionElementBase::put_AdditionalProperties(value);
        }

        IFACEMETHODIMP ToJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonObject** result) override
        {
            return AdaptiveActionElementBase::ToJson(result);
        }

        virtual HRESULT GetSharedModel(std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedModel) override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard> m_card;
    };

    ActivatableClass(AdaptiveShowCardAction);
}
