#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

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

        IFACEMETHODIMP get_HighlightColors(ABI::AdaptiveNamespace::IAdaptiveHighlightColorConfig** highlightColors);
        IFACEMETHODIMP put_HighlightColors(ABI::AdaptiveNamespace::IAdaptiveHighlightColorConfig* highlightColors);

    private:
        ABI::Windows::UI::Color m_defaultColor;
        ABI::Windows::UI::Color m_subtleColor;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveHighlightColorConfig> m_highlightColors;
    };

    ActivatableClass(AdaptiveColorConfig);
}
