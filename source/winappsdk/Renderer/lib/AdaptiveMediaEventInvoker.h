// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "RenderedAdaptiveCard.h"
#include "AdaptiveMediaEventInvoker.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveMediaEventInvoker : AdaptiveMediaEventInvokerT < AdaptiveMediaEventInvoker>
    {
        AdaptiveMediaEventInvoker() {}

        AdaptiveMediaEventInvoker(WinUI3::RenderedAdaptiveCard const& renderResult);

        void SendMediaClickedEvent(winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveMedia const& mediaElement);

        winrt::weak_ref<WinUI3::RenderedAdaptiveCard> m_weakRenderResult;
    };
}

namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveMediaEventInvoker : AdaptiveMediaEventInvokerT<AdaptiveMediaEventInvoker, implementation::AdaptiveMediaEventInvoker>
    {
    };
}
