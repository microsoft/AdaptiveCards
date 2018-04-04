#pragma once
#include "AdaptiveCards.Rendering.Uwp.h"

AdaptiveNamespaceStart
    class AdaptiveCardResourceResolvers :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveCardResourceResolvers>
    {
        AdaptiveRuntime(AdaptiveCardResourceResolvers)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING scheme, _In_ ABI::AdaptiveNamespace::IAdaptiveCardResourceResolver* resolver);
        IFACEMETHODIMP Get(_In_ HSTRING scheme, _Outptr_ ABI::AdaptiveNamespace::IAdaptiveCardResourceResolver** resolver);

    private:
        std::map<std::string, Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCardResourceResolver>> m_resourceResolvers;
    };

    ActivatableClass(AdaptiveCardResourceResolvers);
AdaptiveNamespaceEnd