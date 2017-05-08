#include "pch.h"
#include "AdaptiveToggleInputOptions.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveToggleInputOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveToggleInputOptions::RuntimeClassInitialize(ToggleInputOptions toggleInputOptions) noexcept
    {
        m_sharedToggleInputOptions = toggleInputOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInputOptions::get_Separation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedToggleInputOptions.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveToggleInputOptions::put_Separation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }
}
}
