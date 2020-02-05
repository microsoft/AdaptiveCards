// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    class AdaptiveSpacingConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveSpacingConfig>
    {
        AdaptiveRuntime(AdaptiveSpacingConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(SpacingConfig SpacingConfig) noexcept;

        IFACEMETHODIMP get_Small(_Out_ UINT32* value);
        IFACEMETHODIMP put_Small(UINT32 value);

        IFACEMETHODIMP get_Default(_Out_ UINT32* value);
        IFACEMETHODIMP put_Default(UINT32 value);

        IFACEMETHODIMP get_Medium(_Out_ UINT32* value);
        IFACEMETHODIMP put_Medium(UINT32 value);

        IFACEMETHODIMP get_Large(_Out_ UINT32* value);
        IFACEMETHODIMP put_Large(UINT32 value);

        IFACEMETHODIMP get_ExtraLarge(_Out_ UINT32* value);
        IFACEMETHODIMP put_ExtraLarge(UINT32 value);

        IFACEMETHODIMP get_Padding(_Out_ UINT32* value);
        IFACEMETHODIMP put_Padding(UINT32 value);

    private:
        UINT32 m_small;
        UINT32 m_default;
        UINT32 m_medium;
        UINT32 m_large;
        UINT32 m_extraLarge;
        UINT32 m_padding;
    };

    ActivatableClass(AdaptiveSpacingConfig);
}
