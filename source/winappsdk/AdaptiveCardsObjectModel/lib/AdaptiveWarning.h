// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.ObjectModel.WinAppSDK.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class AdaptiveWarning
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveWarning>,
                                              Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveWarning);

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(ABI::AdaptiveCards::ObjectModel::WinAppSDK::WarningStatusCode statusCode, _In_ HSTRING message);

        // IAdaptiveWarning
        IFACEMETHODIMP put_StatusCode(ABI::AdaptiveCards::ObjectModel::WinAppSDK::WarningStatusCode value);
        IFACEMETHODIMP get_StatusCode(_Out_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::WarningStatusCode* value);

        IFACEMETHODIMP put_Message(_In_ HSTRING value);
        IFACEMETHODIMP get_Message(_Outptr_ HSTRING* value);

    private:
        Microsoft::WRL::Wrappers::HString m_message;
        ABI::AdaptiveCards::ObjectModel::WinAppSDK::WarningStatusCode m_statusCode;
    };

    class AdaptiveWarningFactory
        : public Microsoft::WRL::AgileActivationFactory<ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveWarningFactory>
    {
        IFACEMETHODIMP CreateInstance(ABI::AdaptiveCards::ObjectModel::WinAppSDK::WarningStatusCode statusCode,
                                      _In_ HSTRING message,
                                      _COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveWarning** result) override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveWarning>(result, statusCode, message);
        }
    };

    ActivatableClassWithFactory(AdaptiveWarning, AdaptiveWarningFactory);
}
