// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveNamespace
{
    class AdaptiveImageConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveImageConfig>
    {
        AdaptiveRuntime(AdaptiveImageConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ImageConfig ImageConfig) noexcept;

        IFACEMETHODIMP get_ImageSize(_Out_ ABI::AdaptiveNamespace::ImageSize* imageSize);
        IFACEMETHODIMP put_ImageSize(ABI::AdaptiveNamespace::ImageSize imageSize);

    private:
        ABI::AdaptiveNamespace::ImageSize m_imageSize;
    };

    ActivatableClass(AdaptiveImageConfig);
}
