#include "pch.h"
#include "AdaptiveDateInputOptions.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveDateInputOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveDateInputOptions::RuntimeClassInitialize(DateInputOptions dateInputOptions) noexcept
    {
        m_sharedDateInputOptions = dateInputOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInputOptions::get_Separation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedDateInputOptions.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveDateInputOptions::put_Separation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }
}
}
