// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
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

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    struct DECLSPEC_UUID("F25E0D36-0B5B-4398-AFC8-F84105EC46A2") RenderedAdaptiveCard
        : RenderedAdaptiveCardT<RenderedAdaptiveCard, ITypePeek>
    {
        RenderedAdaptiveCard();
        RenderedAdaptiveCard(winrt::IVector<ObjectModel::Uwp::AdaptiveError> const& errors,
                             winrt::IVector<ObjectModel::Uwp::AdaptiveWarning> const& warnings);

        // IRenderedAdaptiveCard
        auto OriginatingCard() { return m_originatingCard; }
        auto OriginatingHostConfig() { return m_originatingHostConfig; }
        auto FrameworkElement() { return m_frameworkElement; }
        auto UserInputs() { return static_cast<Uwp::AdaptiveInputs>(*m_inputs); }

        auto_event<Uwp::RenderedAdaptiveCard, Uwp::AdaptiveActionEventArgs> Action;
        auto_event<Uwp::RenderedAdaptiveCard, Uwp::AdaptiveMediaEventArgs> MediaClicked;
        property<winrt::IVector<ObjectModel::Uwp::AdaptiveError>> Errors;
        property<winrt::IVector<ObjectModel::Uwp::AdaptiveWarning>> Warnings;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        void AddInlineShowCard(ObjectModel::Uwp::AdaptiveActionSet const& actionSet,
                               ObjectModel::Uwp::IAdaptiveShowCardAction const& showCardAction,
                               winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                               Rendering::Uwp::AdaptiveRenderArgs const& renderArgs);

        void AddInlineShowCard(ObjectModel::Uwp::AdaptiveCard const& adaptiveCard,
                               ObjectModel::Uwp::IAdaptiveShowCardAction const& showCardAction,
                               winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                               Uwp::AdaptiveRenderArgs const& renderArgs);

        void AddOverflowButton(ObjectModel::Uwp::AdaptiveActionSet const& actionSet,
                               winrt::Windows::UI::Xaml::UIElement const& actionUIElement);

        void AddOverflowButton(ObjectModel::Uwp::AdaptiveCard const& actionCard,
                               winrt::Windows::UI::Xaml::UIElement const& actionUIElement);

        void AddInputValue(Uwp::IAdaptiveInputValue const& inputValue, Uwp::AdaptiveRenderArgs const& renderArgs);
        void LinkActionToCard(ObjectModel::Uwp::IAdaptiveActionElement const& submitAction, Uwp::AdaptiveRenderArgs const& renderArgs);
        void LinkCardToParent(ObjectModel::Uwp::AdaptiveCard const& card, Uwp::AdaptiveRenderArgs const& renderArgs);
        Uwp::IAdaptiveInputValue GetInputValue(ObjectModel::Uwp::IAdaptiveInputElement const& inputElement);

        void SetFrameworkElement(winrt::Windows::UI::Xaml::FrameworkElement const& value);
        void SetOriginatingCard(ObjectModel::Uwp::AdaptiveCard const& value);
        void SetOriginatingHostConfig(Rendering::Uwp::AdaptiveHostConfig const& value);
        void SendActionEvent(ObjectModel::Uwp::IAdaptiveActionElement const& eventArgs);
        void SendMediaClickedEvent(ObjectModel::Uwp::AdaptiveMedia const& eventArgs);

    private:
        void HandleInlineShowCardEvent(ObjectModel::Uwp::IAdaptiveActionElement const& actionElement);

        void AddInlineShowCardHelper(uint32_t internalId,
                                     ObjectModel::Uwp::IAdaptiveShowCardAction const& showCardAction,
                                     winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                                     Uwp::AdaptiveRenderArgs const& renderArgs);

        ObjectModel::Uwp::AdaptiveCard m_originatingCard;
        Rendering::Uwp::AdaptiveHostConfig m_originatingHostConfig;
        winrt::com_ptr<Uwp::implementation::AdaptiveInputs> m_inputs;
        winrt::Windows::UI::Xaml::FrameworkElement m_frameworkElement;

        // Map of rendered show cards. The key is the id of the show card action, and the value is the ShowCardInfo structure for that show card
        std::unordered_map<uint32_t, std::shared_ptr<ShowCardInfo>> m_showCards;

        // Map of the rendered overflow buttons keyed on action set Id. This is needed to move buttons around when a
        // show card from an overflow menu needs to be moved to a primary button in the action set
        std::unordered_map<uint32_t, winrt::Windows::UI::Xaml::UIElement> m_overflowButtons;
    };
}

namespace winrt::AdaptiveCards::Rendering::Uwp::factory_implementation
{
    struct RenderedAdaptiveCard : RenderedAdaptiveCardT<RenderedAdaptiveCard, implementation::RenderedAdaptiveCard>
    {
    };
}
