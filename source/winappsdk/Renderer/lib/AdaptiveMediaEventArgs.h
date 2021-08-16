// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveCards.Rendering.WinAppSDK.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveMediaEventArgs
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
                                              ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveMediaEventArgs>
    {
        AdaptiveRuntime(AdaptiveMediaEventArgs);

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveMedia* media);

        // IAdaptiveMediaEventArgs
        IFACEMETHODIMP get_Media(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveMedia** media);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::WinAppSDK::IAdaptiveMedia> m_media;
    };
}
