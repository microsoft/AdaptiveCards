#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

AdaptiveNamespaceStart
    class AdaptiveError:
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        Microsoft::WRL::Implements<ABI::AdaptiveNamespaceRef::IAdaptiveError>,
        Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveError)

    public:
        HRESULT RuntimeClassInitialize();

        HRESULT RuntimeClassInitialize(
            ABI::AdaptiveNamespaceRef::ErrorStatusCode statusCode,
            HSTRING message);

        // IAdaptiveError
        HRESULT put_StatusCode(_In_ ABI::AdaptiveNamespaceRef::ErrorStatusCode value);
        IFACEMETHODIMP get_StatusCode(_Out_ ABI::AdaptiveNamespaceRef::ErrorStatusCode* value);

        HRESULT put_Message(_In_ HSTRING value);
        IFACEMETHODIMP get_Message(_Out_ HSTRING* value);

    private:
        Microsoft::WRL::Wrappers::HString m_message;
        ABI::AdaptiveNamespaceRef::ErrorStatusCode m_statusCode;
    };

    ActivatableClass(AdaptiveError);
AdaptiveNamespaceEnd
