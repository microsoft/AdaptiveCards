#pragma once

#include "util.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveHostConfigParseResult :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::Implements<ABI::AdaptiveCards::Uwp::IAdaptiveHostConfigParseResult>>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveHostConfigParseResult, BaseTrust)

    public:
        AdaptiveHostConfigParseResult();

        HRESULT RuntimeClassInitialize(); 
        HRESULT RuntimeClassInitialize(ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig* hostConfig);

        // IAdaptiveHostConfigParseResult
        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig** value);

        IFACEMETHODIMP get_Errors(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveError*>** value);
        IFACEMETHODIMP get_Warnings(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveWarning*>** value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveError*>> m_errors;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Uwp::IAdaptiveWarning*>> m_warnings;
    };

    ActivatableClass(AdaptiveHostConfigParseResult);
}}