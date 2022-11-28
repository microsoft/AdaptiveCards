// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "util.h"
#include "InputValue.h"
#include "AdaptiveInputs.h"
#include "RenderedAdaptiveCard.g.h"

template<typename TSrc, typename TPayload> struct auto_event
{
    using handler = winrt::TypedEventHandler<TSrc, TPayload>;
    winrt::event<handler> m_event;
    auto operator()(handler const& t) { return m_event.add(t); }
    void operator()(winrt::event_token const& t) { return m_event.remove(t); }
    auto operator()(TSrc const& src, TPayload const& p) { return m_event(src, p); }
};

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    struct DECLSPEC_UUID("F25E0D36-0B5B-4398-AFC8-F84105EC46A2") RenderedAdaptiveCard
        : RenderedAdaptiveCardT<RenderedAdaptiveCard, ITypePeek>
    {
        RenderedAdaptiveCard();
        RenderedAdaptiveCard(winrt::IVector<winrt::AdaptiveError> const& errors,
                             winrt::IVector<winrt::AdaptiveWarning> const& warnings);

        // IRenderedAdaptiveCard
        auto OriginatingCard() { return m_originatingCard; }
        auto OriginatingHostConfig() { return m_originatingHostConfig; }
        auto FrameworkElement() { return m_frameworkElement; }
        auto UserInputs() { return static_cast<winrt::render_xaml::AdaptiveInputs>(*m_inputs); }

        auto_event<winrt::render_xaml::RenderedAdaptiveCard, winrt::render_xaml::AdaptiveActionEventArgs> Action;
        auto_event<winrt::render_xaml::RenderedAdaptiveCard, winrt::render_xaml::AdaptiveMediaEventArgs> MediaClicked;
        property<winrt::IVector<winrt::AdaptiveError>> Errors;
        property<winrt::IVector<winrt::AdaptiveWarning>> Warnings;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        void AddInlineShowCard(winrt::AdaptiveActionSet const& actionSet,
                               winrt::IAdaptiveShowCardAction const& showCardAction,
                               winrt::xaml::UIElement const& showCardUIElement,
                               winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);

        void AddInlineShowCard(winrt::AdaptiveCard const& adaptiveCard,
                               winrt::IAdaptiveShowCardAction const& showCardAction,
                               winrt::xaml::UIElement const& showCardUIElement,
                               winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);

        void AddOverflowButton(winrt::AdaptiveActionSet const& actionSet, winrt::xaml::UIElement const& actionUIElement);

        void AddOverflowButton(winrt::AdaptiveCard const& actionCard, winrt::xaml::UIElement const& actionUIElement);

        void AddInputValue(winrt::render_xaml::IAdaptiveInputValue const& inputValue, winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);
        void LinkActionToCard(winrt::IAdaptiveActionElement const& submitAction, winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);
        void LinkCardToParent(winrt::AdaptiveCard const& card, winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);
        winrt::render_xaml::IAdaptiveInputValue GetInputValue(winrt::IAdaptiveInputElement const& inputElement);

        void SetFrameworkElement(winrt::xaml::FrameworkElement const& value);
        void SetOriginatingCard(winrt::AdaptiveCard const& value);
        void SetOriginatingHostConfig(winrt::render_xaml::AdaptiveHostConfig const& value);
        void SendActionEvent(winrt::IAdaptiveActionElement const& eventArgs);
        void SendMediaClickedEvent(winrt::AdaptiveMedia const& eventArgs);

    private:
        void HandleInlineShowCardEvent(winrt::IAdaptiveActionElement const& actionElement);

        void AddInlineShowCardHelper(uint32_t internalId,
                                     winrt::IAdaptiveShowCardAction const& showCardAction,
                                     winrt::xaml::UIElement const& showCardUIElement,
                                     winrt::render_xaml::AdaptiveRenderArgs const& renderArgs);

        winrt::AdaptiveCard m_originatingCard;
        winrt::render_xaml::AdaptiveHostConfig m_originatingHostConfig;
        winrt::com_ptr<winrt::implementation::AdaptiveInputs> m_inputs;
        winrt::xaml::FrameworkElement m_frameworkElement;

        // Map of rendered show cards. The key is the id of the show card action, and the value is the ShowCardInfo structure for that show card
        std::unordered_map<uint32_t, std::shared_ptr<ShowCardInfo>> m_showCards;

        // Map of the rendered overflow buttons keyed on action set Id. This is needed to move buttons around when a
        // show card from an overflow menu needs to be moved to a primary button in the action set
        std::unordered_map<uint32_t, winrt::xaml::UIElement> m_overflowButtons;
    };
}

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::factory_implementation
{
    struct RenderedAdaptiveCard : RenderedAdaptiveCardT<RenderedAdaptiveCard, implementation::RenderedAdaptiveCard>
    {
    };
}
