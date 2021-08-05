// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveError.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveError::RuntimeClassInitialize() { return S_OK; }

    HRESULT AdaptiveError::RuntimeClassInitialize(ABI::AdaptiveCards::ObjectModel::Uwp::ErrorStatusCode statusCode, _In_ HSTRING message)
    {
        m_statusCode = statusCode;
        m_message.Set(message);
        return S_OK;
    }

    HRESULT AdaptiveError::get_StatusCode(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ErrorStatusCode* value)
    {
        *value = m_statusCode;
        return S_OK;
    }

    HRESULT AdaptiveError::put_StatusCode(ABI::AdaptiveCards::ObjectModel::Uwp::ErrorStatusCode value)
    {
        m_statusCode = value;
        return S_OK;
    }

    HRESULT AdaptiveError::get_Message(_Outptr_ HSTRING* value) { return m_message.CopyTo(value); }

    HRESULT AdaptiveError::put_Message(_In_ HSTRING value) { return m_message.Set(value); }
}
