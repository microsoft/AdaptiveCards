#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class AdaptiveImageSetConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImageSetConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveImageSetConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ImageSetConfig ImageSetConfig) noexcept;

        IFACEMETHODIMP get_ImageSize(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ImageSize* imageSize);
        IFACEMETHODIMP put_ImageSize(_In_ ABI::AdaptiveCards::Rendering::Uwp::ImageSize imageSize);

        IFACEMETHODIMP get_MaxImageHeight(_Out_ UINT32* maxImageHeight);
        IFACEMETHODIMP put_MaxImageHeight(_In_ UINT32 maxImageHeight);

    private:
        ABI::AdaptiveCards::Rendering::Uwp::ImageSize m_imageSize;
        UINT32 m_maxImageHeight;
    };

    ActivatableClass(AdaptiveImageSetConfig);
}}}