// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.ObjectModel.WinUI3.h"

namespace AdaptiveCards::ObjectModel::WinUI3
{
    class AdaptiveError
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveError>,
                                              Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveError);

    public:
        HRESULT RuntimeClassInitialize();

        HRESULT RuntimeClassInitialize(ABI::AdaptiveCards::ObjectModel::WinUI3::ErrorStatusCode statusCode, _In_ HSTRING message);

        // IAdaptiveError
        IFACEMETHODIMP put_StatusCode(ABI::AdaptiveCards::ObjectModel::WinUI3::ErrorStatusCode value);
        IFACEMETHODIMP get_StatusCode(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::ErrorStatusCode* value);

        IFACEMETHODIMP put_Message(_In_ HSTRING value);
        IFACEMETHODIMP get_Message(_Outptr_ HSTRING* value);

    private:
        Microsoft::WRL::Wrappers::HString m_message;
        ABI::AdaptiveCards::ObjectModel::WinUI3::ErrorStatusCode m_statusCode;
    };

    class AdaptiveErrorFactory : public Microsoft::WRL::AgileActivationFactory<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveErrorFactory>
    {
        IFACEMETHODIMP CreateInstance(ABI::AdaptiveCards::ObjectModel::WinUI3::ErrorStatusCode statusCode,
                                      _In_ HSTRING message,
                                      _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveError** result) override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveError>(result, statusCode, message);
        }
    };

    ActivatableClassWithFactory(AdaptiveError, AdaptiveErrorFactory);
}
