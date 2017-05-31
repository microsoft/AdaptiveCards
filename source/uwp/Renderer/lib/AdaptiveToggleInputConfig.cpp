#include "pch.h"
#include "AdaptiveToggleInputConfig.h"
#include "AdaptiveSeparationConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveToggleInputConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveToggleInputConfig::RuntimeClassInitialize(ToggleInputConfig toggleInputConfig) noexcept
    {
        m_sharedToggleInputConfig = toggleInputConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInputConfig::get_Separation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedToggleInputConfig.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInputConfig::put_Separation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }
}
}
