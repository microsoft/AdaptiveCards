#include "pch.h"
#include "XamlCardRendererComponent.h"
#include "AdaptiveTimeInputOptions.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveTimeInputOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveTimeInputOptions::RuntimeClassInitialize(TimeInputOptions timeInputOptions) noexcept
    {
        m_sharedTimeInputOptions = timeInputOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInputOptions::get_Separation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedTimeInputOptions.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTimeInputOptions::put_Separation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }
}
}
