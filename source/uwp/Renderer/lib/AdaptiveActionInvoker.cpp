// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveActionInvoker.h"
#include "AdaptiveActionInvoker.g.cpp"
#include "Util.h"

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    void AdaptiveActionInvoker::SendActionEvent(winrt::IAdaptiveActionElement const& actionElement)
    {
        if (auto strong = peek_innards<winrt::implementation::RenderedAdaptiveCard>(m_weakRenderResult.get()))
        {
            strong->SendActionEvent(actionElement);
        }
    }
}
