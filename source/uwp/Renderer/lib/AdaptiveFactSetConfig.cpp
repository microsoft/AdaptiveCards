// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFactSetConfig.h"
#include "AdaptiveTextConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveFactSetConfig::RuntimeClassInitialize() noexcept
    try
    {
        FactSetConfig factSetConfig;
        return RuntimeClassInitialize(factSetConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveFactSetConfig::RuntimeClassInitialize(FactSetConfig factSetConfig) noexcept
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveTextConfig>(m_title.GetAddressOf(), factSetConfig.title));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveTextConfig>(m_value.GetAddressOf(), factSetConfig.value));
        m_spacing = factSetConfig.spacing;

        return S_OK;
    }

    HRESULT AdaptiveFactSetConfig::get_Title(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveTextConfig** titleTextConfig)
    {
        return m_title.CopyTo(titleTextConfig);
    }

    HRESULT AdaptiveFactSetConfig::put_Title(_In_ ABI::AdaptiveNamespace::IAdaptiveTextConfig* titleTextConfig)
    {
        m_title = titleTextConfig;
        return S_OK;
    }

    HRESULT AdaptiveFactSetConfig::get_Value(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveTextConfig** valueTextConfig)
    {
        return m_value.CopyTo(valueTextConfig);
    }

    HRESULT AdaptiveFactSetConfig::put_Value(_In_ ABI::AdaptiveNamespace::IAdaptiveTextConfig* valueTextConfig)
    {
        m_value = valueTextConfig;
        return S_OK;
    }

    HRESULT AdaptiveFactSetConfig::get_Spacing(_Out_ UINT32* value)
    {
        *value = m_spacing;
        return S_OK;
    }

    HRESULT AdaptiveFactSetConfig::put_Spacing(UINT32 value)
    {
        m_spacing = value;
        return S_OK;
    }
}
