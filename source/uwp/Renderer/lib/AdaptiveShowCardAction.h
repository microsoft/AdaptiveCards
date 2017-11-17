#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "ShowCardAction.h"

namespace AdaptiveCards { namespace Uwp
{
    class DECLSPEC_UUID("429d6be9-a5f4-44dc-8dc3-3fe9b633ff1c") AdaptiveShowCardAction :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveShowCardAction,
            ABI::AdaptiveCards::Uwp::IAdaptiveActionElement,
            Microsoft::WRL::CloakedIid<ITypePeek>>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveShowCardAction, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::ShowCardAction>& sharedShowCardAction);

        // IAdaptiveShowCardAction
        IFACEMETHODIMP get_Card(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveCard** card);
        IFACEMETHODIMP put_Card(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveCard* card);

        // IAdaptiveActionElement
        IFACEMETHODIMP get_ActionType(_Out_ ABI::AdaptiveCards::Uwp::ActionType* actionType);
        IFACEMETHODIMP get_ActionTypeString(_Out_ HSTRING* value);

        IFACEMETHODIMP get_Title(_Out_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);

        IFACEMETHODIMP get_Id(_Out_ HSTRING* id);
        IFACEMETHODIMP put_Id(_In_ HSTRING id);

        IFACEMETHODIMP get_AdditionalProperties(_Out_ ABI::Windows::Data::Json::IJsonObject** result);
        IFACEMETHODIMP put_AdditionalProperties(_In_ ABI::Windows::Data::Json::IJsonObject* value);

        IFACEMETHODIMP ToJson(_Out_ ABI::Windows::Data::Json::IJsonObject** result);

        HRESULT GetSharedModel(_In_ std::shared_ptr<AdaptiveCards::ShowCardAction>& sharedModel);

        // ITypePeek method
        void *PeekAt(REFIID riid) override
        {
            return PeekHelper(riid, this);
        }

    private:
        
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCard> m_card;

        Microsoft::WRL::Wrappers::HString m_id;
        Microsoft::WRL::Wrappers::HString m_title;
        Microsoft::WRL::ComPtr<ABI::Windows::Data::Json::IJsonObject> m_additionalProperties;

    };

    ActivatableClass(AdaptiveShowCardAction);
}}