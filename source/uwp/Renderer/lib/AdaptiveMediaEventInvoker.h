// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "RenderedAdaptiveCard.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveMediaEventInvoker
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveMediaEventInvoker>
    {
        AdaptiveRuntime(AdaptiveMediaEventInvoker);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(_In_ ABI::AdaptiveCards::Rendering::Uwp::IRenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP SendMediaClickedEvent(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveMedia* mediaElement);

    private:
        Microsoft::WRL::WeakRef m_weakRenderResult;
    };

    class AdaptiveMediaEventInvokerFactory
        : public Microsoft::WRL::AgileActivationFactory<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveMediaEventInvokerFactory>

    {
        IFACEMETHODIMP CreateInstance(ABI::AdaptiveCards::Rendering::Uwp::IRenderedAdaptiveCard* renderResult,
                                      _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveMediaEventInvoker** result) override
        {
            return Microsoft::WRL::Details::MakeAndInitialize<AdaptiveMediaEventInvoker>(result, renderResult);
        }
    };

    ActivatableClassWithFactory(AdaptiveMediaEventInvoker, AdaptiveActionInvokerFactory);
}
