#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class AdaptiveColorConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveColorConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ColorConfig colorConfig) noexcept;

        IFACEMETHODIMP get_Default(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_Default(_In_ ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_Subtle(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_Subtle(_In_ ABI::Windows::UI::Color value);

    private:
        ABI::Windows::UI::Color m_defaultColor;
        ABI::Windows::UI::Color m_subtleColor;
    };

    ActivatableClass(AdaptiveColorConfig);
}}}
