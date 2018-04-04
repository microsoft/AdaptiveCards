#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveFontWeightsConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveFontWeightsConfig>
    {
        AdaptiveRuntime(AdaptiveFontWeightsConfig)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(FontWeightsConfig fontWeightsConfig) noexcept;

        IFACEMETHODIMP get_Lighter(_Out_ UINT16 *value);
        IFACEMETHODIMP put_Lighter(_In_ UINT16 value);

        IFACEMETHODIMP get_Default(_Out_ UINT16 *value);
        IFACEMETHODIMP put_Default(_In_ UINT16 value);

        IFACEMETHODIMP get_Bolder(_Out_ UINT16 *value);
        IFACEMETHODIMP put_Bolder(_In_ UINT16 value);

    private:
        UINT16 m_default;
        UINT16 m_lighter;
        UINT16 m_bolder;
    };

    ActivatableClass(AdaptiveFontWeightsConfig);
AdaptiveNamespaceEnd