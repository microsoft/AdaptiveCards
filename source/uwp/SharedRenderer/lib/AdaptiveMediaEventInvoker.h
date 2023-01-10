// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "RenderedAdaptiveCard.h"
#include "AdaptiveMediaEventInvoker.g.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct AdaptiveMediaEventInvoker : AdaptiveMediaEventInvokerT<AdaptiveMediaEventInvoker>
    {
        AdaptiveMediaEventInvoker(winrt::RenderedAdaptiveCard const& renderResult = nullptr) :
            m_weakRenderResult(renderResult)
        {
        }

        void SendMediaClickedEvent(winrt::AdaptiveMedia const& mediaElement);
        winrt::weak_ref<winrt::RenderedAdaptiveCard> m_weakRenderResult;
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct AdaptiveMediaEventInvoker : AdaptiveMediaEventInvokerT<AdaptiveMediaEventInvoker, implementation::AdaptiveMediaEventInvoker>
    {
    };
}
