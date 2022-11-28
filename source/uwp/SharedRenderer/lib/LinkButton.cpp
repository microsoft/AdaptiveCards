// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "LinkButton.h"

namespace AdaptiveCards::Rendering::Xaml_Rendering
{
    winrt::xaml_automation::Peers::AutomationPeer LinkButton::OnCreateAutomationPeer()
    {
        // instead of the standard ButtonAutomationPeer, use our custom peer
        return winrt::make<LinkButtonAutomationPeer>(*this);
    }

    LinkButtonAutomationPeer::LinkButtonAutomationPeer(LinkButton& linkButton) :
        winrt::xaml_automation::Peers::ButtonAutomationPeerT<LinkButtonAutomationPeer>(linkButton.operator winrt::xaml_controls::Button())
    {
    }

    winrt::xaml_automation::Peers::AutomationControlType LinkButtonAutomationPeer::GetAutomationControlType() const
    {
        return winrt::xaml_automation::Peers::AutomationControlType::Hyperlink;
    }

    winrt::xaml_automation::Peers::AutomationControlType LinkButtonAutomationPeer::GetAutomationControlTypeCore() const
    {
        return winrt::xaml_automation::Peers::AutomationControlType::Hyperlink;
    }
}
