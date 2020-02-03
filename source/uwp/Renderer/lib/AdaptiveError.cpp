// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveError.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveError::RuntimeClassInitialize() { return S_OK; }

    HRESULT AdaptiveError::RuntimeClassInitialize(ABI::AdaptiveNamespace::ErrorStatusCode statusCode, _In_ HSTRING message)
    {
        m_statusCode = statusCode;
        m_message.Set(message);
        return S_OK;
    }

    HRESULT AdaptiveError::get_StatusCode(_Out_ ABI::AdaptiveNamespace::ErrorStatusCode* value)
    {
        *value = m_statusCode;
        return S_OK;
    }

    HRESULT AdaptiveError::put_StatusCode(ABI::AdaptiveNamespace::ErrorStatusCode value)
    {
        m_statusCode = value;
        return S_OK;
    }

    HRESULT AdaptiveError::get_Message(_Outptr_ HSTRING* value) { return m_message.CopyTo(value); }

    HRESULT AdaptiveError::put_Message(_In_ HSTRING value) { return m_message.Set(value); }
}
