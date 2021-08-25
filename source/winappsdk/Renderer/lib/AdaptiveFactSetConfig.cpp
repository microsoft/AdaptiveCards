// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveFactSetConfig.h"
#include "AdaptiveFactSetConfig.g.cpp"
#include "AdaptiveFactSetTextConfig.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveFactSetConfig::AdaptiveFactSetConfig(::AdaptiveCards::FactSetConfig factSetConfig) :
        Title{winrt::make<implementation::AdaptiveFactSetTextConfig>(factSetConfig.title)},
        Value{winrt::make<implementation::AdaptiveFactSetTextConfig>(factSetConfig.value)},
        Spacing{factSetConfig.spacing}
    {
    }

    HRESULT AdaptiveFactSetConfig::get_Title(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFactSetTextConfig** titleTextConfig)
    {
        return m_title.CopyTo(titleTextConfig);
    }

    HRESULT AdaptiveFactSetConfig::put_Title(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFactSetTextConfig* titleTextConfig)
    {
        m_title = titleTextConfig;
        return S_OK;
    }

    HRESULT AdaptiveFactSetConfig::get_Value(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFactSetTextConfig** valueTextConfig)
    {
        return m_value.CopyTo(valueTextConfig);
    }

    HRESULT AdaptiveFactSetConfig::put_Value(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFactSetTextConfig* valueTextConfig)
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
