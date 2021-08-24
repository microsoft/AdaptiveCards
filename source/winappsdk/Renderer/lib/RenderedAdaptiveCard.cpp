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
        Warnings{warnings}
    {
        THROW_IF_FAILED(MakeAndInitialize<AdaptiveCards::Rendering::WinUI3::AdaptiveInputs>(&m_inputs));
    }

    HRESULT RenderedAdaptiveCard::HandleInlineShowCardEvent(_In_ IAdaptiveActionElement* actionElement)
    {
        ComPtr<IAdaptiveActionElement> localActionElement(actionElement);
        ComPtr<IAdaptiveShowCardAction> showCardAction;
        RETURN_IF_FAILED(localActionElement.As(&showCardAction));

        UINT32 showCardToToggle;
        RETURN_IF_FAILED(showCardAction->get_InternalId(&showCardToToggle));
        auto found = m_showCards.find(showCardToToggle);

        if (found != m_showCards.end())
        {
            std::shared_ptr<ShowCardInfo> showCardInfoToHandle = found->second;

            Visibility overflowButtonVisibility = Visibility_Collapsed;
            if (showCardInfoToHandle->overflowUIElement != nullptr)
            {
                RETURN_IF_FAILED(showCardInfoToHandle->overflowUIElement->get_Visibility(&overflowButtonVisibility));
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
                    RETURN_IF_FAILED(showCardInfoToHandle->buttonUIElement->put_Visibility(Visibility_Visible));

                    // Set the column width to 1* if we're using column definitions to show equal width buttons
                    if (columnDefinitions)
                    {
                        columnDefinitions.GetAt(showCardInfoToHandle->primaryButtonIndex).Width({1.0, winrt::Windows::UI::Xaml::GridUnitType::Star});
                    }

                    // Next get the flyout menu so we can collapse this action from the flyout and show the one we hid from the action bar
                    auto overflowButtonAsButtonWithFlyout = overflowButton.as<winrt::Windows::UI::Xaml::Controls::IButtonWithFlyout>();
                    auto flyoutBase = overflowButtonAsButtonWithFlyout.Flyout();
                    auto flyout = flyoutBase.as<winrt::Windows::UI::Xaml::Controls::MenuFlyout>();

                    for (auto&& flyout : flyout.Items())
                    {
                        flyout.Visibility(winrt::Windows::UI::Xaml::Visibility::Visible);
                    }

                    // Make the the action we're handling collapsed in the overflow menu. It is now shown in the button bar and don't want it to show here.
                    RETURN_IF_FAILED(showCardInfoToHandle->overflowUIElement->put_Visibility(Visibility_Collapsed));
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
                        RETURN_IF_FAILED(showCardUIElementCurrent->put_Visibility(Visibility_Collapsed));
                    }
                }
            }
        }
        return S_OK;
    }

    static HRESULT HandleToggleVisibilityClick(_In_ IFrameworkElement* cardFrameworkElement, _In_ IAdaptiveActionElement* action)
    {
        ComPtr<IAdaptiveActionElement> localAction(action);
        ComPtr<IAdaptiveToggleVisibilityAction> toggleAction;
        RETURN_IF_FAILED(localAction.As(&toggleAction));

        ComPtr<IVector<AdaptiveToggleVisibilityTarget*>> targets;
        RETURN_IF_FAILED(toggleAction->get_TargetElements(&targets));

        ComPtr<IIterable<AdaptiveToggleVisibilityTarget*>> targetsIterable;
        RETURN_IF_FAILED(targets.As<IIterable<AdaptiveToggleVisibilityTarget*>>(&targetsIterable));

        boolean hasCurrent;
        ComPtr<IIterator<AdaptiveToggleVisibilityTarget*>> targetIterator;
        HRESULT hr = targetsIterable->First(&targetIterator);
        RETURN_IF_FAILED(targetIterator->get_HasCurrent(&hasCurrent));

        std::unordered_set<IPanel*> parentPanels;
        while (SUCCEEDED(hr) && hasCurrent)
        {
            ComPtr<IAdaptiveToggleVisibilityTarget> currentTarget;
            RETURN_IF_FAILED(targetIterator->get_Current(&currentTarget));

            HString toggleId;
            RETURN_IF_FAILED(currentTarget->get_ElementId(toggleId.GetAddressOf()));

            ABI::AdaptiveCards::ObjectModel::WinUI3::IsVisible toggle;
            RETURN_IF_FAILED(currentTarget->get_IsVisible(&toggle));

            ComPtr<IInspectable> toggleElement;
            RETURN_IF_FAILED(cardFrameworkElement->FindName(toggleId.Get(), &toggleElement));

            if (toggleElement != nullptr)
            {
                ComPtr<IUIElement> toggleElementAsUIElement;
                RETURN_IF_FAILED(toggleElement.As(&toggleElementAsUIElement));

                ComPtr<IFrameworkElement> toggleElementAsFrameworkElement;
                RETURN_IF_FAILED(toggleElement.As(&toggleElementAsFrameworkElement));

                ComPtr<IInspectable> tag;
                RETURN_IF_FAILED(toggleElementAsFrameworkElement->get_Tag(&tag));

                ComPtr<IElementTagContent> elementTagContent;
                RETURN_IF_FAILED(tag.As(&elementTagContent));

                Visibility visibilityToSet = Visibility_Visible;
                if (toggle == ABI::AdaptiveCards::ObjectModel::WinUI3::IsVisible_IsVisibleTrue)
                {
                    visibilityToSet = Visibility_Visible;
                }
                else if (toggle == ABI::AdaptiveCards::ObjectModel::WinUI3::IsVisible_IsVisibleFalse)
                {
                    visibilityToSet = Visibility_Collapsed;
                }
                else if (toggle == ABI::AdaptiveCards::ObjectModel::WinUI3::IsVisible_IsVisibleToggle)
                {
                    boolean currentVisibility{};
                    RETURN_IF_FAILED(elementTagContent->get_ExpectedVisibility(&currentVisibility));
                    visibilityToSet = (currentVisibility) ? Visibility_Collapsed : Visibility_Visible;
                }

                RETURN_IF_FAILED(toggleElementAsUIElement->put_Visibility(visibilityToSet));
                RETURN_IF_FAILED(elementTagContent->set_ExpectedVisibility(visibilityToSet == Visibility_Visible));

                ComPtr<IPanel> parentPanel;
                RETURN_IF_FAILED(elementTagContent->get_ParentPanel(&parentPanel));
                parentPanels.insert(parentPanel.Get());

                ComPtr<IAdaptiveCardElement> cardElement;
                RETURN_IF_FAILED(elementTagContent->get_AdaptiveCardElement(&cardElement));

                // If the element we're toggling is a column, we'll need to change the width on the column definition
                ComPtr<IAdaptiveColumn> cardElementAsColumn;
                if (SUCCEEDED(cardElement.As(&cardElementAsColumn)))
                {
                    ComPtr<IColumnDefinition> columnDefinition;
                    RETURN_IF_FAILED(elementTagContent->get_ColumnDefinition(&columnDefinition));
                    RETURN_IF_FAILED(XamlHelpers::HandleColumnWidth(cardElementAsColumn.Get(),
                                                                    (visibilityToSet == Visibility_Visible),
                                                                    columnDefinition.Get()));
                }
            }

            hr = targetIterator->MoveNext(&hasCurrent);
        }

        for (auto parentPanel : parentPanels)
        {
            if (parentPanel)
            {
                XamlHelpers::SetSeparatorVisibility(parentPanel);
            }
        }

        return S_OK;
    }

    HRESULT RenderedAdaptiveCard::SendActionEvent(_In_ IAdaptiveActionElement* actionElement)
    {
        ABI::AdaptiveCards::ObjectModel::WinUI3::ActionType actionType;
        RETURN_IF_FAILED(actionElement->get_ActionType(&actionType));

        switch (actionType)
        {
        case ABI::AdaptiveCards::ObjectModel::WinUI3::ActionType_ToggleVisibility:
        {
            return HandleToggleVisibilityClick(m_frameworkElement.Get(), actionElement);
        }

        case ABI::AdaptiveCards::ObjectModel::WinUI3::ActionType_ShowCard:
        {
            ComPtr<IAdaptiveActionsConfig> actionConfig;
            RETURN_IF_FAILED(m_originatingHostConfig->get_Actions(&actionConfig));

            ComPtr<IAdaptiveShowCardActionConfig> showCardConfig;
            RETURN_IF_FAILED(actionConfig->get_ShowCard(&showCardConfig));

            ABI::AdaptiveCards::Rendering::WinUI3::ActionMode actionMode;
            RETURN_IF_FAILED(showCardConfig->get_ActionMode(&actionMode));

            bool handleInlineShowCard = (actionMode == ABI::AdaptiveCards::Rendering::WinUI3::ActionMode_Inline);

            if (handleInlineShowCard)
            {
                // If the host is custom rendering ActionSets, they are responsible for showing and hiding the cards therein.
                // Check if the action being invoked is one we registered, otherwise we'll send the action to the host.
                ComPtr<IAdaptiveActionElement> action(actionElement);
                ComPtr<IAdaptiveShowCardAction> showCardAction;
                RETURN_IF_FAILED(action.As(&showCardAction));

                UINT32 internalId;
                RETURN_IF_FAILED(showCardAction->get_InternalId(&internalId));

                auto found = m_showCards.find(internalId);
                handleInlineShowCard &= (found != m_showCards.end());
            }

            if (handleInlineShowCard)
            {
                return HandleInlineShowCardEvent(actionElement);
            }
            else
            {
                ComPtr<IAdaptiveActionEventArgs> eventArgs;
                RETURN_IF_FAILED(MakeRt<winrt::AdaptiveCards::Rendering::WinUI3::implementation::AdaptiveActionEventArgs>(
                    eventArgs, to_winrt(actionElement), nullptr));

                return m_actionEvents->InvokeAll(this, eventArgs.Get());
            }
        }
        case ABI::AdaptiveCards::ObjectModel::WinUI3::ActionType_Submit:
        case ABI::AdaptiveCards::ObjectModel::WinUI3::ActionType_Execute:
        {
            ComPtr<IAdaptiveActionElement> localActionElement(actionElement);
            ABI::AdaptiveCards::ObjectModel::WinUI3::AssociatedInputs associatedInputs;

            if (actionType == ABI::AdaptiveCards::ObjectModel::WinUI3::ActionType_Submit)
            {
                ComPtr<IAdaptiveSubmitAction> submitAction;
                RETURN_IF_FAILED(localActionElement.As(&submitAction));
                RETURN_IF_FAILED(submitAction->get_AssociatedInputs(&associatedInputs));
            }
            else
            {
                ComPtr<IAdaptiveExecuteAction> executeAction;
                RETURN_IF_FAILED(localActionElement.As(&executeAction));
                RETURN_IF_FAILED(executeAction->get_AssociatedInputs(&associatedInputs));
            }

            ComPtr<IAdaptiveInputs> gatheredInputs;
            boolean inputsAreValid;
            if (associatedInputs == ABI::AdaptiveCards::ObjectModel::WinUI3::AssociatedInputs::None)
            {
                // Create an empty inputs object
                RETURN_IF_FAILED(MakeAndInitialize<AdaptiveInputs>(&gatheredInputs));
                inputsAreValid = true;
            }
            else
            {
                // get the inputElements in Json form.
                RETURN_IF_FAILED(get_UserInputs(&gatheredInputs));
                RETURN_IF_FAILED(gatheredInputs->ValidateInputs(localActionElement.Get(), &inputsAreValid));
            }

            if (!inputsAreValid)
            {
                return S_OK;
            }
            else
            {
                ComPtr<IAdaptiveActionEventArgs> eventArgs;
                RETURN_IF_FAILED(MakeRt<winrt::AdaptiveCards::Rendering::WinUI3::implementation::AdaptiveActionEventArgs>(
                    eventArgs, to_winrt(actionElement), to_winrt(gatheredInputs)));
                return m_actionEvents->InvokeAll(this, eventArgs.Get());
            }
        }
        case ABI::AdaptiveCards::ObjectModel::WinUI3::ActionType_OpenUrl:
        case ABI::AdaptiveCards::ObjectModel::WinUI3::ActionType_Custom:
        default:
        {
            ComPtr<IAdaptiveActionEventArgs> eventArgs;

            // Create an empty inputs object
            ComPtr<IAdaptiveInputs> inputs;
            RETURN_IF_FAILED(MakeAndInitialize<AdaptiveInputs>(&inputs));

            RETURN_IF_FAILED(MakeRt<winrt::AdaptiveCards::Rendering::WinUI3::implementation::AdaptiveActionEventArgs>(
                eventArgs, to_winrt(actionElement), to_winrt(inputs)));
            return m_actionEvents->InvokeAll(this, eventArgs.Get());
        }
        }
    }

    HRESULT RenderedAdaptiveCard::SendMediaClickedEvent(_In_ IAdaptiveMedia* mediaElement)
    {
        ComPtr<IAdaptiveMediaEventArgs> eventArgs;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveMediaEventArgs>(&eventArgs, mediaElement));

        return m_mediaClickedEvents->InvokeAll(this, eventArgs.Get());
    }

    void RenderedAdaptiveCard::SetFrameworkElement(_In_ ABI::Windows::UI::Xaml::IFrameworkElement* value)
    {
        m_frameworkElement = value;
    }

    void RenderedAdaptiveCard::SetOriginatingCard(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* value)
    {
        m_originatingCard = value;
    }

    void RenderedAdaptiveCard::SetOriginatingHostConfig(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* value)
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
