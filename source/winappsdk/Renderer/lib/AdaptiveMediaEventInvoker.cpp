// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveMediaEventInvoker.h"
#include "AdaptiveMediaEventInvoker.g.cpp"
#include "Util.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveMediaEventInvoker::AdaptiveMediaEventInvoker(WinUI3::RenderedAdaptiveCard const& renderResult) :
        m_weakRenderResult(renderResult)
    {
    }

    void AdaptiveMediaEventInvoker::SendMediaClickedEvent(_In_ winrt::AdaptiveCards::ObjectModel::WinUI3::AdaptiveMedia const& mediaElement)
    {
        if (auto renderResult = peek_innards<implementation::RenderedAdaptiveCard>(m_weakRenderResult.get()))
        {
            renderResult->SendMediaClickedEvent(mediaElement);
        }
    }
}
