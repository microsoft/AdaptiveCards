#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "ShowCardAction.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveShowCardAction :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveShowCardAction,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveShowCardAction, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::ShowCardAction>& sharedShowCardAction);

        // IAdaptiveShowCardAction
        IFACEMETHODIMP get_Card(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard** card);
        IFACEMETHODIMP put_Card(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* card);

        // IAdaptiveActionElement
        IFACEMETHODIMP get_ActionType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ActionType* actionType);

        IFACEMETHODIMP get_Speak(_Out_ HSTRING* speak);
        IFACEMETHODIMP put_Speak(_In_ HSTRING speak);

        IFACEMETHODIMP get_Title(_Out_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);
    private:
        std::shared_ptr<AdaptiveCards::ShowCardAction> m_sharedShowCardAction;
    };

    ActivatableClass(AdaptiveShowCardAction);
}}