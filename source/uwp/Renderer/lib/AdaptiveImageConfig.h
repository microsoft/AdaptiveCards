#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveImageConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespaceRef::IAdaptiveImageConfig>
    {
        AdaptiveRuntime(AdaptiveImageConfig)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ImageConfig ImageConfig) noexcept;

        IFACEMETHODIMP get_ImageSize(_Out_ ABI::AdaptiveNamespaceRef::ImageSize* imageSize);
        IFACEMETHODIMP put_ImageSize(_In_ ABI::AdaptiveNamespaceRef::ImageSize imageSize);

    private:
        ABI::AdaptiveNamespaceRef::ImageSize m_imageSize;
    };

    ActivatableClass(AdaptiveImageConfig);
AdaptiveNamespaceEnd