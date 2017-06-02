#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveContainerStyleConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveContainerStyleConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::ContainerStyleConfig containerStyleConfig) noexcept;

        IFACEMETHODIMP get_BorderThickness(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingDefinition** value);
        IFACEMETHODIMP put_BorderThickness(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingDefinition* value);

        IFACEMETHODIMP get_Padding(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingDefinition** value);
        IFACEMETHODIMP put_Padding(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingDefinition* value);

        IFACEMETHODIMP get_BackgroundColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_BackgroundColor(_In_ ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_BorderColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_BorderColor(_In_ ABI::Windows::UI::Color value);

    private:
        AdaptiveCards::ContainerStyleConfig m_sharedContainerStyleConfig;
    };

    ActivatableClass(AdaptiveContainerStyleConfig);
}
}