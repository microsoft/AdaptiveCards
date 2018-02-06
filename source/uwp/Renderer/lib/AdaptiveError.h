#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp {
    class AdaptiveError:
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::Implements<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveError>,
        Microsoft::WRL::FtmBase>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveError, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize();

        HRESULT RuntimeClassInitialize(
            ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode statusCode,
            HSTRING message);

        // IAdaptiveError
        HRESULT put_StatusCode(_In_ ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode value);
        IFACEMETHODIMP get_StatusCode(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode* value);

        HRESULT put_Message(_In_ HSTRING value);
        IFACEMETHODIMP get_Message(_Out_ HSTRING* value);

    private:
        Microsoft::WRL::Wrappers::HString m_message;
        ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode m_statusCode;
    };

    ActivatableClass(AdaptiveError);
}}}
