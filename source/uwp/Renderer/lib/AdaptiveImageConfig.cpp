// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveImageConfig::RuntimeClassInitialize() noexcept
    try
    {
        ImageConfig imageConfig;
        return RuntimeClassInitialize(imageConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveImageConfig::RuntimeClassInitialize(ImageConfig sharedImageConfig) noexcept
    {
        m_imageSize = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize>(sharedImageConfig.imageSize);
        return S_OK;
    }

    HRESULT AdaptiveImageConfig::get_ImageSize(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize* imageSize)
    {
        *imageSize = m_imageSize;
        return S_OK;
    }

    HRESULT AdaptiveImageConfig::put_ImageSize(ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize imageSize)
    {
        m_imageSize = imageSize;
        return S_OK;
    }
}
