#include "pch.h"
#include "AdaptiveNumberInputOptions.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveNumberInputOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveNumberInputOptions::RuntimeClassInitialize(NumberInputOptions NumberInputOptions) noexcept
    {
        m_sharedNumberInputOptions = NumberInputOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInputOptions::get_Separation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedNumberInputOptions.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveNumberInputOptions::put_Separation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }
}
}
