// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveInputsConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveInputsConfig::RuntimeClassInitialize() noexcept
    try
    {
        InputsConfig inputsConfig;
        return RuntimeClassInitialize(inputsConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveInputsConfig::RuntimeClassInitialize(InputsConfig inputsConfig) noexcept
    {
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveErrorMessageConfig>(m_errorMessage.GetAddressOf(), inputsConfig.errorMessage));
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveLabelConfig>(m_label.GetAddressOf(), inputsConfig.label));

        return S_OK;
    }

    HRESULT AdaptiveInputsConfig::get_ErrorMessage(_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveErrorMessageConfig** errorMessage)
    {
        return m_errorMessage.CopyTo(errorMessage);
    }

    HRESULT AdaptiveInputsConfig::put_ErrorMessage(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveErrorMessageConfig* errorMessage)
    {
        m_errorMessage = errorMessage;
        return S_OK;
    }

    HRESULT AdaptiveInputsConfig::get_Label(_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveLabelConfig** inputLabels)
    {
        return m_label.CopyTo(inputLabels);
    }

    HRESULT AdaptiveInputsConfig::put_Label(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveLabelConfig* inputLabels)
    {
        m_label = inputLabels;
        return S_OK;
    }
}
