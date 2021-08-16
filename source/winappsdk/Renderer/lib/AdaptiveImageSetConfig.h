// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveImageSetConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveImageSetConfig>
    {
        AdaptiveRuntime(AdaptiveImageSetConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ImageSetConfig ImageSetConfig) noexcept;

        IFACEMETHODIMP get_ImageSize(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize* imageSize);
        IFACEMETHODIMP put_ImageSize(ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize imageSize);

        IFACEMETHODIMP get_MaxImageHeight(_Out_ UINT32* maxImageHeight);
        IFACEMETHODIMP put_MaxImageHeight(UINT32 maxImageHeight);

    private:
        ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize m_imageSize;
        UINT32 m_maxImageHeight;
    };

    ActivatableClass(AdaptiveImageSetConfig);
}
