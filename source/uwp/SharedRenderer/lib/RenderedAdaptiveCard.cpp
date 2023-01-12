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

namespace winrt::AdaptiveCards::Rendering::Xaml_Rendering::implementation
{
    RenderedAdaptiveCard::RenderedAdaptiveCard() :
        RenderedAdaptiveCard(winrt::single_threaded_vector<winrt::AdaptiveError>(),
                             winrt::single_threaded_vector<winrt::AdaptiveWarning>())
    {
    }

    RenderedAdaptiveCard::RenderedAdaptiveCard(winrt::IVector<winrt::AdaptiveError> const& errors, winrt::IVector<winrt::AdaptiveWarning> const& warnings) :
        Errors{errors}, Warnings{warnings}, m_inputs{winrt::make_self<implementation::AdaptiveInputs>()}, m_frameworkElement{nullptr}
    {
    }

    void RenderedAdaptiveCard::HandleInlineShowCardEvent(winrt::IAdaptiveActionElement const& actionElement)
    {
        auto showCardAction = actionElement.as<winrt::AdaptiveShowCardAction>();
        auto showCardToToggle = showCardAction.InternalId();
        auto found = m_showCards.find(showCardToToggle);

        if (found != m_showCards.end())
        {
            std::shared_ptr<ShowCardInfo> showCardInfoToHandle = found->second;

            // Determine if the card is currently being shown
            winrt::Visibility currentVisibility = showCardInfoToHandle->cardUIElement.Visibility();

            if (currentVisibility == winrt::Visibility::Visible)
            {
                // If it was shown, hide it
                showCardInfoToHandle->cardUIElement.Visibility(winrt::Visibility::Collapsed);
            }
            else
            {
                // If it was hidden, show it, and hide all other cards in this action set
                showCardInfoToHandle->cardUIElement.Visibility(winrt::Visibility::Visible);

                for (auto& showCardEntry : m_showCards)
                {
                    const UINT32 showCardId = showCardEntry.first;
                    auto currentShowCardInfo = showCardEntry.second;
                    if ((showCardInfoToHandle->actionSetId == currentShowCardInfo->actionSetId) && (showCardToToggle != showCardId))
                    {
                        currentShowCardInfo->cardUIElement.Visibility(winrt::Visibility::Collapsed);
                    }
                }
            }
        }
    }

    void HandleToggleVisibilityClick(winrt::FrameworkElement const& cardFrameworkElement, winrt::IAdaptiveActionElement const& action)
    {
        auto toggleAction = action.as<winrt::AdaptiveToggleVisibilityAction>();
        std::vector<winrt::Panel> parentPanels;
        for (auto&& currentTarget : toggleAction.TargetElements())
        {
            auto toggleId = currentTarget.ElementId();
            auto toggle = currentTarget.IsVisible();

            if (auto toggleObject = cardFrameworkElement.FindName(toggleId))
            {
                auto toggleElementAsUIElement = toggleObject.as<winrt::UIElement>();
                auto toggleElementAsFrameworkElement = toggleObject.as<winrt::FrameworkElement>();
                auto elementTagContent = toggleElementAsFrameworkElement.Tag().as<winrt::ElementTagContent>();

                winrt::Visibility visibilityToSet = winrt::Visibility::Visible;
                if (toggle == winrt::IsVisible::IsVisibleTrue)
                {
                    visibilityToSet = winrt::Visibility::Visible;
                }
                else if (toggle == winrt::IsVisible::IsVisibleFalse)
                {
                    visibilityToSet = winrt::Visibility::Collapsed;
                }
                else if (toggle == winrt::IsVisible::IsVisibleToggle)
                {
                    bool currentVisibility = elementTagContent.ExpectedVisibility();
                    visibilityToSet = currentVisibility ? winrt::Visibility::Collapsed : winrt::Visibility::Visible;
                }

                toggleElementAsUIElement.Visibility(visibilityToSet);
                elementTagContent.ExpectedVisibility(visibilityToSet == winrt::Visibility::Visible);

                auto parentPanel = elementTagContent.ParentPanel();
                parentPanels.emplace_back(parentPanel);

                auto cardElement = elementTagContent.CardElement();

                if (auto cardElementAsColumn = cardElement.try_as<winrt::AdaptiveColumn>())
                {
                    auto columnDefinition = elementTagContent.ColumnDefinition();
                    XamlHelpers::HandleColumnWidth(cardElementAsColumn, (visibilityToSet == winrt::Visibility::Visible), columnDefinition);
                }
            }
        }

        for (auto&& parentPanel : parentPanels)
        {
            if (parentPanel)
            {
                XamlHelpers::SetSeparatorVisibility(parentPanel);
            }
        }
    }

    void RenderedAdaptiveCard::SendActionEvent(winrt::IAdaptiveActionElement const& actionElement)
    {
        auto actionType = actionElement.ActionType();

        switch (actionType)
        {
        case winrt::ActionType::ToggleVisibility:
            return HandleToggleVisibilityClick(m_frameworkElement, actionElement);

        case winrt::ActionType::ShowCard:
        {
            auto actionConfig = m_originatingHostConfig.Actions();
            auto showCardConfig = actionConfig.ShowCard();
            auto actionMode = showCardConfig.ActionMode();
            bool handleInlineShowCard = (actionMode == winrt::AdaptiveCards::Rendering::Xaml_Rendering::ActionMode::Inline);

            if (handleInlineShowCard)
            {
                // If the host is custom rendering ActionSets, they are responsible for showing and hiding the cards therein.
                // Check if the action being invoked is one we registered, otherwise we'll send the action to the host.
                auto showCardAction = actionElement.as<winrt::AdaptiveShowCardAction>();
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
        case winrt::ActionType::Submit:
        case winrt::ActionType::Execute:
        {
            winrt::AssociatedInputs associatedInputs;

            if (actionType == winrt::ActionType::Submit)
            {
                associatedInputs = actionElement.as<winrt::AdaptiveSubmitAction>().AssociatedInputs();
            }
            else
            {
                associatedInputs = actionElement.as<winrt::AdaptiveExecuteAction>().AssociatedInputs();
            }

            winrt::AdaptiveInputs gatheredInputs;
            bool inputsAreValid;
            if (associatedInputs == winrt::AssociatedInputs::None)
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
                return;
            }
            else
            {
                return;
            }
        }
        case winrt::ActionType::OpenUrl:
        case winrt::ActionType::Custom:
        default:
        {
            Action(*this,
                   winrt::make<implementation::AdaptiveActionEventArgs>(actionElement,
                                                                        winrt::make<implementation::AdaptiveInputs>()));
        }
        }
    }

    void RenderedAdaptiveCard::SendMediaClickedEvent(winrt::AdaptiveMedia const& mediaElement)
    {
        MediaClicked(*this, winrt::make<implementation::AdaptiveMediaEventArgs>(mediaElement));
    }

    void RenderedAdaptiveCard::SetFrameworkElement(winrt::FrameworkElement const& value)
    {
        m_frameworkElement = value;
    }

    void RenderedAdaptiveCard::SetOriginatingCard(winrt::AdaptiveCard const& value)
    {
        m_originatingCard = value;
    }

    void RenderedAdaptiveCard::SetOriginatingHostConfig(winrt::AdaptiveHostConfig const& value)
    {
        m_originatingHostConfig = value;
    }

    void RenderedAdaptiveCard::AddInlineShowCard(winrt::AdaptiveActionSet const& actionSet,
                                                 winrt::IAdaptiveShowCardAction const& showCardAction,
                                                 winrt::UIElement const& showCardUIElement,
                                                 winrt::AdaptiveRenderArgs const& renderArgs)
    {
        AddInlineShowCardHelper(actionSet.InternalId(), showCardAction, showCardUIElement, renderArgs);
    }

    void RenderedAdaptiveCard::AddInlineShowCard(winrt::AdaptiveCard const& adaptiveCard,
                                                 winrt::IAdaptiveShowCardAction const& showCardAction,
                                                 winrt::UIElement const& showCardUIElement,
                                                 winrt::AdaptiveRenderArgs const& renderArgs)
    {
        AddInlineShowCardHelper(adaptiveCard.InternalId(), showCardAction, showCardUIElement, renderArgs);
    }

    void RenderedAdaptiveCard::AddInlineShowCardHelper(uint32_t actionSetId,
                                                       winrt::IAdaptiveShowCardAction const& showCardAction,
                                                       winrt::UIElement const& showCardUIElement,
                                                       winrt::AdaptiveRenderArgs const& renderArgs)
    {
        auto showCardInfo = std::make_shared<ShowCardInfo>();
        showCardInfo->actionSetId = actionSetId;
        showCardInfo->cardUIElement = showCardUIElement;

        m_showCards.emplace(std::make_pair(showCardAction.InternalId(), showCardInfo));

        // We also add the parent card relationship here
        LinkCardToParent(showCardAction.Card(), renderArgs);
    }

    void RenderedAdaptiveCard::AddOverflowButton(winrt::AdaptiveActionSet const& actionSet, winrt::UIElement const& actionUIElement)
    {
        m_overflowButtons.emplace(std::make_pair(actionSet.InternalId(), actionUIElement));
    }

    void RenderedAdaptiveCard::AddOverflowButton(winrt::AdaptiveCard const& actionCard, winrt::UIElement const& actionUIElement)
    {
        m_overflowButtons.emplace(std::make_pair(actionCard.InternalId(), actionUIElement));
    }

    void RenderedAdaptiveCard::AddInputValue(winrt::IAdaptiveInputValue const& inputValue, winrt::AdaptiveRenderArgs const& renderArgs)
    {
        m_inputs->AddInputValue(inputValue, renderArgs);
    }

    void RenderedAdaptiveCard::LinkActionToCard(winrt::IAdaptiveActionElement const& submitAction,
                                                winrt::AdaptiveRenderArgs const& renderArgs)
    {
        return m_inputs->LinkSubmitActionToCard(submitAction, renderArgs);
    }

    void RenderedAdaptiveCard::LinkCardToParent(winrt::AdaptiveCard const& card, winrt::AdaptiveRenderArgs const& renderArgs)
    {
        // We get the card internal id from the showcard action
        uint32_t cardId = card.InternalId();

        // Then we get the parent card internal id from the renderArgs
        uint32_t parentCardId = ::AdaptiveCards::InternalId::Invalid;
        if (renderArgs)
        {
            if (auto parentCard = renderArgs.ParentCard())
            {
                parentCardId = parentCard.InternalId();
            }
        }

        m_inputs->LinkCardToParent(cardId, parentCardId);
    }

    winrt::IAdaptiveInputValue RenderedAdaptiveCard::GetInputValue(winrt::IAdaptiveInputElement const& inputElement)
    {
        return m_inputs->GetInputValue(inputElement);
    }
}
