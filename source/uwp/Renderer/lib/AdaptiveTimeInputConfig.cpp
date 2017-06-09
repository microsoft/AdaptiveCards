#include "pch.h"
#include "XamlCardRendererComponent.h"
#include "AdaptiveTimeInputConfig.h"
#include "AdaptiveSeparationConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveTimeInputConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveTimeInputConfig::RuntimeClassInitialize(TimeInputConfig timeInputConfig) noexcept
    {
        m_sharedTimeInputConfig = timeInputConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInputConfig::get_Separation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedTimeInputConfig.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInputConfig::put_Separation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }
}
}
