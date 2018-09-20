#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveContainerStylesDefinition :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveContainerStylesDefinition>
    {
        AdaptiveRuntime(AdaptiveContainerStylesDefinition)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ContainerStylesDefinition stylesDefinition) noexcept;

        IFACEMETHODIMP get_Default(_Out_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Default(_In_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Emphasis(_Out_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Emphasis(_In_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition> m_default;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition> m_emphasis;
    };

    ActivatableClass(AdaptiveContainerStylesDefinition);
AdaptiveNamespaceEnd