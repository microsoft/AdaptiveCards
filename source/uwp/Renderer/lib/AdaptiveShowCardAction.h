#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "ShowCardAction.h"

AdaptiveNamespaceStart
    class DECLSPEC_UUID("429d6be9-a5f4-44dc-8dc3-3fe9b633ff1c") AdaptiveShowCardAction :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveShowCardAction,
            ABI::AdaptiveNamespace::IAdaptiveActionElement,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        AdaptiveRuntime(AdaptiveShowCardAction)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveSharedNamespace::ShowCardAction>& sharedShowCardAction);

        // IAdaptiveShowCardAction
        IFACEMETHODIMP get_Card(_Out_ ABI::AdaptiveNamespace::IAdaptiveCard** card);
        IFACEMETHODIMP put_Card(_Out_ ABI::AdaptiveNamespace::IAdaptiveCard* card);

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

        HRESULT GetSharedModel(_In_ std::shared_ptr<AdaptiveSharedNamespace::ShowCardAction>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCard> m_card;

        Microsoft::WRL::Wrappers::HString m_id;
        Microsoft::WRL::Wrappers::HString m_title;
        Microsoft::WRL::ComPtr<ABI::Windows::Data::Json::IJsonObject> m_additionalProperties;

    };

    ActivatableClass(AdaptiveShowCardAction);
AdaptiveNamespaceEnd