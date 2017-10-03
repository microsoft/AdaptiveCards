#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveTextConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Uwp::IAdaptiveTextConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveTextConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(TextConfig textConfig) noexcept;

        IFACEMETHODIMP get_Weight(_Out_ ABI::AdaptiveCards::Uwp::TextWeight* textWeight);
        IFACEMETHODIMP put_Weight(_In_ ABI::AdaptiveCards::Uwp::TextWeight textWeight);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveCards::Uwp::TextSize* textSize);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveCards::Uwp::TextSize textSize);

        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveCards::Uwp::ForegroundColor* textColor);
        IFACEMETHODIMP put_Color(_In_ ABI::AdaptiveCards::Uwp::ForegroundColor textColor);

        IFACEMETHODIMP get_IsSubtle(_Out_ boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(_In_ boolean isSubtle);

        IFACEMETHODIMP get_Wrap(_Out_ boolean* wrap);
        IFACEMETHODIMP put_Wrap(_In_ boolean wrap);

        IFACEMETHODIMP get_MaxWidth(_Out_ UINT32* maxWidth);
        IFACEMETHODIMP put_MaxWidth(_In_ UINT32 maxWidth);

    private:
        TextConfig m_sharedTextConfig;
    };

    ActivatableClass(AdaptiveTextConfig);
}
}