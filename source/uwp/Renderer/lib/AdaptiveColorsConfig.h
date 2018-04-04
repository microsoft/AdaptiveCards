#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveColorsConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespace::IAdaptiveColorsConfig>
    {
        AdaptiveRuntime(AdaptiveColorsConfig)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ColorsConfig colorsConfig) noexcept;

        IFACEMETHODIMP get_Default(_Out_ ABI::AdaptiveNamespace::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Default(_In_ ABI::AdaptiveNamespace::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Accent(_Out_ ABI::AdaptiveNamespace::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Accent(_In_ ABI::AdaptiveNamespace::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Dark(_Out_ ABI::AdaptiveNamespace::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Dark(_In_ ABI::AdaptiveNamespace::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Light(_Out_ ABI::AdaptiveNamespace::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Light(_In_ ABI::AdaptiveNamespace::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Good(_Out_ ABI::AdaptiveNamespace::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Good(_In_ ABI::AdaptiveNamespace::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Warning(_Out_ ABI::AdaptiveNamespace::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Warning(_In_ ABI::AdaptiveNamespace::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Attention(_Out_ ABI::AdaptiveNamespace::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Attention(_In_ ABI::AdaptiveNamespace::IAdaptiveColorConfig* value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveColorConfig> m_default;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveColorConfig> m_accent;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveColorConfig> m_dark;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveColorConfig> m_light;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveColorConfig> m_good;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveColorConfig> m_warning;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveColorConfig> m_attention;
    };

    ActivatableClass(AdaptiveColorsConfig);
AdaptiveNamespaceEnd
