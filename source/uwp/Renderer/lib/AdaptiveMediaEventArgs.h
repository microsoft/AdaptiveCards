// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once
#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveMediaEventArgs
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveMediaEventArgs>
    {
        AdaptiveRuntime(AdaptiveMediaEventArgs);

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveMedia* media);

        // IAdaptiveMediaEventArgs
        IFACEMETHODIMP get_Media(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveMedia** media);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveMedia> m_media;
    };
}
