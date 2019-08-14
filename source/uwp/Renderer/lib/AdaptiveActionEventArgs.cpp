// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionEventArgs.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveActionEventArgs::RuntimeClassInitialize() { return S_OK; }

    HRESULT AdaptiveActionEventArgs::RuntimeClassInitialize(_In_ IAdaptiveActionElement* action, _In_ IAdaptiveInputs* inputs)
    {
        m_action = action;
        m_inputs = inputs;
        return S_OK;
    }

    HRESULT AdaptiveActionEventArgs::get_Action(_COM_Outptr_ IAdaptiveActionElement** action)
    {
        return m_action.CopyTo(action);
    }

    IFACEMETHODIMP AdaptiveActionEventArgs::get_Inputs(_COM_Outptr_ IAdaptiveInputs** inputs)
    {
        return m_inputs.CopyTo(inputs);
    }
}
