#include "pch.h"
#include "AdaptiveSeparatorConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

AdaptiveNamespaceStart
    HRESULT AdaptiveSeparatorConfig::RuntimeClassInitialize() noexcept try
    {
        SeparatorConfig separatorConfig;
        return RuntimeClassInitialize(separatorConfig);
    } CATCH_RETURN;

    HRESULT AdaptiveSeparatorConfig::RuntimeClassInitialize(SeparatorConfig sharedSeparatorConfig) noexcept try
    {
        RETURN_IF_FAILED(GetColorFromString(sharedSeparatorConfig.lineColor, &m_lineColor));
        m_lineThickness = sharedSeparatorConfig.lineThickness;
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveSeparatorConfig::get_LineThickness(UINT32* lineThickness)
    {
        *lineThickness = m_lineThickness;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSeparatorConfig::put_LineThickness(UINT32 lineThickness)
    {
        m_lineThickness = lineThickness;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveSeparatorConfig::get_LineColor(ABI::Windows::UI::Color* value)
    {
        *value = m_lineColor;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveSeparatorConfig::put_LineColor(ABI::Windows::UI::Color color)
    {
        m_lineColor = color;
        return S_OK;
    }
AdaptiveNamespaceEnd
