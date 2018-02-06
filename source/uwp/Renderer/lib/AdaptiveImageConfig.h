#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class AdaptiveImageConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImageConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveImageConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ImageConfig ImageConfig) noexcept;

        IFACEMETHODIMP get_ImageSize(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ImageSize* imageSize);
        IFACEMETHODIMP put_ImageSize(_In_ ABI::AdaptiveCards::Rendering::Uwp::ImageSize imageSize);

    private:
        ABI::AdaptiveCards::Rendering::Uwp::ImageSize m_imageSize;
    };

    ActivatableClass(AdaptiveImageConfig);
}}}