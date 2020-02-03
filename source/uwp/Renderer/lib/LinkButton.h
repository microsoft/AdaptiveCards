// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    // LinkButton is a templated button that exists strictly to behave as a button but appear as a link for
    // accessibility purposes.
    struct LinkButton : public winrt::Windows::UI::Xaml::Controls::ButtonT<LinkButton>
    {
        winrt::Windows::UI::Xaml::Automation::Peers::AutomationPeer OnCreateAutomationPeer();
    };

    struct LinkButtonAutomationPeer
        : public winrt::Windows::UI::Xaml::Automation::Peers::ButtonAutomationPeerT<LinkButtonAutomationPeer>
    {
        LinkButtonAutomationPeer(LinkButton& linkButton);

        winrt::Windows::UI::Xaml::Automation::Peers::AutomationControlType GetAutomationControlType() const;
        winrt::Windows::UI::Xaml::Automation::Peers::AutomationControlType GetAutomationControlTypeCore() const;
    };
}
