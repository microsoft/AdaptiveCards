// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    class AdaptiveImageSizesConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveImageSizesConfig>
    {
        AdaptiveRuntime(AdaptiveImageSizesConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ImageSizesConfig imageSizesConfig) noexcept;

        IFACEMETHODIMP get_Small(_Out_ UINT32* value);
        IFACEMETHODIMP put_Small(UINT32 value);

        IFACEMETHODIMP get_Medium(_Out_ UINT32* value);
        IFACEMETHODIMP put_Medium(UINT32 value);

        IFACEMETHODIMP get_Large(_Out_ UINT32* value);
        IFACEMETHODIMP put_Large(UINT32 value);

    private:
        UINT32 m_small;
        UINT32 m_medium;
        UINT32 m_large;
    };

    ActivatableClass(AdaptiveImageSizesConfig);
}
