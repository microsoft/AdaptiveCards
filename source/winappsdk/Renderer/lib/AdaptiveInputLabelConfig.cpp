// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveInputLabelConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveInputLabelConfig::RuntimeClassInitialize() noexcept
    try
    {
        InputLabelConfig inputLabelConfig;
        return RuntimeClassInitialize(inputLabelConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveInputLabelConfig::RuntimeClassInitialize(InputLabelConfig inputLabelConfig) noexcept
    {
        m_color = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::ForegroundColor>(inputLabelConfig.color);
        m_isSubtle = static_cast<boolean>(inputLabelConfig.isSubtle);
        m_size = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::TextSize>(inputLabelConfig.size);
        RETURN_IF_FAILED(UTF8ToHString(inputLabelConfig.suffix, m_suffix.GetAddressOf()));
        m_weight = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight>(inputLabelConfig.weight);

        return S_OK;
    }

    HRESULT AdaptiveInputLabelConfig::get_Color(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ForegroundColor* color)
    {
        *color = m_color;
        return S_OK;
    }

    HRESULT AdaptiveInputLabelConfig::put_Color(ABI::AdaptiveCards::ObjectModel::Uwp::ForegroundColor color)
    {
        m_color = color;
        return S_OK;
    }

    HRESULT AdaptiveInputLabelConfig::get_IsSubtle(_Outptr_ boolean* isSubtle)
    {
        *isSubtle = m_isSubtle;
        return S_OK;
    }

    HRESULT AdaptiveInputLabelConfig::put_IsSubtle(_In_ boolean isSubtle)
    {
        m_isSubtle = isSubtle;
        return S_OK;
    }

    HRESULT AdaptiveInputLabelConfig::get_Size(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::TextSize* size)
    {
        *size = m_size;
        return S_OK;
    }

    HRESULT AdaptiveInputLabelConfig::put_Size(ABI::AdaptiveCards::ObjectModel::Uwp::TextSize size)
    {
        m_size = size;
        return S_OK;
    }

    HRESULT AdaptiveInputLabelConfig::get_Suffix(_Outptr_ HSTRING* suffix) { return m_suffix.CopyTo(suffix); }

    HRESULT AdaptiveInputLabelConfig::put_Suffix(_In_ HSTRING suffix) { return m_suffix.Set(suffix); }

    HRESULT AdaptiveInputLabelConfig::get_Weight(_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight* weight)
    {
        *weight = m_weight;
        return S_OK;
    }

    HRESULT AdaptiveInputLabelConfig::put_Weight(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight weight)
    {
        m_weight = weight;
        return S_OK;
    }
}
