// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveNamespace
{
    class AdaptiveRequirement
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveNamespace::IAdaptiveRequirement>,
                                              Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveRequirement);

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ HSTRING name, _In_ HSTRING version);
        HRESULT RuntimeClassInitialize(const std::pair<const std::string, AdaptiveCards::SemanticVersion>& sharedRequirement) noexcept;

        // IAdaptiveRequirement
        IFACEMETHODIMP put_Name(_In_ HSTRING value);
        IFACEMETHODIMP get_Name(_Outptr_ HSTRING* value);

        IFACEMETHODIMP put_Version(_In_ HSTRING value);
        IFACEMETHODIMP get_Version(_Outptr_ HSTRING* value);

    private:
        Microsoft::WRL::Wrappers::HString m_name;
        Microsoft::WRL::Wrappers::HString m_version;
    };

    class AdaptiveRequirementFactory : public Microsoft::WRL::AgileActivationFactory<ABI::AdaptiveNamespace::IAdaptiveRequirementFactory>
    {
        IFACEMETHODIMP CreateInstance(_In_ HSTRING name,
                                      _In_ HSTRING version,
                                      _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRequirement** result) override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveRequirement>(result, name, version);
        }
    };

    ActivatableClassWithFactory(AdaptiveRequirement, AdaptiveRequirementFactory);
}
