#include "pch.h"
#include "AdaptiveImageSetConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveImageSetConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveImageSetConfig::RuntimeClassInitialize(ImageSetConfig ImageSetConfig) noexcept
    {
        m_sharedImageSetConfig = ImageSetConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSetConfig::get_ImageSize(ABI::AdaptiveCards::XamlCardRenderer::ImageSize* imageSize)
    {
        *imageSize = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ImageSize>(m_sharedImageSetConfig.imageSize);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSetConfig::put_ImageSize(ABI::AdaptiveCards::XamlCardRenderer::ImageSize imageSize)
    {
        m_sharedImageSetConfig.imageSize = static_cast<AdaptiveCards::ImageSize>(imageSize);
        return S_OK;
    }
}
}
