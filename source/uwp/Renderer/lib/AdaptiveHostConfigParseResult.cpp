// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveHostConfigParseResult.h"

#include "AdaptiveCard.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>
#include "XamlBuilder.h"
#include "XamlHelpers.h"
#include "AdaptiveHostConfig.h"
#include "vector.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    AdaptiveHostConfigParseResult::AdaptiveHostConfigParseResult() {}

    HRESULT AdaptiveHostConfigParseResult::RuntimeClassInitialize()
    {
        m_errors = Make<Vector<AdaptiveError*>>();
        return S_OK;
    }

    HRESULT AdaptiveHostConfigParseResult::RuntimeClassInitialize(_In_ IAdaptiveHostConfig* value)
    {
        m_hostConfig = value;
        return S_OK;
    }

    HRESULT AdaptiveHostConfigParseResult::get_HostConfig(_COM_Outptr_ IAdaptiveHostConfig** value)
    {
        return m_hostConfig.CopyTo(value);
    }

    HRESULT AdaptiveHostConfigParseResult::get_Errors(
        _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveError*>** value)
    {
        return m_errors.CopyTo(value);
    }
}
