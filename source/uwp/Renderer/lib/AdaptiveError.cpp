// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveError.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveError::RuntimeClassInitialize() { return S_OK; }

    HRESULT AdaptiveError::RuntimeClassInitialize(ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode statusCode, _In_ HSTRING message)
    {
        m_statusCode = statusCode;
        m_message.Set(message);
        return S_OK;
    }

    HRESULT AdaptiveError::get_StatusCode(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode* value)
    {
        *value = m_statusCode;
        return S_OK;
    }

    HRESULT AdaptiveError::put_StatusCode(ABI::AdaptiveCards::Rendering::Uwp::ErrorStatusCode value)
    {
        m_statusCode = value;
        return S_OK;
    }

    HRESULT AdaptiveError::get_Message(_Outptr_ HSTRING* value) { return m_message.CopyTo(value); }

    HRESULT AdaptiveError::put_Message(_In_ HSTRING value) { return m_message.Set(value); }
}
