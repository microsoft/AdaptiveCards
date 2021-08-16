// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveErrorMessageConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveErrorMessageConfig::RuntimeClassInitialize() noexcept
    try
    {
        ErrorMessageConfig errorMessageConfig;
        return RuntimeClassInitialize(errorMessageConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveErrorMessageConfig::RuntimeClassInitialize(ErrorMessageConfig errorMessageConfig) noexcept
    {
        m_size = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::TextSize>(errorMessageConfig.size);
        m_spacing = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::Spacing>(errorMessageConfig.spacing);
        m_weight = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight>(errorMessageConfig.weight);

        return S_OK;
    }

    HRESULT AdaptiveErrorMessageConfig::get_Size(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::TextSize* size)
    {
        *size = m_size;
        return S_OK;
    }

    HRESULT AdaptiveErrorMessageConfig::put_Size(ABI::AdaptiveCards::ObjectModel::Uwp::TextSize size)
    {
        m_size = size;
        return S_OK;
    }

    HRESULT AdaptiveErrorMessageConfig::get_Spacing(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::Spacing* spacing)
    {
        *spacing = m_spacing;
        return S_OK;
    }

    HRESULT AdaptiveErrorMessageConfig::put_Spacing(ABI::AdaptiveCards::ObjectModel::Uwp::Spacing spacing)
    {
        m_spacing = spacing;
        return S_OK;
    }

    HRESULT AdaptiveErrorMessageConfig::get_Weight(_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight* weight)
    {
        *weight = m_weight;
        return S_OK;
    }

    HRESULT AdaptiveErrorMessageConfig::put_Weight(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight weight)
    {
        m_weight = weight;
        return S_OK;
    }
}
