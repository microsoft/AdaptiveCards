// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveActionInvoker.h"
#include "AdaptiveActionInvoker.g.cpp"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    void AdaptiveActionInvoker::SendActionEvent(ObjectModel::Uwp::IAdaptiveActionElement const& actionElement)
    {
        if (auto strong = peek_innards<implementation::RenderedAdaptiveCard>(m_weakRenderResult.get()))
        {
            strong->SendActionEvent(actionElement);
        }
    }
}
