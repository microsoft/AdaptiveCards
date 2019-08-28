// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveSeparatorConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveSeparatorConfig::RuntimeClassInitialize() noexcept try
    {
        SeparatorConfig separatorConfig;
        return RuntimeClassInitialize(separatorConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveSeparatorConfig::RuntimeClassInitialize(SeparatorConfig sharedSeparatorConfig) noexcept try
    {
        RETURN_IF_FAILED(GetColorFromString(sharedSeparatorConfig.lineColor, &m_lineColor));
        m_lineThickness = sharedSeparatorConfig.lineThickness;
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveSeparatorConfig::get_LineThickness(_Out_ UINT32* lineThickness)
    {
        *lineThickness = m_lineThickness;
        return S_OK;
    }

    HRESULT AdaptiveSeparatorConfig::put_LineThickness(UINT32 lineThickness)
    {
        m_lineThickness = lineThickness;
        return S_OK;
    }

    HRESULT AdaptiveSeparatorConfig::get_LineColor(_Out_ ABI::Windows::UI::Color* value)
    {
        *value = m_lineColor;
        return S_OK;
    }

    HRESULT AdaptiveSeparatorConfig::put_LineColor(ABI::Windows::UI::Color color)
    {
        m_lineColor = color;
        return S_OK;
    }
}
