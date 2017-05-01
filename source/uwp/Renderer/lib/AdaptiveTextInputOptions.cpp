#include "pch.h"
#include "AdaptiveTextInputOptions.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveTextInputOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveTextInputOptions::RuntimeClassInitialize(TextInputOptions textInputOptions) noexcept
    {
        m_sharedTextInputOptions = textInputOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInputOptions::get_Separation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedTextInputOptions.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextInputOptions::put_Separation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }
}
}
