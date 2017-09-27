#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveContainerStylesDefinition :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStylesDefinition>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveContainerStylesDefinition, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ContainerStylesDefinition stylesDefinition) noexcept;

        IFACEMETHODIMP get_Default(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Default(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Emphasis(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Emphasis(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleDefinition* value);

    private:
        ContainerStylesDefinition m_sharedContainerStylesDefinition;
    };

    ActivatableClass(AdaptiveContainerStylesDefinition);
}}