// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.WinUI3.h"
#include "util.h"
#include "InputValue.h"
#include "AdaptiveInputs.h"
#include "RenderedAdaptiveCard.g.h"

template<typename TSrc, typename TPayload> struct auto_event
{
    using handler = winrt::Windows::Foundation::TypedEventHandler<TSrc, TPayload>;
    winrt::event<handler> m_event;
    auto operator()(handler const& t) { return m_event.add(t); }
    void operator()(winrt::event_token const& t) { return m_event.remove(t); }
    auto operator()(TSrc const& src, TPayload const& p) { return m_event(src, p); }
};

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    struct DECLSPEC_UUID("F25E0D36-0B5B-4398-AFC8-F84105EC46A2") RenderedAdaptiveCard
        : RenderedAdaptiveCardT<RenderedAdaptiveCard, ITypePeek>
    {
        RenderedAdaptiveCard();
        RenderedAdaptiveCard(winrt::Windows::Foundation::Collections::IVector<ObjectModel::WinUI3::AdaptiveError> const& errors,
                             winrt::Windows::Foundation::Collections::IVector<ObjectModel::WinUI3::AdaptiveWarning> const& warnings);

        // IRenderedAdaptiveCard
        auto OriginatingCard() { return m_originatingCard; }
        auto OriginatingHostConfig() { return m_originatingHostConfig; }
        auto FrameworkElement() { return m_frameworkElement; }
        auto UserInputs() { return static_cast<WinUI3::AdaptiveInputs>(*m_inputs); }

        auto_event<WinUI3::RenderedAdaptiveCard, WinUI3::AdaptiveActionEventArgs> Action;
        auto_event<WinUI3::RenderedAdaptiveCard, WinUI3::AdaptiveMediaEventArgs> MediaClicked;
        property<winrt::Windows::Foundation::Collections::IVector<ObjectModel::WinUI3::AdaptiveError>> Errors;
        property<winrt::Windows::Foundation::Collections::IVector<ObjectModel::WinUI3::AdaptiveWarning>> Warnings;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        void AddInlineShowCard(ObjectModel::WinUI3::AdaptiveActionSet const& actionSet,
                               ObjectModel::WinUI3::IAdaptiveShowCardAction const& showCardAction,
                               winrt::Windows::UI::Xaml::UIElement const& actionButtonUIElement,
                               winrt::Windows::UI::Xaml::UIElement const& actionOverflowUIElement,
                               winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                               uint32_t primaryButtonIndex,
                               Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs);

        void AddInlineShowCard(ObjectModel::WinUI3::AdaptiveCard const& adaptiveCard,
                               ObjectModel::WinUI3::IAdaptiveShowCardAction const& showCardAction,
                               winrt::Windows::UI::Xaml::UIElement const& actionButtonUIElement,
                               winrt::Windows::UI::Xaml::UIElement const& actionOverflowUIElement,
                               winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                               uint32_t primaryButtonIndex,
                               WinUI3::AdaptiveRenderArgs const& renderArgs);

        void AddOverflowButton(ObjectModel::WinUI3::AdaptiveActionSet const& actionSet,
                               winrt::Windows::UI::Xaml::UIElement const& actionUIElement);

        void AddOverflowButton(ObjectModel::WinUI3::AdaptiveCard const& actionCard,
                               winrt::Windows::UI::Xaml::UIElement const& actionUIElement);

        void AddInputValue(WinUI3::IAdaptiveInputValue const& inputValue, WinUI3::AdaptiveRenderArgs const& renderArgs);
        void LinkActionToCard(ObjectModel::WinUI3::IAdaptiveActionElement const& submitAction,
                              WinUI3::AdaptiveRenderArgs const& renderArgs);
        void LinkCardToParent(ObjectModel::WinUI3::AdaptiveCard const& card, WinUI3::AdaptiveRenderArgs const& renderArgs);
        WinUI3::IAdaptiveInputValue GetInputValue(ObjectModel::WinUI3::IAdaptiveInputElement const& inputElement);

        void SetFrameworkElement(winrt::Windows::UI::Xaml::FrameworkElement const& value);
        void SetOriginatingCard(ObjectModel::WinUI3::AdaptiveCard const& value);
        void SetOriginatingHostConfig(Rendering::WinUI3::AdaptiveHostConfig const& value);
        void SendActionEvent(ObjectModel::WinUI3::IAdaptiveActionElement const& eventArgs);
        void SendMediaClickedEvent(ObjectModel::WinUI3::AdaptiveMedia const& eventArgs);

    private:
        void HandleInlineShowCardEvent(ObjectModel::WinUI3::IAdaptiveActionElement const& actionElement);

        void AddInlineShowCardHelper(uint32_t internalId,
                                     ObjectModel::WinUI3::IAdaptiveShowCardAction const& showCardAction,
                                     winrt::Windows::UI::Xaml::UIElement const& actionButtonUIElement,
                                     winrt::Windows::UI::Xaml::UIElement const& actionOverflowUIElement,
                                     winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                                     uint32_t primaryButtonIndex,
                                     WinUI3::AdaptiveRenderArgs const& renderArgs);

        ObjectModel::WinUI3::AdaptiveCard m_originatingCard;
        Rendering::WinUI3::AdaptiveHostConfig m_originatingHostConfig;
        winrt::com_ptr<WinUI3::implementation::AdaptiveInputs> m_inputs;
        winrt::Windows::UI::Xaml::FrameworkElement m_frameworkElement;

        // Map of rendered show cards. The key is the id of the show card action, and the value is the ShowCardInfo structure for that show card
        std::unordered_map<uint32_t, std::shared_ptr<ShowCardInfo>> m_showCards;

        // Map of the rendered overflow buttons keyed on action set Id. This is needed to move buttons around when a
        // show card from an overflow menu needs to be moved to a primary button in the action set
        std::unordered_map<uint32_t, winrt::Windows::UI::Xaml::UIElement> m_overflowButtons;
    };
}

namespace winrt::AdaptiveCards::Rendering::WinUI3::factory_implementation
{
    struct RenderedAdaptiveCard : RenderedAdaptiveCardT<RenderedAdaptiveCard, implementation::RenderedAdaptiveCard>
    {
    };
}
