// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextStyleConfig.h"
#include "AdaptiveTextStylesConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveTextStylesConfig::RuntimeClassInitialize() noexcept
    try
    {
        TextStylesConfig textStylesConfig;
        return RuntimeClassInitialize(textStylesConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveTextStylesConfig::RuntimeClassInitialize(TextStylesConfig textStylesConfig) noexcept
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveTextStyleConfig>(m_headingStyle.GetAddressOf(), textStylesConfig.heading));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveTextStyleConfig>(m_columnHeaderStyle.GetAddressOf(), textStylesConfig.columnHeader));
        return S_OK;
    }

    HRESULT AdaptiveTextStylesConfig::get_Heading(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextStyleConfig** headingStyle)
    {
        return m_headingStyle.CopyTo(headingStyle);
    }

    IFACEMETHODIMP AdaptiveTextStylesConfig::put_Heading(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextStyleConfig* headingStyle)
    {
        m_headingStyle = headingStyle;
        return S_OK;
    }

    HRESULT AdaptiveTextStylesConfig::get_ColumnHeader(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextStyleConfig** columnHeaderStyle)
    {
        return m_columnHeaderStyle.CopyTo(columnHeaderStyle);
    }

    IFACEMETHODIMP AdaptiveTextStylesConfig::put_ColumnHeader(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextStyleConfig* columnHeaderStyle)
    {
        m_columnHeaderStyle = columnHeaderStyle;
        return S_OK;
    }
}
