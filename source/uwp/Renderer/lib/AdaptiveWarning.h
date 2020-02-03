// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveNamespace
{
    class AdaptiveWarning
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveNamespace::IAdaptiveWarning>,
                                              Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveWarning);

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(ABI::AdaptiveNamespace::WarningStatusCode statusCode, _In_ HSTRING message);

        // IAdaptiveWarning
        IFACEMETHODIMP put_StatusCode(ABI::AdaptiveNamespace::WarningStatusCode value);
        IFACEMETHODIMP get_StatusCode(_Out_ ABI::AdaptiveNamespace::WarningStatusCode* value);

        IFACEMETHODIMP put_Message(_In_ HSTRING value);
        IFACEMETHODIMP get_Message(_Outptr_ HSTRING* value);

    private:
        Microsoft::WRL::Wrappers::HString m_message;
        ABI::AdaptiveNamespace::WarningStatusCode m_statusCode;
    };

    class AdaptiveWarningFactory : public Microsoft::WRL::AgileActivationFactory<ABI::AdaptiveNamespace::IAdaptiveWarningFactory>
    {
        IFACEMETHODIMP CreateInstance(ABI::AdaptiveCards::Rendering::Uwp::WarningStatusCode statusCode,
                                      _In_ HSTRING message,
                                      _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveWarning** result) override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveWarning>(result, statusCode, message);
        }
    };

    ActivatableClassWithFactory(AdaptiveWarning, AdaptiveWarningFactory);
}
