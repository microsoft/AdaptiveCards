#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Height.h"

AdaptiveNamespaceStart
    class AdaptiveHeight :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveHeight>
    {
        AdaptiveRuntime(AdaptiveHeight);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(Height height) noexcept;

        IFACEMETHODIMP get_HeightType(_Out_ ABI::AdaptiveNamespace::HeightType* heightType);
        IFACEMETHODIMP put_HeightType(_In_ ABI::AdaptiveNamespace::HeightType heightType);

    private:
        Height m_sharedHeight;
    };

    ActivatableClass(AdaptiveHeight);
AdaptiveNamespaceEnd