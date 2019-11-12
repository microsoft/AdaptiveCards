// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "LinkButton.h"

namespace AdaptiveNamespace
{
    winrt::Windows::UI::Xaml::Automation::Peers::AutomationPeer LinkButton::OnCreateAutomationPeer()
    {
        // instead of the standard ButtonAutomationPeer, use our custom peer
        return winrt::make<LinkButtonAutomationPeer>(*this);
    }

    LinkButtonAutomationPeer::LinkButtonAutomationPeer(LinkButton& linkButton) :
        winrt::Windows::UI::Xaml::Automation::Peers::ButtonAutomationPeerT<LinkButtonAutomationPeer>(
            linkButton.operator winrt::Windows::UI::Xaml::Controls::Button())
    {
    }

    winrt::Windows::UI::Xaml::Automation::Peers::AutomationControlType LinkButtonAutomationPeer::GetAutomationControlType() const
    {
        return winrt::Windows::UI::Xaml::Automation::Peers::AutomationControlType::Hyperlink;
    }

    winrt::Windows::UI::Xaml::Automation::Peers::AutomationControlType LinkButtonAutomationPeer::GetAutomationControlTypeCore() const
    {
        return winrt::Windows::UI::Xaml::Automation::Peers::AutomationControlType::Hyperlink;
    }
}
