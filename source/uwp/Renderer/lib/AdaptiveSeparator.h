#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Separator.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{

    class AdaptiveSeparator :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveSeparator>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveSeparator, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::Separator>& sharedSeparator);

        // IAdaptiveSeparator
        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor* color);
        IFACEMETHODIMP put_Color(_In_ ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor color);

        IFACEMETHODIMP get_Thickness(_Out_ ABI::AdaptiveCards::Rendering::Uwp::SeparatorThickness* thickness);
        IFACEMETHODIMP put_Thickness(_In_ ABI::AdaptiveCards::Rendering::Uwp::SeparatorThickness thickness);

    private:
        std::shared_ptr<AdaptiveCards::Separator> m_sharedSeparator;
    };

    ActivatableClass(AdaptiveSeparator);
}}}