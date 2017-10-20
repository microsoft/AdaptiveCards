#include "pch.h"
#include "AdaptiveImageConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Uwp;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveImageConfig::RuntimeClassInitialize() noexcept try
    {
        ImageConfig imageConfig;
        return RuntimeClassInitialize(imageConfig);
    } CATCH_RETURN;

    HRESULT AdaptiveImageConfig::RuntimeClassInitialize(ImageConfig sharedImageConfig) noexcept
    {
        m_imageSize = static_cast<ABI::AdaptiveCards::Uwp::ImageSize>(sharedImageConfig.imageSize);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageConfig::get_ImageSize(ABI::AdaptiveCards::Uwp::ImageSize* imageSize)
    {
        *imageSize = m_imageSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageConfig::put_ImageSize(ABI::AdaptiveCards::Uwp::ImageSize imageSize)
    {
        m_imageSize = imageSize;
        return S_OK;
    }
}
}
