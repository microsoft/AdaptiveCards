#include "pch.h"
#include "AdaptiveColumnSetOptions.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveColumnSetOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveColumnSetOptions::RuntimeClassInitialize(ColumnSetOptions columnSetOptions) noexcept
    {
        m_sharedColumnSetOptions = columnSetOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSetOptions::get_Separation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedColumnSetOptions.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColumnSetOptions::put_Separation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }
}
}
