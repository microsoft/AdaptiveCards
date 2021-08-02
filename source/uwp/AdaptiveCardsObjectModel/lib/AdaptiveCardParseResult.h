// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ObjectModelUtil.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    class AdaptiveCardParseResult
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardParseResult>>
    {
        AdaptiveRuntime(AdaptiveCardParseResult);

    public:
        AdaptiveCardParseResult();

        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard* adaptiveCard);

        // IAdaptiveCardParseResult
        IFACEMETHODIMP get_AdaptiveCard(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard** value);
        HRESULT put_AdaptiveCard(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard* value);

        IFACEMETHODIMP get_Errors(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveError*>** value);
        IFACEMETHODIMP get_Warnings(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning*>** value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCard> m_adaptiveCard;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveError*>> m_errors;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning*>> m_warnings;
    };

    ActivatableClass(AdaptiveCardParseResult);
}
