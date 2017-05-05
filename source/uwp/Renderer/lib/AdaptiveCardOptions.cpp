#include "pch.h"
#include "Util.h"
#include "AdaptiveCardOptions.h"
#include "AdaptiveBoundaryOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveCardOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveCardOptions::RuntimeClassInitialize(AdaptiveCards::AdaptiveCardOptions adaptiveCardOptions) noexcept
    {
        m_sharedAdaptiveCardOptions = adaptiveCardOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::get_Padding(IAdaptiveBoundaryOptions** boundaryOptions)
    {
        return MakeAndInitialize<AdaptiveBoundaryOptions>(boundaryOptions, m_sharedAdaptiveCardOptions.padding);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::put_Padding(IAdaptiveBoundaryOptions* value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::get_BackgroundColor(Color* value)
    {
        return GetColorFromString(m_sharedAdaptiveCardOptions.backgroundColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardOptions::put_BackgroundColor(Color value)
    {
        return E_NOTIMPL;
    }
}}
