#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveImageConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveImageConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveImageConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ImageConfig ImageConfig) noexcept;

        IFACEMETHODIMP get_ImageSize(_Out_ ABI::AdaptiveCards::Uwp::ImageSize* imageSize);
        IFACEMETHODIMP put_ImageSize(_In_ ABI::AdaptiveCards::Uwp::ImageSize imageSize);

    private:
        ImageConfig m_sharedImageConfig;
    };

    ActivatableClass(AdaptiveImageConfig);
}}