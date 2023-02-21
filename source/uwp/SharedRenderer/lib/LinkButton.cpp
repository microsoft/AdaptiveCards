// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "LinkButton.h"

namespace AdaptiveCards::Rendering::Xaml_Rendering
{
    winrt::AutomationPeer LinkButton::OnCreateAutomationPeer()
    {
        // instead of the standard ButtonAutomationPeer, use our custom peer
        return winrt::make<LinkButtonAutomationPeer>(*this);
    }

    LinkButtonAutomationPeer::LinkButtonAutomationPeer(LinkButton& linkButton) :
        winrt::ButtonAutomationPeerT<LinkButtonAutomationPeer>(linkButton.operator winrt::Button())
    {
    }

    winrt::AutomationControlType LinkButtonAutomationPeer::GetAutomationControlType() const
    {
        return winrt::AutomationControlType::Hyperlink;
    }

    winrt::AutomationControlType LinkButtonAutomationPeer::GetAutomationControlTypeCore() const
    {
        return winrt::AutomationControlType::Hyperlink;
    }
}
