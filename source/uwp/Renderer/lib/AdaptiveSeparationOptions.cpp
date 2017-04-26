#include "pch.h"
#include "AdaptiveHostOptions.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "XamlCardRendererComponent.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveSeparationOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveSeparationOptions::RuntimeClassInitialize(SeparationOptions separationOptions) noexcept
    {
        m_sharedSeparationOptions = separationOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationOptions::get_Spacing(INT32* value)
    {
        *value = m_sharedSeparationOptions.spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationOptions::put_Spacing(INT32 value)
    {
        m_sharedSeparationOptions.spacing = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationOptions::get_LineThickness(INT32* value)
    {
        *value = m_sharedSeparationOptions.lineThickness;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationOptions::put_LineThickness(INT32 value)
    {
        m_sharedSeparationOptions.lineThickness = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationOptions::get_LineColor(ABI::Windows::UI::Color* value)
    {
        return GetColorFromString(m_sharedSeparationOptions.lineColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationOptions::put_LineColor(ABI::Windows::UI::Color value)
    {
        return E_NOTIMPL;
    }
}
}
