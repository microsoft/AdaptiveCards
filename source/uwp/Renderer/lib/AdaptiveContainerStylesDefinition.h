#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveContainerStylesDefinition :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespaceRef::IAdaptiveContainerStylesDefinition>
    {
        AdaptiveRuntime(AdaptiveContainerStylesDefinition)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ContainerStylesDefinition stylesDefinition) noexcept;

        IFACEMETHODIMP get_Default(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Default(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Emphasis(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Emphasis(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveContainerStyleDefinition* value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveContainerStyleDefinition> m_default;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveContainerStyleDefinition> m_emphasis;
    };

    ActivatableClass(AdaptiveContainerStylesDefinition);
AdaptiveNamespaceEnd