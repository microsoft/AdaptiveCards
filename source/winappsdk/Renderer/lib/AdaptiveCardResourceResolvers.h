// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveCards.Rendering.WinUI3.h"

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveCardResourceResolvers
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveCardResourceResolvers>
    {
        AdaptiveRuntime(AdaptiveCardResourceResolvers);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING scheme, _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveCardResourceResolver* resolver);
        IFACEMETHODIMP Get(_In_ HSTRING scheme,
                           _COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveCardResourceResolver** resolver);

    private:
        std::map<std::string, Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveCardResourceResolver>> m_resourceResolvers;
    };

    ActivatableClass(AdaptiveCardResourceResolvers);
}
