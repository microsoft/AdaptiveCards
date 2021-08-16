// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveCards.Rendering.WinUI3.h"

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveMediaEventArgs
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
                                              ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveMediaEventArgs>
    {
        AdaptiveRuntime(AdaptiveMediaEventArgs);

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveMedia* media);

        // IAdaptiveMediaEventArgs
        IFACEMETHODIMP get_Media(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveMedia** media);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveMedia> m_media;
    };
}
