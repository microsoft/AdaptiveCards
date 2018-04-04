#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "OpenUrlAction.h"

AdaptiveNamespaceStart
    class DECLSPEC_UUID("96c1ded5-1ef8-4aa8-8ccf-0bea96295ac8") AdaptiveOpenUrlAction :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveOpenUrlAction,
            ABI::AdaptiveNamespace::IAdaptiveActionElement,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveOpenUrlAction)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveSharedNamespace::OpenUrlAction>& sharedOpenUrlAction);

        // IAdaptiveOpenUrlAction
        IFACEMETHODIMP get_Url(_Out_ ABI::Windows::Foundation::IUriRuntimeClass** url);
        IFACEMETHODIMP put_Url(_In_ ABI::Windows::Foundation::IUriRuntimeClass* url);

        // IAdaptiveActionElement
        IFACEMETHODIMP get_ActionType(_Out_ ABI::AdaptiveNamespace::ActionType* actionType);
        IFACEMETHODIMP get_ActionTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP get_Title(_Out_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);

        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_AdditionalProperties(_Out_ ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT GetSharedModel(_In_ std::shared_ptr<AdaptiveSharedNamespace::OpenUrlAction>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        std::shared_ptr<AdaptiveSharedNamespace::OpenUrlAction> m_sharedOpenUrlAction;
    };

    ActivatableClass(AdaptiveOpenUrlAction);
AdaptiveNamespaceEnd