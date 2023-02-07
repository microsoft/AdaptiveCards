// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "RenderedAdaptiveCard.h"
#include "AdaptiveActionInvoker.g.h"

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct AdaptiveActionInvoker : AdaptiveActionInvokerT<AdaptiveActionInvoker>
    {
        AdaptiveActionInvoker(winrt::RenderedAdaptiveCard const& renderResult = nullptr) :
            m_weakRenderResult(renderResult)
        {
        }

        void SendActionEvent(winrt::IAdaptiveActionElement const& actionElement);
        winrt::weak_ref<winrt::RenderedAdaptiveCard> m_weakRenderResult;
    };
}
namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct AdaptiveActionInvoker : AdaptiveActionInvokerT<AdaptiveActionInvoker, implementation::AdaptiveActionInvoker>
    {
    };
}
