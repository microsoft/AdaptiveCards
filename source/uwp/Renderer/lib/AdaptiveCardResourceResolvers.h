#pragma once
#include "AdaptiveCards.Rendering.Uwp.h"

AdaptiveNamespaceStart
    class AdaptiveCardResourceResolvers :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespaceRef::IAdaptiveCardResourceResolvers>
    {
        AdaptiveRuntime(AdaptiveCardResourceResolvers)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING scheme, _In_ ABI::AdaptiveNamespaceRef::IAdaptiveCardResourceResolver* resolver);
        IFACEMETHODIMP Get(_In_ HSTRING scheme, _Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveCardResourceResolver** resolver);

    private:
        std::map<std::string, Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveCardResourceResolver>> m_resourceResolvers;
    };

    ActivatableClass(AdaptiveCardResourceResolvers);
AdaptiveNamespaceEnd