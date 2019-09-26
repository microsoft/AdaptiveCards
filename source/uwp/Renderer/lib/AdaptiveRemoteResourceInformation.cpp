// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveRemoteResourceInformation.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveRemoteResourceInformation::RuntimeClassInitialize() noexcept
    try
    {
        RemoteResourceInformation uriInformation;
        return RuntimeClassInitialize(uriInformation);
    }
    CATCH_RETURN;

    HRESULT AdaptiveRemoteResourceInformation::RuntimeClassInitialize(RemoteResourceInformation& uriInformation)
    try
    {
        RETURN_IF_FAILED(UTF8ToHString(uriInformation.url, m_url.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(uriInformation.mimeType, m_mimeType.GetAddressOf()));

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveRemoteResourceInformation::get_Url(_Outptr_ HSTRING* url) { return m_url.CopyTo(url); }

    HRESULT AdaptiveRemoteResourceInformation::put_Url(_In_ HSTRING url) { return m_url.Set(url); }

    HRESULT AdaptiveRemoteResourceInformation::get_MimeType(_Outptr_ HSTRING* mimeType)
    {
        return m_mimeType.CopyTo(mimeType);
    }

    HRESULT AdaptiveRemoteResourceInformation::put_MimeType(_In_ HSTRING mimeType) { return m_mimeType.Set(mimeType); }
}
