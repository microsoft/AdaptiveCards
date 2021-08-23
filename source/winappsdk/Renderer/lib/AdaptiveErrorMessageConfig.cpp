// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveErrorMessageConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;

namespace AdaptiveCards::Rendering::WinUI3
{
    HRESULT AdaptiveErrorMessageConfig::RuntimeClassInitialize() noexcept
    try
    {
        ErrorMessageConfig errorMessageConfig;
        return RuntimeClassInitialize(errorMessageConfig);
    }
    CATCH_RETURN();

    HRESULT AdaptiveErrorMessageConfig::RuntimeClassInitialize(ErrorMessageConfig errorMessageConfig) noexcept
    {
        m_size = static_cast<ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize>(errorMessageConfig.size);
        m_spacing = static_cast<ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing>(errorMessageConfig.spacing);
        m_weight = static_cast<ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight>(errorMessageConfig.weight);

        return S_OK;
    }

    HRESULT AdaptiveErrorMessageConfig::get_Size(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize* size)
    {
        *size = m_size;
        return S_OK;
    }

    HRESULT AdaptiveErrorMessageConfig::put_Size(ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize size)
    {
        m_size = size;
        return S_OK;
    }

    HRESULT AdaptiveErrorMessageConfig::get_Spacing(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    HRESULT AdaptiveErrorMessageConfig::put_Spacing(ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    HRESULT AdaptiveErrorMessageConfig::get_Weight(_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight* weight)
    {
        *weight = m_weight;
        return S_OK;
    }

    HRESULT AdaptiveErrorMessageConfig::put_Weight(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight weight)
    {
        m_weight = weight;
        return S_OK;
    }
}
