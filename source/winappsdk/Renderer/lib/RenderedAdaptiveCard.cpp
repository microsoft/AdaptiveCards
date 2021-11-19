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
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::Rendering::WinUI3;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;
using namespace ABI::Windows::UI::Xaml::Controls::Primitives;

namespace winrt::AdaptiveCards::Rendering::WinUI3::implementation
{
    RenderedAdaptiveCard::RenderedAdaptiveCard() :
        RenderedAdaptiveCard(winrt::single_threaded_vector<ObjectModel::WinUI3::AdaptiveError>(),
                             winrt::single_threaded_vector<ObjectModel::WinUI3::AdaptiveWarning>())
    {
    }

    RenderedAdaptiveCard::RenderedAdaptiveCard(
        winrt::Windows::Foundation::Collections::IVector<ObjectModel::WinUI3::AdaptiveError> const& errors,
        winrt::Windows::Foundation::Collections::IVector<ObjectModel::WinUI3::AdaptiveWarning> const& warnings) :
        Errors{errors},
        Warnings{warnings}, m_inputs{winrt::make_self<implementation::AdaptiveInputs>()}, m_frameworkElement{nullptr}
    {
    }

    void RenderedAdaptiveCard::HandleInlineShowCardEvent(ObjectModel::WinUI3::IAdaptiveActionElement const& actionElement)
    {
        auto showCardAction = actionElement.as<ObjectModel::WinUI3::AdaptiveShowCardAction>();
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
                                     ObjectModel::WinUI3::IAdaptiveActionElement const& action)
    {
        auto toggleAction = action.as<ObjectModel::WinUI3::AdaptiveToggleVisibilityAction>();
        std::vector<rtxaml::Controls::Panel> parentPanels;
        for (auto&& currentTarget : toggleAction.TargetElements())
        {
            auto toggleId = currentTarget.ElementId();
            auto toggle = currentTarget.IsVisible();

            if (auto toggleObject = cardFrameworkElement.FindName(toggleId))
            {
                auto toggleElementAsUIElement = toggleObject.as<winrt::Windows::UI::Xaml::UIElement>();
                auto toggleElementAsFrameworkElement = toggleObject.as<winrt::Windows::UI::Xaml::FrameworkElement>();
                auto elementTagContent = toggleElementAsFrameworkElement.Tag().as<rtrender::ElementTagContent>();
                // TODO: once again, how to do it correctly????
                /* auto elementTagContent = peek_innards<rtrender::implementation::ElementTagContent>(toggleElementAsFrameworkElement);*/
                winrt::Windows::UI::Xaml::Visibility visibilityToSet = winrt::Windows::UI::Xaml::Visibility::Visible;

                if (toggle == ObjectModel::WinUI3::IsVisible::IsVisibleTrue)
                {
                    visibilityToSet = winrt::Windows::UI::Xaml::Visibility::Visible;
                }
                else if (toggle == ObjectModel::WinUI3::IsVisible::IsVisibleFalse)
                {
                    visibilityToSet = winrt::Windows::UI::Xaml::Visibility::Collapsed;
                }
                else if (toggle == ObjectModel::WinUI3::IsVisible::IsVisibleToggle)
                {
                    bool currentVisibility = elementTagContent.ExpectedVisibility();
                    /* THROW_IF_FAILED(elementTagContent->get_ExpectedVisibility(&currentVisibility));*/
                    visibilityToSet = currentVisibility ? winrt::Windows::UI::Xaml::Visibility::Collapsed :
                                                          winrt::Windows::UI::Xaml::Visibility::Visible;
                }

                toggleElementAsUIElement.Visibility(visibilityToSet);
                elementTagContent.ExpectedVisibility(visibilityToSet == winrt::Windows::UI::Xaml::Visibility::Visible);

                /*winrt::com_ptr<ABI::Windows::UI::Xaml::Controls::IPanel> parentPanel;
                THROW_IF_FAILED(elementTagContent->get_ParentPanel(parentPanel.put()));*/
                auto parentPanel = elementTagContent.ParentPanel();
                parentPanels.emplace_back(std::move(parentPanel));

                /* winrt::com_ptr<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement> cardElement;
                 THROW_IF_FAILED(elementTagContent->get_AdaptiveCardElement(cardElement.put()));*/
                auto cardElement = elementTagContent.CardElement();

                if (auto cardElementAsColumn = cardElement.try_as<ObjectModel::WinUI3::AdaptiveColumn>())
                {
                    /*winrt::com_ptr<ABI::Windows::UI::Xaml::Controls::IColumnDefinition> columnDefinition;
                    THROW_IF_FAILED(elementTagContent->get_ColumnDefinition(columnDefinition.put()));
                    ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleColumnWidth(cardElementAsColumn,
                                                                                       (visibilityToSet ==
                                                                                        winrt::Windows::UI::Xaml::Visibility::Visible),
                                                                                       to_winrt(columnDefinition.get()));*/
                    auto columnDefinition = elementTagContent.ColumnDefinition();
                    ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleColumnWidth(
                        cardElementAsColumn, (visibilityToSet == winrt::Windows::UI::Xaml::Visibility::Visible), columnDefinition);
                }
            }
        }

        for (auto&& parentPanel : parentPanels)
        {
            if (parentPanel)
            {
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetSeparatorVisibility(parentPanel);
            }
        }
    }

    void RenderedAdaptiveCard::SendActionEvent(ObjectModel::WinUI3::IAdaptiveActionElement const& actionElement)
    {
        auto actionType = actionElement.ActionType();
        switch (actionType)
        {
        case ObjectModel::WinUI3::ActionType::ToggleVisibility:
            return HandleToggleVisibilityClick(m_frameworkElement, actionElement);

        case ObjectModel::WinUI3::ActionType::ShowCard:
        {
            auto actionConfig = m_originatingHostConfig.Actions();
            auto showCardConfig = actionConfig.ShowCard();
            auto actionMode = showCardConfig.ActionMode();
            bool handleInlineShowCard = (actionMode == WinUI3::ActionMode::Inline);

            if (handleInlineShowCard)
            {
                // If the host is custom rendering ActionSets, they are responsible for showing and hiding the cards therein.
                // Check if the action being invoked is one we registered, otherwise we'll send the action to the host.
                auto showCardAction = actionElement.as<ObjectModel::WinUI3::AdaptiveShowCardAction>();
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
        case ObjectModel::WinUI3::ActionType::Submit:
        case ObjectModel::WinUI3::ActionType::Execute:
        {
            ObjectModel::WinUI3::AssociatedInputs associatedInputs;

            if (actionType == ObjectModel::WinUI3::ActionType::Submit)
            {
                associatedInputs = actionElement.as<ObjectModel::WinUI3::AdaptiveSubmitAction>().AssociatedInputs();
            }
            else
            {
                associatedInputs = actionElement.as<ObjectModel::WinUI3::AdaptiveExecuteAction>().AssociatedInputs();
            }

            WinUI3::AdaptiveInputs gatheredInputs;
            bool inputsAreValid;
            if (associatedInputs == ObjectModel::WinUI3::AssociatedInputs::None)
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
        case ObjectModel::WinUI3::ActionType::OpenUrl:
        case ObjectModel::WinUI3::ActionType::Custom:
        default:
        {
            Action(*this,
                   winrt::make<implementation::AdaptiveActionEventArgs>(actionElement,
                                                                        winrt::make<implementation::AdaptiveInputs>()));
        }
        }
    }

    void RenderedAdaptiveCard::SendMediaClickedEvent(ObjectModel::WinUI3::AdaptiveMedia const& mediaElement)
    {
        MediaClicked(*this, winrt::make<implementation::AdaptiveMediaEventArgs>(mediaElement));
    }

    void RenderedAdaptiveCard::SetFrameworkElement(winrt::Windows::UI::Xaml::FrameworkElement const& value)
    {
        m_frameworkElement = value;
    }

    void RenderedAdaptiveCard::SetOriginatingCard(ObjectModel::WinUI3::AdaptiveCard const& value)
    {
        m_originatingCard = value;
    }

    void RenderedAdaptiveCard::SetOriginatingHostConfig(Rendering::WinUI3::AdaptiveHostConfig const& value)
    {
        m_originatingHostConfig = value;
    }

    void RenderedAdaptiveCard::AddInlineShowCard(ObjectModel::WinUI3::AdaptiveActionSet const& actionSet,
                                                 ObjectModel::WinUI3::IAdaptiveShowCardAction const& showCardAction,
                                                 winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                                                 Rendering::WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        AddInlineShowCardHelper(actionSet.InternalId(), showCardAction, showCardUIElement, renderArgs);
    }

    void RenderedAdaptiveCard::AddInlineShowCard(ObjectModel::WinUI3::AdaptiveCard const& adaptiveCard,
                                                 ObjectModel::WinUI3::IAdaptiveShowCardAction const& showCardAction,
                                                 winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                                                 WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        AddInlineShowCardHelper(adaptiveCard.InternalId(), showCardAction, showCardUIElement, renderArgs);
    }

    void RenderedAdaptiveCard::AddInlineShowCardHelper(uint32_t actionSetId,
                                                       ObjectModel::WinUI3::IAdaptiveShowCardAction const& showCardAction,
                                                       winrt::Windows::UI::Xaml::UIElement const& showCardUIElement,
                                                       WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        auto showCardInfo = std::make_shared<ShowCardInfo>();
        showCardInfo->actionSetId = actionSetId;
        showCardInfo->cardUIElement = showCardUIElement;

        m_showCards.emplace(std::make_pair(showCardAction.InternalId(), showCardInfo));

        // We also add the parent card relationship here
        LinkCardToParent(showCardAction.Card(), renderArgs);
    }

    void RenderedAdaptiveCard::AddOverflowButton(ObjectModel::WinUI3::AdaptiveActionSet const& actionSet,
                                                 winrt::Windows::UI::Xaml::UIElement const& actionUIElement)
    {
        m_overflowButtons.emplace(std::make_pair(actionSet.InternalId(), actionUIElement));
    }

    void RenderedAdaptiveCard::AddOverflowButton(ObjectModel::WinUI3::AdaptiveCard const& actionCard,
                                                 winrt::Windows::UI::Xaml::UIElement const& actionUIElement)
    {
        m_overflowButtons.emplace(std::make_pair(actionCard.InternalId(), actionUIElement));
    }

    void RenderedAdaptiveCard::AddInputValue(WinUI3::IAdaptiveInputValue const& inputValue, WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        m_inputs->AddInputValue(inputValue, renderArgs);
    }

    void RenderedAdaptiveCard::LinkActionToCard(ObjectModel::WinUI3::IAdaptiveActionElement const& submitAction,
                                                WinUI3::AdaptiveRenderArgs const& renderArgs)
    {
        return m_inputs->LinkSubmitActionToCard(submitAction, renderArgs);
    }

    void RenderedAdaptiveCard::LinkCardToParent(ObjectModel::WinUI3::AdaptiveCard const& card, WinUI3::AdaptiveRenderArgs const& renderArgs)
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

    Rendering::WinUI3::IAdaptiveInputValue RenderedAdaptiveCard::GetInputValue(ObjectModel::WinUI3::IAdaptiveInputElement const& inputElement)
    {
        return m_inputs->GetInputValue(inputElement);
    }
}
