// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::WinAppSDK
{
    class AdaptiveImageConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveImageConfig>
    {
        AdaptiveRuntime(AdaptiveImageConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ImageConfig ImageConfig) noexcept;

        IFACEMETHODIMP get_ImageSize(_Out_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::ImageSize* imageSize);
        IFACEMETHODIMP put_ImageSize(ABI::AdaptiveCards::ObjectModel::WinAppSDK::ImageSize imageSize);

    private:
        ABI::AdaptiveCards::ObjectModel::WinAppSDK::ImageSize m_imageSize;
    };

    ActivatableClass(AdaptiveImageConfig);
}
