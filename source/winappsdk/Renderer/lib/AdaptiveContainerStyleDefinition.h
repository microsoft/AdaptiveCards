// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveContainerStyleDefinition
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveContainerStyleDefinition>
    {
        AdaptiveRuntime(AdaptiveContainerStyleDefinition);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ContainerStyleDefinition styleDefinition) noexcept;

        IFACEMETHODIMP get_BackgroundColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_BackgroundColor(ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_BorderColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_BorderColor(ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_ForegroundColors(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveColorsConfig** colorsConfig);
        IFACEMETHODIMP put_ForegroundColors(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveColorsConfig* colorsConfig);

        IFACEMETHODIMP get_HighlightColors(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveColorsConfig** colorsConfig);
        IFACEMETHODIMP put_HighlightColors(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveColorsConfig* colorsConfig);

    private:
        ABI::Windows::UI::Color m_backgroundColor;
        ABI::Windows::UI::Color m_borderColor;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveColorsConfig> m_foregroundColors;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveColorsConfig> m_highlightColors;
    };

    ActivatableClass(AdaptiveContainerStyleDefinition);
}
