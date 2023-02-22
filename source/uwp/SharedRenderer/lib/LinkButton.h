// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Xaml_Rendering
{
    // LinkButton is a templated button that exists strictly to behave as a button but appear as a link for
    // accessibility purposes.
    struct LinkButton : public winrt::ButtonT<LinkButton>
    {
        winrt::AutomationPeer OnCreateAutomationPeer();
    };

    struct LinkButtonAutomationPeer : public winrt::ButtonAutomationPeerT<LinkButtonAutomationPeer>
    {
        LinkButtonAutomationPeer(LinkButton& linkButton);

        winrt::AutomationControlType GetAutomationControlType() const;
        winrt::AutomationControlType GetAutomationControlTypeCore() const;
    };
}
