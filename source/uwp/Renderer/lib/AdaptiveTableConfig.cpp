// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTableConfig.h"

using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveTableConfig::RuntimeClassInitialize() noexcept
    try
    {
        TableConfig tableConfig;
        return RuntimeClassInitialize(tableConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveTableConfig::RuntimeClassInitialize(TableConfig tableConfig) noexcept
    {
        m_cellSpacing = tableConfig.cellSpacing;
        return S_OK;
    }

    HRESULT AdaptiveTableConfig::get_CellSpacing(_Out_ UINT32* cellSpacing)
    {
        *cellSpacing = m_cellSpacing;
        return S_OK;
    }

    HRESULT AdaptiveTableConfig::put_CellSpacing(UINT32 cellSpacing)
    {
        m_cellSpacing = cellSpacing;
        return S_OK;
    }
}
