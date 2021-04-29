// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveTextStyleConfig.h"
#include "AdaptiveTextStylesConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
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
        return S_OK;
    }

    HRESULT AdaptiveTextStylesConfig::get_Heading(ABI::AdaptiveNamespace::IAdaptiveTextStyleConfig** headingStyle)
    {
        return m_headingStyle.CopyTo(headingStyle);
    }

    IFACEMETHODIMP AdaptiveTextStylesConfig::put_Heading(ABI::AdaptiveNamespace::IAdaptiveTextStyleConfig* headingStyle)
    {
        m_headingStyle = headingStyle;
        return S_OK;
    }
}
