// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveCardResourceResolvers.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveCardResourceResolvers::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveCardResourceResolvers::Set(_In_ HSTRING scheme, _In_ IAdaptiveCardResourceResolver* resolver)
    {
        std::string schemeString;
        RETURN_IF_FAILED(HStringToUTF8(scheme, schemeString));
        m_resourceResolvers[schemeString] = resolver;
        return S_OK;
    }

    HRESULT AdaptiveCardResourceResolvers::Get(_In_ HSTRING scheme, _COM_Outptr_ IAdaptiveCardResourceResolver** resolver)
    {
        std::string schemeString;
        RETURN_IF_FAILED(HStringToUTF8(scheme, schemeString));
        ComPtr<IAdaptiveCardResourceResolver> resolverPtr = m_resourceResolvers[schemeString];
        return resolverPtr.CopyTo(resolver);
    }
}
