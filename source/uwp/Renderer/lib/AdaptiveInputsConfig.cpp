// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveInputsConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
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
        MakeAndInitialize<AdaptiveErrorMessageConfig>(m_errorMessage.GetAddressOf(), inputsConfig.errorMessage);
        MakeAndInitialize<AdaptiveInputLabelsConfig>(m_inputLabels.GetAddressOf(), inputsConfig.inputLabels);
       
        return S_OK;
    }

    HRESULT AdaptiveInputsConfig::get_ErrorMessage(_Outptr_ ABI::AdaptiveNamespace::IAdaptiveErrorMessageConfig** errorMessage)
    {
        return m_errorMessage.CopyTo(errorMessage);
    }

    HRESULT AdaptiveInputsConfig::put_ErrorMessage(_In_ ABI::AdaptiveNamespace::IAdaptiveErrorMessageConfig* errorMessage)
    {
        m_errorMessage = errorMessage;
        return S_OK;
    }

    HRESULT AdaptiveInputsConfig::get_InputLabels(_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputLabelsConfig** inputLabels)
    {
        return m_inputLabels.CopyTo(inputLabels);
    }

    HRESULT AdaptiveInputsConfig::put_InputLabels(_In_ ABI::AdaptiveNamespace::IAdaptiveInputLabelsConfig* inputLabels)
    {
        m_inputLabels = inputLabels;
        return S_OK;
    }
}
