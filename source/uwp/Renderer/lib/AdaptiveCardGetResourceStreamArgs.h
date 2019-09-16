// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveNamespace
{
    class AdaptiveCardGetResourceStreamArgs
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>, ABI::AdaptiveNamespace::IAdaptiveCardGetResourceStreamArgs>
    {
        AdaptiveRuntime(AdaptiveCardGetResourceStreamArgs);

    public:
        HRESULT RuntimeClassInitialize(_In_ ABI::Windows::Foundation::IUriRuntimeClass* url);

        IFACEMETHODIMP get_Url(_COM_Outptr_ ABI::Windows::Foundation::IUriRuntimeClass** url);

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IUriRuntimeClass> m_url;
    };
}
