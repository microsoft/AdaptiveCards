// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveImageSetConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveImageSetConfig::RuntimeClassInitialize() noexcept
    try
    {
        ImageSetConfig imageSetConfig;
        return RuntimeClassInitialize(imageSetConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveImageSetConfig::RuntimeClassInitialize(ImageSetConfig sharedImageSetConfig) noexcept
    {
        m_imageSize = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize>(sharedImageSetConfig.imageSize);
        m_maxImageHeight = sharedImageSetConfig.maxImageHeight;
        return S_OK;
    }

    HRESULT AdaptiveImageSetConfig::get_ImageSize(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize* imageSize)
    {
        *imageSize = m_imageSize;
        return S_OK;
    }

    HRESULT AdaptiveImageSetConfig::put_ImageSize(ABI::AdaptiveCards::ObjectModel::Uwp::ImageSize imageSize)
    {
        m_imageSize = imageSize;
        return S_OK;
    }

    HRESULT AdaptiveImageSetConfig::get_MaxImageHeight(_Out_ UINT32* maxImageHeight)
    {
        *maxImageHeight = m_maxImageHeight;
        return S_OK;
    }

    HRESULT AdaptiveImageSetConfig::put_MaxImageHeight(UINT32 maxImageHeight)
    {
        m_maxImageHeight = maxImageHeight;
        return S_OK;
    }
}
