// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveNamespace
{
    class AdaptiveMediaEventArgs
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>, ABI::AdaptiveNamespace::IAdaptiveMediaEventArgs>
    {
        AdaptiveRuntime(AdaptiveMediaEventArgs);

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveNamespace::IAdaptiveMedia* media);

        // IAdaptiveMediaEventArgs
        IFACEMETHODIMP get_Media(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveMedia** media);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveMedia> m_media;
    };
}
