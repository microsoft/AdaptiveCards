#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "SubmitAction.h"

AdaptiveNamespaceStart
    class DECLSPEC_UUID("32114ce2-7e10-4f7f-8225-bfd661c6794c") AdaptiveSubmitAction :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveSubmitAction,
            ABI::AdaptiveNamespace::IAdaptiveActionElement,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveSubmitAction)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveSharedNamespace::SubmitAction>& sharedSubmitAction);

        // IAdaptiveActionElement
        IFACEMETHODIMP get_ActionType(_Out_ ABI::AdaptiveNamespace::ActionType* actionType);
        IFACEMETHODIMP get_ActionTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP get_Title(_Out_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);

        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_DataJson(_Out_ ABI::Windows::Data::Json::IJsonValue** data);
        IFACEMETHODIMP put_DataJson(_In_ ABI::Windows::Data::Json::IJsonValue* data);

        IFACEMETHODIMP get_AdditionalProperties(_Out_ ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT GetSharedModel(_In_ std::shared_ptr<AdaptiveSharedNamespace::SubmitAction>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        std::shared_ptr<AdaptiveSharedNamespace::SubmitAction> m_sharedSubmitAction;
    };

    ActivatableClass(AdaptiveSubmitAction);
AdaptiveNamespaceEnd