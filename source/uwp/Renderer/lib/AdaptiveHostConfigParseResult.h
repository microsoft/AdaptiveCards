#pragma once

#include "util.h"

AdaptiveNamespaceStart
    class AdaptiveHostConfigParseResult :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::Implements<ABI::AdaptiveNamespaceRef::IAdaptiveHostConfigParseResult>>
    {
        AdaptiveRuntime(AdaptiveHostConfigParseResult)

    public:
        AdaptiveHostConfigParseResult();

        HRESULT RuntimeClassInitialize(); 
        HRESULT RuntimeClassInitialize(ABI::AdaptiveNamespaceRef::IAdaptiveHostConfig* hostConfig);

        // IAdaptiveHostConfigParseResult
        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveHostConfig** value);

        IFACEMETHODIMP get_Errors(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveError*>** value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveError*>> m_errors;
    };

    ActivatableClass(AdaptiveHostConfigParseResult);
AdaptiveNamespaceEnd