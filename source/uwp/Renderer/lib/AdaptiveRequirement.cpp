// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveRequirement.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveRequirement::RuntimeClassInitialize() { return S_OK; }

    HRESULT AdaptiveRequirement::RuntimeClassInitialize(_In_ HSTRING name, _In_ HSTRING version)
    {
        m_name.Set(name);
        m_version.Set(version);
        return S_OK;
    }

    HRESULT AdaptiveRequirement::RuntimeClassInitialize(const std::pair<const std::string, AdaptiveCards::SemanticVersion>& sharedRequirement) noexcept
    {
        RETURN_IF_FAILED(UTF8ToHString(sharedRequirement.first, m_name.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString((std::string)sharedRequirement.second, m_version.GetAddressOf()));
        return S_OK;
    }

    HRESULT AdaptiveRequirement::get_Name(_Outptr_ HSTRING* value) { return m_name.CopyTo(value); }

    HRESULT AdaptiveRequirement::put_Name(_In_ HSTRING value) { return m_name.Set(value); }

    HRESULT AdaptiveRequirement::get_Version(_Outptr_ HSTRING* value) { return m_version.CopyTo(value); }

    HRESULT AdaptiveRequirement::put_Version(_In_ HSTRING value) { return m_version.Set(value); }
}
