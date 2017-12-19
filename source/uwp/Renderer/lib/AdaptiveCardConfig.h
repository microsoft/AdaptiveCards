#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class AdaptiveCardConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveCardConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::AdaptiveCardConfig adaptiveCardConfig) noexcept;

        IFACEMETHODIMP get_AllowCustomStyle(_Out_ boolean* allowCustomStyle);
        IFACEMETHODIMP put_AllowCustomStyle(_In_ boolean allowCustomStyle);

    private:
        boolean m_allowCustomStyle;
    };

    ActivatableClass(AdaptiveCardConfig);
}}}