// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveWarning.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveWarning::RuntimeClassInitialize() { return S_OK; }

    HRESULT AdaptiveWarning::RuntimeClassInitialize(ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode statusCode,
                                                    _In_ HSTRING message)
    {
        m_statusCode = statusCode;
        m_message.Set(message);
        return S_OK;
    }

    HRESULT AdaptiveWarning::get_StatusCode(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode* value)
    {
        *value = m_statusCode;
        return S_OK;
    }

    HRESULT AdaptiveWarning::put_StatusCode(ABI::AdaptiveCards::ObjectModel::Uwp::WarningStatusCode value)
    {
        m_statusCode = value;
        return S_OK;
    }

    HRESULT AdaptiveWarning::get_Message(_Outptr_ HSTRING* value) { return m_message.CopyTo(value); }

    HRESULT AdaptiveWarning::put_Message(_In_ HSTRING value) { return m_message.Set(value); }
}
