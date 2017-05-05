#include "pch.h"
#include "Util.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
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
    HRESULT AdaptiveSeparationOptions::get_Spacing(UINT32* value)
    {
        *value = m_sharedSeparationOptions.spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationOptions::put_Spacing(UINT32 value)
    {
        m_sharedSeparationOptions.spacing = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationOptions::get_LineThickness(UINT32* value)
    {
        *value = m_sharedSeparationOptions.lineThickness;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationOptions::put_LineThickness(UINT32 value)
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
