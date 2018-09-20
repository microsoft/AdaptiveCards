#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveSpacingConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveSpacingConfig>
    {
        AdaptiveRuntime(AdaptiveSpacingConfig)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(SpacingConfig SpacingConfig) noexcept;

        IFACEMETHODIMP get_Small(_Out_ UINT32* value);
        IFACEMETHODIMP put_Small(_In_ UINT32 value);

        IFACEMETHODIMP get_Default(_Out_ UINT32* value);
        IFACEMETHODIMP put_Default(_In_ UINT32 value);

        IFACEMETHODIMP get_Medium(_Out_ UINT32* value);
        IFACEMETHODIMP put_Medium(_In_ UINT32 value);

        IFACEMETHODIMP get_Large(_Out_ UINT32* value);
        IFACEMETHODIMP put_Large(_In_ UINT32 value);

        IFACEMETHODIMP get_ExtraLarge(_Out_ UINT32* value);
        IFACEMETHODIMP put_ExtraLarge(_In_ UINT32 value);

        IFACEMETHODIMP get_Padding(_Out_ UINT32* value);
        IFACEMETHODIMP put_Padding(_In_ UINT32 value);

    private:
        UINT32 m_small;
        UINT32 m_default;
        UINT32 m_medium;
        UINT32 m_large;
        UINT32 m_extraLarge;
        UINT32 m_padding;
    };

    ActivatableClass(AdaptiveSpacingConfig);
AdaptiveNamespaceEnd