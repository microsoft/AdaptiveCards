// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardGetResourceStreamArgs.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveCardGetResourceStreamArgs::RuntimeClassInitialize(_In_ IUriRuntimeClass* url)
    {
        m_url = url;
        return S_OK;
    }

    HRESULT AdaptiveCardGetResourceStreamArgs::get_Url(_COM_Outptr_ IUriRuntimeClass** url)
    {
        ComPtr<IUriRuntimeClass> localUrl(m_url);
        *url = localUrl.Detach();
        return S_OK;
    }
}
