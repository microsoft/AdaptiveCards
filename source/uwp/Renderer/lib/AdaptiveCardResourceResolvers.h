// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveNamespace
{
    class AdaptiveCardResourceResolvers
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers>
    {
        AdaptiveRuntime(AdaptiveCardResourceResolvers);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING scheme, _In_ ABI::AdaptiveNamespace::IAdaptiveCardResourceResolver* resolver);
        IFACEMETHODIMP Get(_In_ HSTRING scheme, _COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardResourceResolver** resolver);

    private:
        std::map<std::string, Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardResourceResolver>> m_resourceResolvers;
    };

    ActivatableClass(AdaptiveCardResourceResolvers);
}
