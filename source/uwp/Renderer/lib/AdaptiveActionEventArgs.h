#pragma once
#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{

    class AdaptiveActionEventArgs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionEventArgs>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveActionEventArgs, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement* action, _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputs* inputs);

        // IAdaptiveActionEventArgs
        IFACEMETHODIMP get_Action(_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement** action);
        IFACEMETHODIMP get_Inputs(_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputs** inputs);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement> m_action;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputs> m_inputs;
    };
}}}