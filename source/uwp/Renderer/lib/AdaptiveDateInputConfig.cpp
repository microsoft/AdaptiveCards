#include "pch.h"
#include "AdaptiveDateInputConfig.h"
#include "AdaptiveSeparationConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveDateInputConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveDateInputConfig::RuntimeClassInitialize(DateInputConfig dateInputConfig) noexcept
    {
        m_sharedDateInputConfig = dateInputConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInputConfig::get_Separation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedDateInputConfig.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInputConfig::put_Separation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }
}
}
