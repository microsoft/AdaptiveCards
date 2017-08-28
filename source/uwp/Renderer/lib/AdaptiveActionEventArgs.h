#pragma once
#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveActionEventArgs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionEventArgs>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveActionEventArgs, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement* action, _In_ HSTRING inputs);

        // IAdaptiveActionEventArgs
        IFACEMETHODIMP get_Action(_Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement** action);
        IFACEMETHODIMP get_Inputs(_Out_ HSTRING* inputs);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement> m_action;
        Microsoft::WRL::Wrappers::HString m_inputs;
    };
}}