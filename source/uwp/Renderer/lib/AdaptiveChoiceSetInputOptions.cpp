#include "pch.h"
#include "AdaptiveChoiceSetInputOptions.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveChoiceSetInputOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveChoiceSetInputOptions::RuntimeClassInitialize(ChoiceSetOptions choiceSetOptions) noexcept
    {
        m_sharedChoiceSetOptions = choiceSetOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInputOptions::get_Separation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedChoiceSetOptions.separation);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveChoiceSetInputOptions::put_Separation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }
}
}
