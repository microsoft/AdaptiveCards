// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    class AdaptiveColorConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveColorConfig>
    {
        AdaptiveRuntime(AdaptiveColorConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ColorConfig colorConfig) noexcept;

        IFACEMETHODIMP get_Default(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_Default(ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_Subtle(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_Subtle(ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_HighlightColors(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveHighlightColorConfig** highlightColors);
        IFACEMETHODIMP put_HighlightColors(_In_ ABI::AdaptiveNamespace::IAdaptiveHighlightColorConfig* highlightColors);

    private:
        ABI::Windows::UI::Color m_defaultColor;
        ABI::Windows::UI::Color m_subtleColor;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveHighlightColorConfig> m_highlightColors;
    };

    ActivatableClass(AdaptiveColorConfig);
}
