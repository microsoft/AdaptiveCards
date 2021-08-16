// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "ObjectModelUtil.h"

namespace AdaptiveCards::ObjectModel::WinUI3
{
    class AdaptiveCardParseResult
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardParseResult>>
    {
        AdaptiveRuntime(AdaptiveCardParseResult);

    public:
        AdaptiveCardParseResult();

        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* adaptiveCard);

        // IAdaptiveCardParseResult
        IFACEMETHODIMP get_AdaptiveCard(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard** value);
        HRESULT put_AdaptiveCard(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* value);

        IFACEMETHODIMP get_Errors(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveError*>** value);
        IFACEMETHODIMP get_Warnings(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning*>** value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard> m_adaptiveCard;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveError*>> m_errors;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning*>> m_warnings;
    };

    ActivatableClass(AdaptiveCardParseResult);
}
