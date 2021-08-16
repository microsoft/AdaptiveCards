// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "util.h"

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveHostConfigParseResult
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfigParseResult>>
    {
        AdaptiveRuntime(AdaptiveHostConfigParseResult);

    public:
        AdaptiveHostConfigParseResult();

        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* hostConfig);

        // IAdaptiveHostConfigParseResult
        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig** value);

        IFACEMETHODIMP get_Errors(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveError*>** value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveError*>> m_errors;
    };

    ActivatableClass(AdaptiveHostConfigParseResult);
}
