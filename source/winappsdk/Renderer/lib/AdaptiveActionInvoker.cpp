// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveActionInvoker.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::UI::Xaml;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    AdaptiveActionInvoker::AdaptiveActionInvoker(::AdaptiveCards::Rendering::WinUI3::RenderedAdaptiveCard* card) {
        winrt::com_ptr<::AdaptiveCards::Rendering::WinUI3::RenderedAdaptiveCard> c;
        winrt::copy_from_abi(c, card);
        m_weakRenderResult = c.as<WinUI3::RenderedAdaptiveCard>();
    }

    void AdaptiveActionInvoker::SendActionEvent(ObjectModel::WinUI3::IAdaptiveActionElement const& actionElement)
    {
        if (auto strong = PeekInnards<::AdaptiveCards::Rendering::WinUI3::RenderedAdaptiveCard>(m_weakRenderResult.get()))
        {
            strong->SendActionEvent(::to_abi(actionElement));
        }
    }
}
