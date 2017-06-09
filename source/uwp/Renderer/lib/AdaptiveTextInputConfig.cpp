#include "pch.h"
#include "AdaptiveTextInputConfig.h"
#include "AdaptiveSeparationConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveTextInputConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveTextInputConfig::RuntimeClassInitialize(TextInputConfig textInputConfig) noexcept
    {
        m_sharedTextInputConfig = textInputConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInputConfig::get_Separation(IAdaptiveSeparationConfig** separationConfig)
    {
        return MakeAndInitialize<AdaptiveSeparationConfig>(separationConfig, m_sharedTextInputConfig.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInputConfig::put_Separation(IAdaptiveSeparationConfig*)
    {
        return E_NOTIMPL;
    }
}
}
