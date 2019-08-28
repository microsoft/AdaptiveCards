// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "TextBlock.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("0c87566c-a58c-4332-8b3b-79c9714074f6") AdaptiveRemoteResourceInformation
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveRemoteResourceInformation>
    {
        AdaptiveRuntime(AdaptiveRemoteResourceInformation);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(RemoteResourceInformation& uriInformation);

        // IAdaptiveRemoteResourceInformation
        IFACEMETHODIMP get_Url(_Outptr_ HSTRING* url);
        IFACEMETHODIMP put_Url(_In_ HSTRING url);

        IFACEMETHODIMP get_MimeType(_Outptr_ HSTRING* text);
        IFACEMETHODIMP put_MimeType(_In_ HSTRING text);

    private:
        Microsoft::WRL::Wrappers::HString m_url;
        Microsoft::WRL::Wrappers::HString m_mimeType;
    };

    ActivatableClass(AdaptiveRemoteResourceInformation);
}
