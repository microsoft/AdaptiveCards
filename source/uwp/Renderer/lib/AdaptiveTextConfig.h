#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveTextConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveTextConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(TextConfig textConfig) noexcept;

        IFACEMETHODIMP get_Weight(_Out_ ABI::AdaptiveCards::XamlCardRenderer::TextWeight* textWeight);
        IFACEMETHODIMP put_Weight(_In_ ABI::AdaptiveCards::XamlCardRenderer::TextWeight textWeight);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveCards::XamlCardRenderer::TextSize* textSize);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveCards::XamlCardRenderer::TextSize textSize);

        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor* textColor);
        IFACEMETHODIMP put_Color(_In_ ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor textColor);

        IFACEMETHODIMP get_IsSubtle(_Out_ boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(_In_ boolean isSubtle);

    private:
        TextConfig m_sharedTextConfig;
    };

    ActivatableClass(AdaptiveTextConfig);
}
}