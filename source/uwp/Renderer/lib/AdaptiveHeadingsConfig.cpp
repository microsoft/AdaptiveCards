// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveHeadingsConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveHeadingsConfig::RuntimeClassInitialize() noexcept
    try
    {
        HeadingsConfig headingsConfig;
        return RuntimeClassInitialize(headingsConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveHeadingsConfig::RuntimeClassInitialize(HeadingsConfig headingsConfig) noexcept
    {
        m_level = headingsConfig.level;
        return S_OK;
    }

    HRESULT AdaptiveHeadingsConfig::get_Level(_Out_ UINT32* level)
    {
        *level = m_level;
        return S_OK;
    }

    HRESULT AdaptiveHeadingsConfig::put_Level(UINT32 level)
    {
        m_level = level;
        return S_OK;
    }
}
