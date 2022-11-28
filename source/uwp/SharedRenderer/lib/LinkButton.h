// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Xaml_Rendering
{
    // LinkButton is a templated button that exists strictly to behave as a button but appear as a link for
    // accessibility purposes.
    struct LinkButton : public winrt::xaml_controls::ButtonT<LinkButton>
    {
        winrt::xaml_automation::Peers::AutomationPeer OnCreateAutomationPeer();
    };

    struct LinkButtonAutomationPeer : public winrt::xaml_automation::Peers::ButtonAutomationPeerT<LinkButtonAutomationPeer>
    {
        LinkButtonAutomationPeer(LinkButton& linkButton);

        winrt::xaml_automation::Peers::AutomationControlType GetAutomationControlType() const;
        winrt::xaml_automation::Peers::AutomationControlType GetAutomationControlTypeCore() const;
    };
}
