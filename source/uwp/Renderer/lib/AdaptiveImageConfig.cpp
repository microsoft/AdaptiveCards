#include "pch.h"
#include "AdaptiveImageConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

AdaptiveNamespaceStart
    HRESULT AdaptiveImageConfig::RuntimeClassInitialize() noexcept try
    {
        ImageConfig imageConfig;
        return RuntimeClassInitialize(imageConfig);
    } CATCH_RETURN;

    HRESULT AdaptiveImageConfig::RuntimeClassInitialize(ImageConfig sharedImageConfig) noexcept
    {
        m_imageSize = static_cast<ABI::AdaptiveNamespace::ImageSize>(sharedImageConfig.imageSize);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageConfig::get_ImageSize(ABI::AdaptiveNamespace::ImageSize* imageSize)
    {
        *imageSize = m_imageSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageConfig::put_ImageSize(ABI::AdaptiveNamespace::ImageSize imageSize)
    {
        m_imageSize = imageSize;
        return S_OK;
    }
AdaptiveNamespaceEnd
