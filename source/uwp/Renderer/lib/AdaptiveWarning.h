#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp {
    class AdaptiveWarning:
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::Implements<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveWarning>,
        Microsoft::WRL::FtmBase>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveWarning, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize();

        HRESULT RuntimeClassInitialize(
            ABI::AdaptiveCards::Rendering::Uwp::WarningStatusCode statusCode,
            HSTRING message);

        // IAdaptiveWarning
        HRESULT put_StatusCode(_In_ ABI::AdaptiveCards::Rendering::Uwp::WarningStatusCode value);
        IFACEMETHODIMP get_StatusCode(_Out_ ABI::AdaptiveCards::Rendering::Uwp::WarningStatusCode* value);

        HRESULT put_Message(_In_ HSTRING value);
        IFACEMETHODIMP get_Message(_Out_ HSTRING* value);

    private:
        Microsoft::WRL::Wrappers::HString m_message;
        ABI::AdaptiveCards::Rendering::Uwp::WarningStatusCode m_statusCode;
    };

    ActivatableClass(AdaptiveWarning);
}}}
