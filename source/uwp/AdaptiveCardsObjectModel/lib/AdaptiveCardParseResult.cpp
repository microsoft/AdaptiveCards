// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardParseResult.h"

#include "AdaptiveCard.h"
#include <windows.foundation.collections.h>
#include "vector.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    AdaptiveCardParseResult::AdaptiveCardParseResult() {}

    HRESULT AdaptiveCardParseResult::RuntimeClassInitialize()
    {
        m_errors = Make<Vector<AdaptiveError*>>();
        m_warnings = Make<Vector<AdaptiveWarning*>>();
        return S_OK;
    }

    HRESULT AdaptiveCardParseResult::RuntimeClassInitialize(_In_ IAdaptiveCard* value)
    {
        m_adaptiveCard = value;
        return S_OK;
    }

    HRESULT AdaptiveCardParseResult::get_AdaptiveCard(_COM_Outptr_ IAdaptiveCard** value)
    {
        return m_adaptiveCard.CopyTo(value);
    }

    HRESULT AdaptiveCardParseResult::get_Errors(
        _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveError*>** value)
    {
        return m_errors.CopyTo(value);
    }

    HRESULT AdaptiveCardParseResult::get_Warnings(
        _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveWarning*>** value)
    {
        return m_warnings.CopyTo(value);
    }

    HRESULT AdaptiveCardParseResult::put_AdaptiveCard(_In_ IAdaptiveCard* value)
    {
        m_adaptiveCard = value;
        return S_OK;
    }
}
