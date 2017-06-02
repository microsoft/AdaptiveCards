#include "pch.h"
#include "AdaptiveNumberInputConfig.h"
#include "AdaptiveSeparationConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveNumberInputConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveNumberInputConfig::RuntimeClassInitialize(NumberInputConfig NumberInputConfig) noexcept
    {
        m_sharedNumberInputConfig = NumberInputConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInputConfig::get_Separation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedNumberInputConfig.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInputConfig::put_Separation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }
}
}
