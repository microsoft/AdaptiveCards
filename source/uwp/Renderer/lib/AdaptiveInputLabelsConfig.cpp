// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveInputLabelsConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveInputLabelsConfig::RuntimeClassInitialize() noexcept
    try
    {
        InputLabelsConfig inputLabelsConfig;
        return RuntimeClassInitialize(inputLabelsConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveInputLabelsConfig::RuntimeClassInitialize(InputLabelsConfig inputLabelsConfig) noexcept
    {
        MakeAndInitialize<AdaptiveInputLabelConfig>(m_requiredInputs.GetAddressOf(), inputLabelsConfig.requiredInputs);
        MakeAndInitialize<AdaptiveInputLabelConfig>(m_optionalInputs.GetAddressOf(), inputLabelsConfig.optionalInputs);

        return S_OK;
    }

    HRESULT AdaptiveInputLabelsConfig::get_RequiredInputs(_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig** requiredInputs)
    {
        return m_requiredInputs.CopyTo(requiredInputs);
    }

    HRESULT AdaptiveInputLabelsConfig::put_RequiredInputs(_In_ ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig* requiredInputs)
    {
        m_requiredInputs = requiredInputs;
        return S_OK;
    }

    HRESULT AdaptiveInputLabelsConfig::get_OptionalInputs(_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig** optionalInputs)
    {
        return m_optionalInputs.CopyTo(optionalInputs);
    }

    HRESULT AdaptiveInputLabelsConfig::put_OptionalInputs(_In_ ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig* optionalInputs)
    {
        m_optionalInputs = optionalInputs;
        return S_OK;
    }
}
