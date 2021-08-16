// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.WinUI3.h"
#include "Util.h"

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveActionRendererRegistration
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveActionRendererRegistration>,
                                              Microsoft::WRL::FtmBase>
    {
        AdaptiveRuntime(AdaptiveActionRendererRegistration);

        typedef std::unordered_map<std::string, Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveActionRenderer>, CaseInsensitiveHash, CaseInsensitiveEqualTo> RegistrationMap;

    public:
        AdaptiveActionRendererRegistration();
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING type, _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveActionRenderer* renderer);
        IFACEMETHODIMP Get(_In_ HSTRING type, _COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveActionRenderer** result);
        IFACEMETHODIMP Remove(_In_ HSTRING type);

    private:
        std::shared_ptr<RegistrationMap> m_registration;
    };
}
