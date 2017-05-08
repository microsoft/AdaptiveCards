#include "pch.h"
#include "AdaptiveImageSetOptions.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveImageSetOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveImageSetOptions::RuntimeClassInitialize(ImageSetOptions ImageSetOptions) noexcept
    {
        m_sharedImageSetOptions = ImageSetOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSetOptions::get_ImageSize(ABI::AdaptiveCards::XamlCardRenderer::ImageSize* imageSize)
    {
        *imageSize = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ImageSize>(m_sharedImageSetOptions.imageSize);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSetOptions::put_ImageSize(ABI::AdaptiveCards::XamlCardRenderer::ImageSize imageSize)
    {
        m_sharedImageSetOptions.imageSize = static_cast<AdaptiveCards::ImageSize>(imageSize);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSetOptions::get_Separation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedImageSetOptions.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSetOptions::put_Separation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }
}
}
