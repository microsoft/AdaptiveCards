#include "pch.h"
#include "AdaptiveImageConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespaceRef;

AdaptiveNamespaceStart
    HRESULT AdaptiveImageConfig::RuntimeClassInitialize() noexcept try
    {
        ImageConfig imageConfig;
        return RuntimeClassInitialize(imageConfig);
    } CATCH_RETURN;

    HRESULT AdaptiveImageConfig::RuntimeClassInitialize(ImageConfig sharedImageConfig) noexcept
    {
        m_imageSize = static_cast<ABI::AdaptiveNamespaceRef::ImageSize>(sharedImageConfig.imageSize);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageConfig::get_ImageSize(ABI::AdaptiveNamespaceRef::ImageSize* imageSize)
    {
        *imageSize = m_imageSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageConfig::put_ImageSize(ABI::AdaptiveNamespaceRef::ImageSize imageSize)
    {
        m_imageSize = imageSize;
        return S_OK;
    }
AdaptiveNamespaceEnd
