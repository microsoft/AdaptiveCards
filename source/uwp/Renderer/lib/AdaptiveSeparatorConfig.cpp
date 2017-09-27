#include "pch.h"
#include "AdaptiveSeparatorConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveSeparatorConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveSeparatorConfig::RuntimeClassInitialize(SeparatorConfig SeparatorConfig) noexcept try
    {
        m_sharedSeparatorConfig = SeparatorConfig;
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveSeparatorConfig::get_LineThickness(UINT32* lineThickness)
    {
        *lineThickness = m_sharedSeparatorConfig.lineThickness;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparatorConfig::put_LineThickness(UINT32 lineThickness)
    {
        m_sharedSeparatorConfig.lineThickness = lineThickness;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveSeparatorConfig::get_LineColor(ABI::Windows::UI::Color* value)
    {
        return GetColorFromString(m_sharedSeparatorConfig.lineColor, value);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveSeparatorConfig::put_LineColor(ABI::Windows::UI::Color /*value*/)
    {
        return E_NOTIMPL;
    }
}
}
