// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "RenderedAdaptiveCard.h"
#include "AdaptiveActionInvoker.g.h"

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct AdaptiveActionInvoker : AdaptiveActionInvokerT < AdaptiveActionInvoker>
    {
        AdaptiveActionInvoker(WinUI3::RenderedAdaptiveCard const& renderResult = nullptr) :
            m_weakRenderResult(renderResult)
        {
        }

        AdaptiveActionInvoker(winrt::AdaptiveCards::Rendering::WinUI3::implementation::RenderedAdaptiveCard* card);

        void SendActionEvent(ObjectModel::WinUI3::IAdaptiveActionElement const& actionElement);

    private:
        winrt::weak_ref<WinUI3::RenderedAdaptiveCard> m_weakRenderResult;
    };
}
namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct AdaptiveActionInvoker : AdaptiveActionInvokerT<AdaptiveActionInvoker, implementation::AdaptiveActionInvoker>
    {
    };
}

