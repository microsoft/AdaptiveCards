#include "pch.h"
#include "AdaptiveImageOptions.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveImageOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveImageOptions::RuntimeClassInitialize(ImageOptions ImageOptions) noexcept
    {
        m_sharedImageOptions = ImageOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageOptions::get_Separation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedImageOptions.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageOptions::put_Separation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }
}
}
