#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveImageSetConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespaceRef::IAdaptiveImageSetConfig>
    {
        AdaptiveRuntime(AdaptiveImageSetConfig)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ImageSetConfig ImageSetConfig) noexcept;

        IFACEMETHODIMP get_ImageSize(_Out_ ABI::AdaptiveNamespaceRef::ImageSize* imageSize);
        IFACEMETHODIMP put_ImageSize(_In_ ABI::AdaptiveNamespaceRef::ImageSize imageSize);

        IFACEMETHODIMP get_MaxImageHeight(_Out_ UINT32* maxImageHeight);
        IFACEMETHODIMP put_MaxImageHeight(_In_ UINT32 maxImageHeight);

    private:
        ABI::AdaptiveNamespaceRef::ImageSize m_imageSize;
        UINT32 m_maxImageHeight;
    };

    ActivatableClass(AdaptiveImageSetConfig);
AdaptiveNamespaceEnd