#pragma once

#include "AdaptiveCards.Uwp.h"

namespace AdaptiveCards { namespace Uwp {
    class AdaptiveFailure:
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::Implements<ABI::AdaptiveCards::Uwp::IAdaptiveFailure>,
        Microsoft::WRL::FtmBase>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveFailure, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize();

        HRESULT RuntimeClassInitialize(
            ABI::AdaptiveCards::Uwp::FailureStatusCode FailureStatusCode,
            HSTRING message);

        // IAdaptiveFailure
        IFACEMETHODIMP put_FailureStatusCode(_In_ ABI::AdaptiveCards::Uwp::FailureStatusCode value);
        IFACEMETHODIMP get_FailureStatusCode(_Out_ ABI::AdaptiveCards::Uwp::FailureStatusCode* value);

        IFACEMETHODIMP put_Message(_In_ HSTRING value);
        IFACEMETHODIMP get_Message(_Out_ HSTRING* value);

    private:
        Microsoft::WRL::Wrappers::HString m_message;
        ABI::AdaptiveCards::Uwp::FailureStatusCode m_FailureStatusCode;

    };

    ActivatableClass(AdaptiveFailure);
}}
