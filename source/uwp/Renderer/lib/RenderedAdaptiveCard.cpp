// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "RenderedAdaptiveCard.h"
#include "RenderedAdaptiveCard.g.cpp"

#include "AdaptiveActionEventArgs.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveMediaEventArgs.h"
#include "ElementTagContent.h"

using namespace concurrency;

namespace winrt::AdaptiveCards::Rendering::Uwp::implementation
{
    RenderedAdaptiveCard::RenderedAdaptiveCard() :
        RenderedAdaptiveCard(winrt::single_threaded_vector<ObjectModel::Uwp::AdaptiveError>(),
                             winrt::single_threaded_vector<ObjectModel::Uwp::AdaptiveWarning>())
    {
    }

    RenderedAdaptiveCard::RenderedAdaptiveCard(
        winrt::Windows::Foundation::Collections::IVector<ObjectModel::Uwp::AdaptiveError> const& errors,
        winrt::Windows::Foundation::Collections::IVector<ObjectModel::Uwp::AdaptiveWarning> const& warnings) :
        Errors{errors},
        Warnings{warnings}, m_inputs{winrt::make_self<implementation::AdaptiveInputs>()}, m_frameworkElement{nullptr}
    {
    }

    void RenderedAdaptiveCard::HandleInlineShowCardEvent(ObjectModel::Uwp::IAdaptiveActionElement const& actionElement)
    {
        auto showCardAction = actionElement.as<ObjectModel::Uwp::AdaptiveShowCardAction>();
        auto showCardToToggle = showCardAction.InternalId();
        auto found = m_showCards.find(showCardToToggle);

        if (found != m_showCards.end())
        {
            std::shared_ptr<ShowCardInfo> showCardInfoToHandle = found->second;

            // Determine if the card is currently being shown
            winrt::Windows::UI::Xaml::Visibility currentVisibility = showCardInfoToHandle->cardUIElement.Visibility();

            if (currentVisibility == winrt::Windows::UI::Xaml::Visibility::Visible)
            {
                // If it was shown, hide it
                showCardInfoToHandle->cardUIElement.Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
            }
            else
            {
                // If it was hidden, show it, and hide all other cards in this action set
                showCardInfoToHandle->cardUIElement.Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);

                for (auto& showCardEntry : m_showCards)
                {
                    const UINT32 showCardId = showCardEntry.first;
                    auto currentShowCardInfo = showCardEntry.second;
                    if ((showCardInfoToHandle->actionSetId == currentShowCardInfo->actionSetId) && (showCardToToggle != showCardId))
                    {
                        currentShowCardInfo->cardUIElement.Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);
                    }
                }
            }
        }
    }

    void HandleToggleVisibilityClick(winrt::Windows::UI::Xaml::FrameworkElement const& cardFrameworkElement,
                                     ObjectModel::Uwp::IAdaptiveActionElement const& action)
    {
        auto toggleAction = action.as<ObjectModel::Uwp::AdaptiveToggleVisibilityAction>();
        std::vector<rtxaml::Controls::Panel> parentPanels;
        for (auto&& currentTarget : toggleAction.TargetElements())
        {
            auto toggleId = currentTarget.ElementId();
            auto toggle = currentTarget.IsVisible();

            if (auto toggleObject = cardFrameworkElement.FindName(toggleId))
            {
                auto toggleElementAsUIElement = toggleObject.as<winrt::Windows::UI::Xaml::UIElement>();
                auto toggleElementAsFrameworkElement = toggleObject.as<winrt::Windows::UI::Xaml::FrameworkElement>();
                // TODO: we need to peek to make sure it's our own class, right? because it's coming from the Tag
                // auto elementTagContent = peek_innards<rtrender::implementation::ElementTagContent>(toggleElementAsFrameworkElement);
                auto elementTagContent = toggleElementAsFrameworkElement.Tag().as<rtrender::ElementTagContent>();

                winrt::Windows::UI::Xaml::Visibility visibilityToSet = winrt::Windows::UI::Xaml::Visibility::Visible;
                if (toggle == ObjectModel::Uwp::IsVisible::IsVisibleTrue)
                {
                    visibilityToSet = winrt::Windows::UI::Xaml::Visibility::Visible;
                }
                else if (toggle == ObjectModel::Uwp::IsVisible::IsVisibleFalse)
                {
                    visibilityToSet = winrt::Windows::UI::Xaml::Visibility::Collapsed;
                }
                else if (toggle == ObjectModel::Uwp::IsVisible::IsVisibleToggle)
                {
                    bool currentVisibility = elementTagContent.ExpectedVisibility();
                    visibilityToSet = currentVisibility ? winrt::Windows::UI::Xaml::Visibility::Collapsed :
                                                          winrt::Windows::UI::Xaml::Visibility::Visible;
                }

                toggleElementAsUIElement.Visibility(visibilityToSet);
                elementTagContent.ExpectedVisibility(visibilityToSet == winrt::Windows::UI::Xaml::Visibility::Visible);

                auto parentPanel = elementTagContent.ParentPanel();
                parentPanels.emplace_back(parentPanel);

                auto cardElement = elementTagContent.CardElement();

                if (auto cardElementAsColumn = cardElement.try_as<ObjectModel::Uwp::AdaptiveColumn>())
                {
                    auto columnDefinition = elementTagContent.ColumnDefinition();
                    ::AdaptiveCards::Rendering::Uwp::XamlHelpers::HandleColumnWidth(
                        cardElementAsColumn, (visibilityToSet == winrt::Windows::UI::Xaml::Visibility::Visible), columnDefinition);
                }
            }
        }

        for (auto&& parentPanel : parentPanels)
        {
            if (parentPanel)
            {
                ::AdaptiveCards::Rendering::Uwp::XamlHelpers::SetSeparatorVisibility(parentPanel);
            }
        }
    }

    void RenderedAdaptiveCard::SendActionEvent(ObjectModel::Uwp::IAdaptiveActionElement const& actionElement)
    {
        auto actionType = actionElement.ActionType();

        switch (actionType)
        {
        case ObjectModel::Uwp::ActionType::ToggleVisibility:
            return HandleToggleVisibilityClick(m_frameworkElement, actionElement);

        case ObjectModel::Uwp::ActionType::ShowCard:
        {
            auto actionConfig = m_originatingHostConfig.Actions();
            auto showCardConfig = actionConfig.ShowCard();
            auto actionMode = showCardConfig.ActionMode();
            bool handleInlineShowCard = (actionMode == Uwp::ActionMode::Inline);

            if (handleInlineShowCard)
            {
                // If the host is custom rendering ActionSets, they are responsible for showing and hiding the cards therein.
                // Check if the action being invoked is one we registered, otherwise we'll send the action to the host.
                auto showCardAction = actionElement.as<ObjectModel::Uwp::AdaptiveShowCardAction>();
                handleInlineShowCard &= (m_showCards.find(showCardAction.InternalId()) != m_showCards.end());
            }

            if (handleInlineShowCard)
            {
                return HandleInlineShowCardEvent(actionElement);
            }
            else
            {
                Action(*this, winrt::make<implementation::AdaptiveActionEventArgs>(actionElement, nullptr));
            }
        }
        case ObjectModel::Uwp::ActionType::Submit:
        case ObjectModel::Uwp::ActionType::Execute:
        {
            ObjectModel::Uwp::AssociatedInputs associatedInputs;

            if (actionType == ObjectModel::Uwp::ActionType::Submit)
            {
                associatedInputs = actionElement.as<ObjectModel::Uwp::AdaptiveSubmitAction>().AssociatedInputs();
            }
            else
            {
                associatedInputs = actionElement.as<ObjectModel::Uwp::AdaptiveExecuteAction>().AssociatedInputs();
            }

            Uwp::AdaptiveInputs gatheredInputs;
            bool inputsAreValid;
            if (associatedInputs == ObjectModel::Uwp::AssociatedInputs::None)
            {
                gatheredInputs = winrt::make<implementation::AdaptiveInputs>();
                inputsAreValid = true;
            }
            else
            {
                gatheredInputs = UserInputs();
                inputsAreValid = gatheredInputs.ValidateInputs(actionElement);
            }

            if (inputsAreValid)
            {
                Action(*this, winrt::make<implementation::AdaptiveActionEventArgs>(actionElement, gatheredInputs));
            }
            else
            {
                return;
            }
        }
        case ObjectModel::Uwp::ActionType::OpenUrl:
        case ObjectModel::Uwp::ActionType::Custom:
        default:
        {
            Action(*this,
                   winrt::make<implementation::AdaptiveActionEventArgs>(actionElement,
                                                                        winrt::make<implementation::AdaptiveInputs>()));
        }
        }
    }

    void RenderedAdaptiveCard::SendMediaClickedEvent(ObjectModel::Uwp::AdaptiveMedia const& mediaElement)
    {
        MediaClicked(*this, winrt::make<implementation::AdaptiveMediaEventArgs>(mediaElement));
    }

    void RenderedAdaptiveCard::SetFrameworkElement(winrt::Windows::UI::Xaml::FrameworkElement const& value)
    {
        m_frameworkElement = value;
    }

    void RenderedAdaptiveCard::SetOriginatingCard(ObjectModel::Uwp::AdaptiveCard const& value)
    {
        m_originatingCard = value;
    }

    void RenderedAdaptiveCard::SetOriginatingHostConfig(Rendering::Uwp::AdaptiveHostConfig const& value)
    {
        m_originatingHostConfig = value;
    }

    void RenderedAdaptiveCard::AddInlineShowCard(ObjectModel::Uwp::AdaptiveActionSet const& actionSet,
                                                 ObjectModel::Uwp::IAdaptiveShowCardAction const& showCardAction,
                                                 winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                                                 Rendering::Uwp::AdaptiveRenderArgs const& renderArgs)
    {
        AddInlineShowCardHelper(actionSet.InternalId(), showCardAction, showCardUIElement, renderArgs);
    }

    void RenderedAdaptiveCard::AddInlineShowCard(ObjectModel::Uwp::AdaptiveCard const& adaptiveCard,
                                                 ObjectModel::Uwp::IAdaptiveShowCardAction const& showCardAction,
                                                 winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                                                 Uwp::AdaptiveRenderArgs const& renderArgs)
    {
        AddInlineShowCardHelper(adaptiveCard.InternalId(), showCardAction, showCardUIElement, renderArgs);
    }

    void RenderedAdaptiveCard::AddInlineShowCardHelper(uint32_t actionSetId,
                                                       ObjectModel::Uwp::IAdaptiveShowCardAction const& showCardAction,
                                                       winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                                                       Uwp::AdaptiveRenderArgs const& renderArgs)
    {
        auto showCardInfo = std::make_shared<ShowCardInfo>();
        showCardInfo->actionSetId = actionSetId;
        showCardInfo->cardUIElement = showCardUIElement;

        m_showCards.emplace(std::make_pair(showCardAction.InternalId(), showCardInfo));

        // We also add the parent card relationship here
        LinkCardToParent(showCardAction.Card(), renderArgs);
    }

    void RenderedAdaptiveCard::AddOverflowButton(ObjectModel::Uwp::AdaptiveActionSet const& actionSet,
                                                 winrt::Windows::UI::Xaml::UIElement const& actionUIElement)
    {
        m_overflowButtons.emplace(std::make_pair(actionSet.InternalId(), actionUIElement));
    }

    void RenderedAdaptiveCard::AddOverflowButton(ObjectModel::Uwp::AdaptiveCard const& actionCard,
                                                 winrt::Windows::UI::Xaml::UIElement const& actionUIElement)
    {
        m_overflowButtons.emplace(std::make_pair(actionCard.InternalId(), actionUIElement));
    }

    void RenderedAdaptiveCard::AddInputValue(Uwp::IAdaptiveInputValue const& inputValue, Uwp::AdaptiveRenderArgs const& renderArgs)
    {
        m_inputs->AddInputValue(inputValue, renderArgs);
    }

    void RenderedAdaptiveCard::LinkActionToCard(ObjectModel::Uwp::IAdaptiveActionElement const& submitAction,
                                                Uwp::AdaptiveRenderArgs const& renderArgs)
    {
        return m_inputs->LinkSubmitActionToCard(submitAction, renderArgs);
    }

    void RenderedAdaptiveCard::LinkCardToParent(ObjectModel::Uwp::AdaptiveCard const& card, Uwp::AdaptiveRenderArgs const& renderArgs)
    {
        // We get the card internal id from the showcard action
        uint32_t cardId = card.InternalId();

        // Then we get the parent card internal id from the renderArgs
        uint32_t parentCardId = ::AdaptiveCards::InternalId().Hash();
        if (renderArgs)
        {
            if (auto parentCard = renderArgs.ParentCard())
            {
                parentCardId = parentCard.InternalId();
            }
        }

        m_inputs->LinkCardToParent(cardId, parentCardId);
    }

    Rendering::Uwp::IAdaptiveInputValue RenderedAdaptiveCard::GetInputValue(ObjectModel::Uwp::IAdaptiveInputElement const& inputElement)
    {
        return m_inputs->GetInputValue(inputElement);
    }
}
