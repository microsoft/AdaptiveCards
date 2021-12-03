// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFactSetTextConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveFactSetTextConfig::RuntimeClassInitialize() noexcept
    try
    {
        FactSetTextConfig textConfig;
        return RuntimeClassInitialize(textConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveFactSetTextConfig::RuntimeClassInitialize(FactSetTextConfig textConfig) noexcept
    {
        InitializeTextStyleConfig(textConfig);
        m_wrap = textConfig.wrap;
        m_maxWidth = textConfig.maxWidth;

        return S_OK;
    }

    HRESULT AdaptiveFactSetTextConfig::get_Wrap(_Out_ boolean* wrap)
    {
        *wrap = m_wrap;
        return S_OK;
    }
    HRESULT AdaptiveFactSetTextConfig::put_Wrap(boolean wrap)
    {
        m_wrap = wrap;
        return S_OK;
    }
    HRESULT AdaptiveFactSetTextConfig::get_MaxWidth(_Out_ UINT32* maxWidth)
    {
        *maxWidth = m_maxWidth;
        return S_OK;
    }
    HRESULT AdaptiveFactSetTextConfig::put_MaxWidth(UINT32 maxWidth)
    {
        m_maxWidth = maxWidth;
        return S_OK;
    }
}
