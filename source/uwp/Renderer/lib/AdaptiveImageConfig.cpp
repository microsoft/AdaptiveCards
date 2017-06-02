#include "pch.h"
#include "AdaptiveImageConfig.h"
#include "AdaptiveSeparationConfig.h"

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
    HRESULT AdaptiveImageConfig::get_Separation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedImageConfig.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageConfig::put_Separation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }
}
}
