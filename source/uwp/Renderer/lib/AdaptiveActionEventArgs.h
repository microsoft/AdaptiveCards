#pragma once
#include "AdaptiveCards.Uwp.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveActionEventArgs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
        ABI::AdaptiveCards::Uwp::IAdaptiveActionEventArgs>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveActionEventArgs, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveActionElement* action, _In_ ABI::AdaptiveCards::Uwp::IAdaptiveInputs* inputs);

        // IAdaptiveActionEventArgs
        IFACEMETHODIMP get_Action(_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveActionElement** action);
        IFACEMETHODIMP get_Inputs(_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveInputs** inputs);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveActionElement> m_action;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveInputs> m_inputs;
    };
}}