#include "pch.h"
#include "AdaptiveImageConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveImageConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveImageConfig::RuntimeClassInitialize(ImageConfig ImageConfig) noexcept
    {
        m_sharedImageConfig = ImageConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageConfig::get_ImageSize(ABI::AdaptiveCards::XamlCardRenderer::ImageSize* imageSize)
    {
        *imageSize = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ImageSize>(m_sharedImageConfig.imageSize);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageConfig::put_ImageSize(ABI::AdaptiveCards::XamlCardRenderer::ImageSize imageSize)
    {
        m_sharedImageConfig.imageSize = static_cast<AdaptiveCards::ImageSize>(imageSize);
        return S_OK;
    }
}
}
