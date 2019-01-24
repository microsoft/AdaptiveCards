#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveNamespace
{
    class AdaptiveFontStylesDefinition
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveFontStylesDefinition>
    {
        AdaptiveRuntime(AdaptiveFontStylesDefinition);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(FontStylesDefinition stylesDefinition) noexcept;

        IFACEMETHODIMP get_Default(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition** value);
        IFACEMETHODIMP put_Default(_In_ ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition* value);

        IFACEMETHODIMP get_Display(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition** value);
        IFACEMETHODIMP put_Display(_In_ ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition* value);

        IFACEMETHODIMP get_Monospace(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition** value);
        IFACEMETHODIMP put_Monospace(_In_ ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition* value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition> m_default;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition> m_display;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveFontStyleDefinition> m_monospace;
    };

    ActivatableClass(AdaptiveFontStylesDefinition);
}
