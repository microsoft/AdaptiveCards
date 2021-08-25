// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveActionEventArgs.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveMediaEventArgs.h"
#include "RenderedAdaptiveCard.h"
#include "XamlBuilder.h"
#include "XamlHelpers.h"
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
        Warnings{warnings}, m_inputs{winrt::make<implementation::AdaptiveInputs>()}
    {
    }

    void RenderedAdaptiveCard::HandleInlineShowCardEvent(ObjectModel::WinUI3::IAdaptiveActionElement const& actionElement)
    {
        auto showCardAction = actionElement.as<ObjectModel::WinUI3::AdaptiveShowCardAction>();
        auto found = m_showCards.find(showCardAction.InternalId());

        if (found != m_showCards.end())
        {
            std::shared_ptr<ShowCardInfo> showCardInfoToHandle = found->second;

            Visibility overflowButtonVisibility = Visibility_Collapsed;
            if (showCardInfoToHandle->overflowUIElement)
            {
                THROW_IF_FAILED(showCardInfoToHandle->overflowUIElement->get_Visibility(&overflowButtonVisibility));
            }

            // Check if the action is being invoked from the overflow menu
            if (overflowButtonVisibility == Visibility_Visible)
            {
                // When a show card action is selected from the overflow menu, we need to move it from the overflow menu
                // to the action bar by swapping it with the last item currently there. In order to do this we make this
                // action non-visible in the flyout menu and visible in the action bar, and we make the last action
                // visible in the action bar visible in the flyout menu and non-visible in the action bar.

                auto overflowButtonPair = m_overflowButtons.find(showCardInfoToHandle->actionSetId);
                auto overflowButton = overflowButtonPair->second;
                auto buttonParent = overflowButton.as<winrt::Windows::UI::Xaml::FrameworkElement>().Parent();
                auto actionPanel = buttonParent.as<winrt::Windows::UI::Xaml::Controls::Panel>();
                auto actionButtons = actionPanel.Children();

                winrt::Windows::Foundation::Collections::IVector<winrt::Windows::UI::Xaml::Controls::ColumnDefinition> columnDefinitions;
                if (auto actionPanelAsGrid = buttonParent.try_as<winrt::Windows::UI::Xaml::Controls::Grid>())
                {
                    columnDefinitions = actionPanelAsGrid.ColumnDefinitions();
                }

                // Walk the buttons in the button bar. We're looking for the last visible action button (so we can hide
                // it now that it's visible on the overflow menu). This will be the second to last visible button in the
                // panel (the last being the overflow button itself)
                uint32_t currentButtonIndex = 0;
                uint32_t lastVisibleButtonIndex = 0;
                uint32_t penultimateVisibleButtonIndex = 0;
                winrt::Windows::UI::Xaml::UIElement lastVisibleButton{nullptr};
                winrt::Windows::UI::Xaml::UIElement penultimateVisibleButton{nullptr};
                for (auto&& action : actionButtons)
                {
                    if (action.Visibility() == winrt::Windows::UI::Xaml::Visibility::Visible)
                    {
                        penultimateVisibleButton = lastVisibleButton;
                        lastVisibleButton = action;

                        penultimateVisibleButtonIndex = lastVisibleButtonIndex;
                        lastVisibleButtonIndex = currentButtonIndex;
                    }

                    ++currentButtonIndex;
                }

                // If there isn't a visible button available to swap this show card with, there's nothing to do here.
                if (penultimateVisibleButton)
                {
                    penultimateVisibleButton.Visibility(winrt::Windows::UI::Xaml::Visibility::Collapsed);

                    // Set the column width to auto if we're using column definitions to allow the space allocated for this button to collapse
                    if (columnDefinitions)
                    {
                        columnDefinitions.GetAt(penultimateVisibleButtonIndex).Width({0, winrt::Windows::UI::Xaml::GridUnitType::Auto});
                    }

                    // Make the show card button visible
                    THROW_IF_FAILED(showCardInfoToHandle->buttonUIElement->put_Visibility(Visibility_Visible));

                    // Set the column width to 1* if we're using column definitions to show equal width buttons
                    if (columnDefinitions)
                    {
                        columnDefinitions.GetAt(showCardInfoToHandle->primaryButtonIndex).Width({1.0, winrt::Windows::UI::Xaml::GridUnitType::Star});
                    }

                    // Next get the flyout menu so we can collapse this action from the flyout and show the one we hid from the action bar
                    auto overflowButtonAsButtonWithFlyout =
                        overflowButton.as<winrt::Windows::UI::Xaml::Controls::IButtonWithFlyout>();
                    auto flyoutBase = overflowButtonAsButtonWithFlyout.Flyout();
                    auto flyout = flyoutBase.as<winrt::Windows::UI::Xaml::Controls::MenuFlyout>();

                    for (auto&& flyout : flyout.Items())
                    {
                        flyout.Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
                    }

                    // Make the the action we're handling collapsed in the overflow menu. It is now shown in the button bar and don't want it to show here.
                    THROW_IF_FAILED(showCardInfoToHandle->overflowUIElement->put_Visibility(Visibility_Collapsed));
                }
            }

            // Determine if the card is currently being shown
            ABI::Windows::UI::Xaml::Visibility currentVisibility;
            showCardInfoToHandle->cardUIElement->get_Visibility(&currentVisibility);

            if (currentVisibility == Visibility_Visible)
            {
                // If it was shown, hide it
                showCardInfoToHandle->cardUIElement->put_Visibility(Visibility_Collapsed);
            }
            else
            {
                // If it was hidden, show it, and hide all other cards in this action set
                showCardInfoToHandle->cardUIElement->put_Visibility(Visibility_Visible);

                for (auto& showCardEntry : m_showCards)
                {
                    const UINT32 showCardId = showCardEntry.first;
                    auto currentShowCardInfo = showCardEntry.second;
                    if ((showCardInfoToHandle->actionSetId == currentShowCardInfo->actionSetId) && (showCardToToggle != showCardId))
                    {
                        ComPtr<IUIElement> showCardUIElementCurrent = currentShowCardInfo->cardUIElement;
                        THROW_IF_FAILED(showCardUIElementCurrent->put_Visibility(Visibility_Collapsed));
                    }
                }
            }
        }
    }

    void HandleToggleVisibilityClick(winrt::Windows::UI::Xaml::FrameworkElement const& cardFrameworkElement,
                                     ObjectModel::WinUI3::IAdaptiveActionElement const& action)
    {
        auto toggleAction = action.as<ObjectModel::WinUI3::AdaptiveToggleVisibilityAction>();
        std::vector<winrt::com_ptr<ABI::Windows::UI::Xaml::Controls::IPanel>> parentPanels;
        for (auto&& currentTarget : toggleAction.TargetElements())
        {
            auto toggleId = currentTarget.ElementId();
            auto toggle = currentTarget.IsVisible();

            if (auto toggleObject = cardFrameworkElement.FindName(toggleId))
            {
                auto toggleElementAsUIElement = toggleObject.as<winrt::Windows::UI::Xaml::UIElement>();
                auto toggleElementAsFrameworkElement = toggleObject.as<winrt::Windows::UI::Xaml::FrameworkElement>();
                auto elementTagContent = toggleElementAsFrameworkElement.Tag().as<::AdaptiveCards::Rendering::WinUI3::IElementTagContent>();
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
                    boolean currentVisibility;
                    THROW_IF_FAILED(elementTagContent->get_ExpectedVisibility(&currentVisibility));
                    visibilityToSet = currentVisibility ? winrt::Windows::UI::Xaml::Visibility::Collapsed :
                                                          winrt::Windows::UI::Xaml::Visibility::Visible;
                }

                toggleElementAsUIElement.Visibility(visibilityToSet);
                elementTagContent->set_ExpectedVisibility(visibilityToSet == winrt::Windows::UI::Xaml::Visibility::Visible);

                winrt::com_ptr<ABI::Windows::UI::Xaml::Controls::IPanel> parentPanel;
                THROW_IF_FAILED(elementTagContent->get_ParentPanel(parentPanel.put()));
                parentPanels.emplace_back(std::move(parentPanel));

                winrt::com_ptr<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCardElement> cardElement;
                THROW_IF_FAILED(elementTagContent->get_AdaptiveCardElement(cardElement.put()));

                if (auto cardElementAsColumn = cardElement.try_as<ObjectModel::WinUI3::AdaptiveColumn>())
                {
                    winrt::com_ptr<ABI::Windows::UI::Xaml::Controls::IColumnDefinition> columnDefinition;
                    THROW_IF_FAILED(elementTagContent->get_ColumnDefinition(columnDefinition.put()));
                    THROW_IF_FAILED(::AdaptiveCards::Rendering::WinUI3::XamlHelpers::HandleColumnWidth(
                        cardElementAsColumn,
                        (visibilityToSet == winrt::Windows::UI::Xaml::Visibility::Visible),
                        columnDefinition.get()));
                }
            }
        }

        for (auto&& parentPanel : parentPanels)
        {
            if (parentPanel)
            {
                ::AdaptiveCards::Rendering::WinUI3::XamlHelpers::SetSeparatorVisibility(parentPanel.get());
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

    HRESULT RenderedAdaptiveCard::AddInlineShowCard(_In_ IAdaptiveActionSet* actionSet,
                                                    _In_ IAdaptiveShowCardAction* showCardAction,
                                                    _In_ ABI::Windows::UI::Xaml::IUIElement* actionButtonUIElement,
                                                    _In_ ABI::Windows::UI::Xaml::IUIElement* actionOverflowUIElement,
                                                    _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                                    UINT32 primaryButtonIndex,
                                                    ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs)
    try
    {
        UINT32 actionSetId;
        RETURN_IF_FAILED(actionSet->get_InternalId(&actionSetId));

        RETURN_IF_FAILED(AddInlineShowCardHelper(
            actionSetId, showCardAction, actionButtonUIElement, actionOverflowUIElement, showCardUIElement, primaryButtonIndex, renderArgs));

        return S_OK;
    }
    CATCH_RETURN();

    HRESULT RenderedAdaptiveCard::AddInlineShowCard(ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* adaptiveCard,
                                                    ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveShowCardAction* showCardAction,
                                                    _In_ ABI::Windows::UI::Xaml::IUIElement* actionButtonUIElement,
                                                    _In_ ABI::Windows::UI::Xaml::IUIElement* actionOverflowUIElement,
                                                    _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                                    UINT32 primaryButtonIndex,
                                                    _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs)
    try
    {
        UINT32 actionSetId;
        RETURN_IF_FAILED(adaptiveCard->get_InternalId(&actionSetId));

        RETURN_IF_FAILED(AddInlineShowCardHelper(
            actionSetId, showCardAction, actionButtonUIElement, actionOverflowUIElement, showCardUIElement, primaryButtonIndex, renderArgs));

        return S_OK;
    }
    CATCH_RETURN();

    HRESULT RenderedAdaptiveCard::AddInlineShowCardHelper(UINT32 actionSetId,
                                                          _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveShowCardAction* showCardAction,
                                                          _In_ ABI::Windows::UI::Xaml::IUIElement* actionButtonUIElement,
                                                          _In_ ABI::Windows::UI::Xaml::IUIElement* actionOverflowUIElement,
                                                          _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                                          UINT32 primaryButtonIndex,
                                                          _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs)
    try
    {
        UINT32 showCardActionId;
        RETURN_IF_FAILED(showCardAction->get_InternalId(&showCardActionId));

        std::shared_ptr<ShowCardInfo> showCardInfo = std::make_shared<ShowCardInfo>();
        showCardInfo->actionSetId = actionSetId;
        showCardInfo->buttonUIElement = actionButtonUIElement;
        showCardInfo->overflowUIElement = actionOverflowUIElement;
        showCardInfo->cardUIElement = showCardUIElement;
        showCardInfo->primaryButtonIndex = primaryButtonIndex;

        m_showCards.emplace(std::make_pair(showCardActionId, showCardInfo));

        // We also add the parent card relationship here
        ComPtr<IAdaptiveShowCardAction> localShowCardAction(showCardAction);
        ComPtr<IAdaptiveCard> card;
        RETURN_IF_FAILED(localShowCardAction->get_Card(card.GetAddressOf()));

        RETURN_IF_FAILED(LinkCardToParent(card.Get(), renderArgs));

        return S_OK;
    }
    CATCH_RETURN();

    HRESULT RenderedAdaptiveCard::AddOverflowButton(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionSet* actionSet,
                                                    _In_ ABI::Windows::UI::Xaml::IUIElement* actionUIElement)
    try
    {
        UINT32 actionSetId;
        RETURN_IF_FAILED(actionSet->get_InternalId(&actionSetId));

        m_overflowButtons.emplace(std::make_pair(actionSetId, actionUIElement));

        return S_OK;
    }
    CATCH_RETURN();

    HRESULT RenderedAdaptiveCard::AddOverflowButton(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* actionCard,
                                                    _In_ ABI::Windows::UI::Xaml::IUIElement* actionUIElement)
    try
    {
        UINT32 adaptiveCardId;
        RETURN_IF_FAILED(actionCard->get_InternalId(&adaptiveCardId));

        m_overflowButtons.emplace(std::make_pair(adaptiveCardId, actionUIElement));

        return S_OK;
    }
    CATCH_RETURN();

    HRESULT RenderedAdaptiveCard::AddInputValue(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputValue* inputItem,
                                                _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs)
    {
        return m_inputs->AddInputValue(inputItem, renderArgs);
    }

    HRESULT RenderedAdaptiveCard::LinkActionToCard(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* action,
                                                   _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs)
    {
        return m_inputs->LinkSubmitActionToCard(action, renderArgs);
    }

    HRESULT RenderedAdaptiveCard::LinkCardToParent(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* card,
                                                   _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs)
    {
        // We get the card internal id from the showcard action
        UINT32 cardId;
        RETURN_IF_FAILED(card->get_InternalId(&cardId));

        // Then we get the parent card internal id from the renderArgs
        ComPtr<IAdaptiveRenderArgs> localRenderArgs(renderArgs);
        UINT32 parentCardId = InternalId().Hash();
        if (renderArgs)
        {
            ComPtr<IAdaptiveCard> parentCard;
            RETURN_IF_FAILED(localRenderArgs->get_ParentCard(parentCard.GetAddressOf()));

            if (parentCard)
            {
                parentCard->get_InternalId(&parentCardId);
            }
        }

        return m_inputs->LinkCardToParent(cardId, parentCardId);
    }

    HRESULT RenderedAdaptiveCard::GetInputValue(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInputElement* inputElement,
                                                _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputValue** inputValue)
    {
        return m_inputs->GetInputValue(inputElement, inputValue);
    }

}
