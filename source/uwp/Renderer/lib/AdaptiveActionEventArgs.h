#pragma once
#include "AdaptiveCards.Rendering.Uwp.h"

AdaptiveNamespaceStart
    class AdaptiveActionEventArgs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
        ABI::AdaptiveNamespaceRef::IAdaptiveActionEventArgs>
    {
        AdaptiveRuntime(AdaptiveActionEventArgs)

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveActionElement* action, _In_ ABI::AdaptiveNamespaceRef::IAdaptiveInputs* inputs);

        // IAdaptiveActionEventArgs
        IFACEMETHODIMP get_Action(_Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveActionElement** action);
        IFACEMETHODIMP get_Inputs(_Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveInputs** inputs);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveActionElement> m_action;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveInputs> m_inputs;
    };
AdaptiveNamespaceEnd