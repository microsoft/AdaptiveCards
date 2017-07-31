#include "pch.h"
#include "Util.h"
#include "AdaptiveSeparationConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveSeparationConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveSeparationConfig::RuntimeClassInitialize(SeparationConfig separationConfig) noexcept
    {
        m_sharedSeparationConfig = separationConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationConfig::get_Spacing(UINT32* value)
    {
        *value = m_sharedSeparationConfig.spacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationConfig::put_Spacing(UINT32 value)
    {
        m_sharedSeparationConfig.spacing = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationConfig::get_LineThickness(UINT32* value)
    {
        *value = m_sharedSeparationConfig.lineThickness;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationConfig::put_LineThickness(UINT32 value)
    {
        m_sharedSeparationConfig.lineThickness = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationConfig::get_LineColor(ABI::Windows::UI::Color* value)
    {
        return GetColorFromString(m_sharedSeparationConfig.lineColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparationConfig::put_LineColor(ABI::Windows::UI::Color /*value*/)
    {
        return E_NOTIMPL;
    }
}
}
