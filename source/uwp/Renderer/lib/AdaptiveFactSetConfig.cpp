// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFactSetConfig.h"
#include "AdaptiveFactSetTextConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards::Rendering::Uwp
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
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFactSetTextConfig>(m_title.GetAddressOf(), factSetConfig.title));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveFactSetTextConfig>(m_value.GetAddressOf(), factSetConfig.value));
        m_spacing = factSetConfig.spacing;

        return S_OK;
    }

    HRESULT AdaptiveFactSetConfig::get_Title(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFactSetTextConfig** titleTextConfig)
    {
        return m_title.CopyTo(titleTextConfig);
    }

    HRESULT AdaptiveFactSetConfig::put_Title(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFactSetTextConfig* titleTextConfig)
    {
        m_title = titleTextConfig;
        return S_OK;
    }

    HRESULT AdaptiveFactSetConfig::get_Value(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFactSetTextConfig** valueTextConfig)
    {
        return m_value.CopyTo(valueTextConfig);
    }

    HRESULT AdaptiveFactSetConfig::put_Value(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFactSetTextConfig* valueTextConfig)
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
