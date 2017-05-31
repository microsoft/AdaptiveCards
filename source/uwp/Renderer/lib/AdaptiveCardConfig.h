#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveCardConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveCardConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::AdaptiveCardConfig adaptiveCardConfig) noexcept;

        IFACEMETHODIMP get_Padding(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingDefinition** value);
        IFACEMETHODIMP put_Padding(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingDefinition* value);

        IFACEMETHODIMP get_BackgroundColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_BackgroundColor(_In_ ABI::Windows::UI::Color value);

    private:
        AdaptiveCards::AdaptiveCardConfig m_sharedAdaptiveCardConfig;
    };

    ActivatableClass(AdaptiveCardConfig);
}
}