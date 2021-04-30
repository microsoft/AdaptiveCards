// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ExecuteAction.h"
#include "AdaptiveActionElement.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("05764D21-0053-4282-A254-10A93BA21D7B") AdaptiveExecuteAction
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveNamespace::IAdaptiveExecuteAction,
                                              ABI::AdaptiveNamespace::IAdaptiveActionElement,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::CloakedIid<AdaptiveNamespace::AdaptiveActionElementBase>>
    {
        AdaptiveRuntime(AdaptiveExecuteAction);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::ExecuteAction>& sharedExecuteAction);

        // IAdaptiveExecuteAction
        IFACEMETHODIMP get_DataJson(_COM_Outptr_ ABI::Windows::Data::Json::IJsonValue** data) override;
        IFACEMETHODIMP put_DataJson(_In_ ABI::Windows::Data::Json::IJsonValue* data) override;

        IFACEMETHODIMP get_AssociatedInputs(_Out_ ABI::AdaptiveNamespace::AssociatedInputs* associatedInputs) override;
        IFACEMETHODIMP put_AssociatedInputs(ABI::AdaptiveNamespace::AssociatedInputs associatedInputs) override;

        IFACEMETHODIMP get_Verb(_Outptr_ HSTRING* verb) override;
        IFACEMETHODIMP put_Verb(_In_ HSTRING verb) override;

        // IAdaptiveActionElement
        IFACEMETHODIMP get_ActionType(_Out_ ABI::AdaptiveNamespace::ActionType* actionType) override;
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

        IFACEMETHODIMP get_FallbackType(_Out_ ABI::AdaptiveNamespace::FallbackType* fallback) override
        {
            return AdaptiveActionElementBase::get_FallbackType(fallback);
        }

        IFACEMETHODIMP get_FallbackContent(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveActionElement** content) override
        {
            return AdaptiveActionElementBase::get_FallbackContent(content);
        }

        IFACEMETHODIMP put_FallbackType(ABI::AdaptiveNamespace::FallbackType fallback) override
        {
            return AdaptiveActionElementBase::put_FallbackType(fallback);
        }

        IFACEMETHODIMP put_FallbackContent(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* content) override
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

        virtual HRESULT GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedModel) override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override
        {
            void* returnPointer;
            returnPointer = PeekHelper(riid, this);
            if (returnPointer == nullptr)
            {
                returnPointer = PeekHelper(riid, (AdaptiveActionElementBase*)this);
            }

            return returnPointer;
        }

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Data::Json::IJsonValue> m_dataJson;
        ABI::AdaptiveNamespace::AssociatedInputs m_associatedInputs;
        Microsoft::WRL::Wrappers::HString m_verb;
    };

    ActivatableClass(AdaptiveExecuteAction);
}
