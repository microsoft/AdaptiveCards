// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveNamespace
{
    class AdaptiveError
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveNamespace::IAdaptiveError>,
                                              Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveError);

    public:
        HRESULT RuntimeClassInitialize();

        HRESULT RuntimeClassInitialize(ABI::AdaptiveNamespace::ErrorStatusCode statusCode, _In_ HSTRING message);

        // IAdaptiveError
        HRESULT put_StatusCode(ABI::AdaptiveNamespace::ErrorStatusCode value);
        IFACEMETHODIMP get_StatusCode(_Out_ ABI::AdaptiveNamespace::ErrorStatusCode* value);

        HRESULT put_Message(_In_ HSTRING value);
        IFACEMETHODIMP get_Message(_Outptr_ HSTRING* value);

    private:
        Microsoft::WRL::Wrappers::HString m_message;
        ABI::AdaptiveNamespace::ErrorStatusCode m_statusCode;
    };

    ActivatableClass(AdaptiveError);
}
