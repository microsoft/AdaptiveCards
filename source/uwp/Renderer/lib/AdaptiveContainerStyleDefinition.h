#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveContainerStyleDefinition :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveContainerStyleDefinition, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ContainerStyleDefinition styleDefinition) noexcept;

        IFACEMETHODIMP get_BackgroundColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_BackgroundColor(_In_ ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_ForegroundColors(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorsConfig** colorsConfig);
        IFACEMETHODIMP put_ForegroundColors(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorsConfig* colorsConfig);

    private:
        ContainerStyleDefinition m_sharedContainerStyleDefinition;
    };

    ActivatableClass(AdaptiveContainerStyleDefinition);
}}