#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HttpAction.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveHttpAction :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveHttpAction,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveHttpAction, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::HttpAction>& sharedHttpAction);

        // IAdaptiveHttpAction
        IFACEMETHODIMP get_Url(_Out_ ABI::Windows::Foundation::IUriRuntimeClass** url);
        IFACEMETHODIMP put_Url(_In_ ABI::Windows::Foundation::IUriRuntimeClass* url);

        IFACEMETHODIMP get_Method(_Out_ HSTRING* method);
        IFACEMETHODIMP put_Method(_In_ HSTRING method);

        IFACEMETHODIMP get_Body(_Out_ HSTRING* body);
        IFACEMETHODIMP put_Body(_In_ HSTRING body);

        // IAdaptiveActionElement
        IFACEMETHODIMP get_ActionType(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ActionType* actionType);

        IFACEMETHODIMP get_Title(_Out_ HSTRING* title);
        IFACEMETHODIMP put_Title(_In_ HSTRING title);

        IFACEMETHODIMP get_Speak(_Out_ HSTRING* speak);
        IFACEMETHODIMP put_Speak(_In_ HSTRING speak);

    private:
        std::shared_ptr<AdaptiveCards::HttpAction> m_sharedHttpAction;
    };

    ActivatableClass(AdaptiveHttpAction);
}}