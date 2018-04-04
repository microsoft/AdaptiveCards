#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveContainerStyleDefinition :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition>
    {
        AdaptiveRuntime(AdaptiveContainerStyleDefinition)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ContainerStyleDefinition styleDefinition) noexcept;

        IFACEMETHODIMP get_BackgroundColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_BackgroundColor(_In_ ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_ForegroundColors(_Out_ ABI::AdaptiveNamespace::IAdaptiveColorsConfig** colorsConfig);
        IFACEMETHODIMP put_ForegroundColors(_In_ ABI::AdaptiveNamespace::IAdaptiveColorsConfig* colorsConfig);

    private:
        ABI::Windows::UI::Color m_backgroundColor;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveColorsConfig> m_foregroundColors;
    };

    ActivatableClass(AdaptiveContainerStyleDefinition);
AdaptiveNamespaceEnd