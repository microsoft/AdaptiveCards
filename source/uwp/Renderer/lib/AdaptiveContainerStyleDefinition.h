// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    class AdaptiveContainerStyleDefinition
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition>
    {
        AdaptiveRuntime(AdaptiveContainerStyleDefinition);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ContainerStyleDefinition styleDefinition) noexcept;

        IFACEMETHODIMP get_BackgroundColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_BackgroundColor(ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_ForegroundColors(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveColorsConfig** colorsConfig);
        IFACEMETHODIMP put_ForegroundColors(_In_ ABI::AdaptiveNamespace::IAdaptiveColorsConfig* colorsConfig);

        IFACEMETHODIMP get_HighlightColors(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveColorsConfig** colorsConfig);
        IFACEMETHODIMP put_HighlightColors(_In_ ABI::AdaptiveNamespace::IAdaptiveColorsConfig* colorsConfig);

    private:
        ABI::Windows::UI::Color m_backgroundColor;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveColorsConfig> m_foregroundColors;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveColorsConfig> m_highlightColors;
    };

    ActivatableClass(AdaptiveContainerStyleDefinition);
}
