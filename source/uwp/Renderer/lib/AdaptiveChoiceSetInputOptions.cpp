#include "pch.h"
#include "AdaptiveHostOptions.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "XamlCardRendererComponent.h"
#include "AdaptiveChoiceSetInputOptions.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

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
