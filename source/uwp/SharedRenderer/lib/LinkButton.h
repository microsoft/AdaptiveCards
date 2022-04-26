// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "LinkButton.g.h"
#include "LinkButtonAutomationPeer.g.h"

namespace AdaptiveCards::Rendering::Xaml_Rendering
{
    // LinkButtonAutomationPeer extends WUX::ButtonAutomationPeer
    struct LinkButtonAutomationPeer : public LinkButtonAutomationPeerT<LinkButtonAutomationPeer>
    {
    public:
        LinkButtonAutomationPeer(Uwp::LinkButton const& owner) :
            LinkButtonAutomationPeerT<LinkButtonAutomationPeer>(owner)
        {
        }

        winrt::AutomationControlType GetAutomationControlTypeCore() const
        {
            return winrt::AutomationControlType::Hyperlink;
        }
    };

    struct LinkButton : public LinkButtonT<LinkButton>
    {
    public:
        LinkButton() : LinkButtonT<LinkButton>() {}

        winrt::AutomationPeer OnCreateAutomationPeer()
        {
            if (!_autoPeer)
            {
                _autoPeer = winrt::make<implementation::LinkButtonAutomationPeer>(*this);
            }
            return _autoPeer;
        }

    private:
        Uwp::LinkButtonAutomationPeer _autoPeer{nullptr};
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct LinkButton : LinkButtonT<LinkButton, implementation::LinkButton>
    {
    };

    struct LinkButtonAutomationPeer : LinkButtonAutomationPeerT<LinkButtonAutomationPeer, implementation::LinkButtonAutomationPeer>
    {
    };
}
