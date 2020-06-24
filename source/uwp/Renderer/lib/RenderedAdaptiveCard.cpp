// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveActionEventArgs.h"
#include "AdaptiveActionSet.h"
#include "AdaptiveCard.h"
#include "AdaptiveError.h"
#include "AdaptiveHostConfig.h"
#include "AdaptiveMediaEventArgs.h"
#include "AdaptiveShowCardAction.h"
#include "RenderedAdaptiveCard.h"
#include "XamlBuilder.h"
#include "XamlHelpers.h"
#include "ElementTagContent.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    RenderedAdaptiveCard::RenderedAdaptiveCard() {}

    HRESULT RenderedAdaptiveCard::RuntimeClassInitialize()
    {
        RETURN_IF_FAILED(
            RenderedAdaptiveCard::RuntimeClassInitialize(Make<Vector<ABI::AdaptiveNamespace::AdaptiveError*>>().Get(),
                                                         Make<Vector<ABI::AdaptiveNamespace::AdaptiveWarning*>>().Get()));
        return S_OK;
    }

    HRESULT RenderedAdaptiveCard::RuntimeClassInitialize(
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveError*>* errors,
        _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* warnings)
    {
        m_errors = errors;
        m_warnings = warnings;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveNamespace::AdaptiveInputs>(&m_inputs));
        m_actionEvents = std::make_shared<ActionEventSource>();
        m_mediaClickedEvents = std::make_shared<MediaEventSource>();
        return S_OK;
    }

    HRESULT RenderedAdaptiveCard::get_OriginatingCard(_COM_Outptr_ IAdaptiveCard** value)
    {
        return m_originatingCard.CopyTo(value);
    }

    HRESULT RenderedAdaptiveCard::get_OriginatingHostConfig(_COM_Outptr_ IAdaptiveHostConfig** value)
    {
        return m_originatingHostConfig.CopyTo(value);
    }

    HRESULT RenderedAdaptiveCard::get_FrameworkElement(_COM_Outptr_ IFrameworkElement** value)
    {
        return m_frameworkElement.CopyTo(value);
    }

    HRESULT RenderedAdaptiveCard::get_UserInputs(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputs** value)
    {
        return m_inputs.CopyTo(value);
    }

    HRESULT RenderedAdaptiveCard::add_Action(
        _In_ ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveNamespace::RenderedAdaptiveCard*, ABI::AdaptiveNamespace::AdaptiveActionEventArgs*>* handler,
        _Out_ EventRegistrationToken* token)
    {
        return m_actionEvents->Add(handler, token);
    }

    HRESULT RenderedAdaptiveCard::remove_Action(EventRegistrationToken token) { return m_actionEvents->Remove(token); }

    HRESULT RenderedAdaptiveCard::add_MediaClicked(
        _In_ ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveNamespace::RenderedAdaptiveCard*, ABI::AdaptiveNamespace::AdaptiveMediaEventArgs*>* handler,
        _Out_ EventRegistrationToken* token)
    {
        return m_mediaClickedEvents->Add(handler, token);
    }

    HRESULT RenderedAdaptiveCard::remove_MediaClicked(EventRegistrationToken token)
    {
        return m_mediaClickedEvents->Remove(token);
    }

    HRESULT RenderedAdaptiveCard::get_Errors(
        _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveError*>** value)
    {
        return m_errors.CopyTo(value);
    }

    HRESULT RenderedAdaptiveCard::get_Warnings(
        _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>** value)
    {
        return m_warnings.CopyTo(value);
    }

    HRESULT RenderedAdaptiveCard::HandleInlineShowCardEvent(_In_ IAdaptiveActionElement* actionElement)
    {
        ComPtr<IAdaptiveActionElement> localActionElement(actionElement);
        ComPtr<IAdaptiveShowCardAction> showCardAction;
        RETURN_IF_FAILED(localActionElement.As(&showCardAction));

        ComPtr<AdaptiveNamespace::AdaptiveShowCardAction> showCardImpl =
            PeekInnards<AdaptiveNamespace::AdaptiveShowCardAction>(showCardAction);

        // Find the show card that needs to be toggled
        InternalId showCardToToggle = showCardImpl->GetInternalId();
        auto found = m_showCards.find(showCardToToggle);

        if (found != m_showCards.end())
        {
            // The key (showCardEntry.first) is the show card id and the value (showCardEntry.second) is a pair
            // made up of the actionSetId and the UIElement for the card
            InternalId actionSetToToggle = found->second.first;
            ComPtr<IUIElement> showCardUIElement = found->second.second;

            // Determine if the card is currently being shown
            ABI::Windows::UI::Xaml::Visibility currentVisibility;
            showCardUIElement->get_Visibility(&currentVisibility);

            if (currentVisibility == Visibility_Visible)
            {
                // If it was shown, hide it
                showCardUIElement->put_Visibility(Visibility_Collapsed);
            }
            else
            {
                // If it was hidden, show it, and hide all other cards in this action set
                showCardUIElement->put_Visibility(Visibility_Visible);

                for (auto& showCardEntry : m_showCards)
                {
                    const InternalId showCardId = showCardEntry.first;
                    const InternalId actionSetId = showCardEntry.second.first;
                    if ((actionSetToToggle == actionSetId) && (showCardToToggle != showCardId))
                    {
                        ComPtr<IUIElement> showCardUIElementCurrent = showCardEntry.second.second;
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

            ABI::AdaptiveNamespace::IsVisible toggle;
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
                if (toggle == ABI::AdaptiveNamespace::IsVisible_IsVisibleTrue)
                {
                    visibilityToSet = Visibility_Visible;
                }
                else if (toggle == ABI::AdaptiveNamespace::IsVisible_IsVisibleFalse)
                {
                    visibilityToSet = Visibility_Collapsed;
                }
                else if (toggle == ABI::AdaptiveNamespace::IsVisible_IsVisibleToggle)
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
        // get the inputElements in Json form.
        ComPtr<IAdaptiveInputs> gatheredInputs;
        RETURN_IF_FAILED(get_UserInputs(&gatheredInputs));

        ComPtr<IAdaptiveActionEventArgs> eventArgs;
        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveActionEventArgs>(&eventArgs, actionElement, gatheredInputs.Get()));

        ABI::AdaptiveCards::Rendering::Uwp::ActionType actionType;
        RETURN_IF_FAILED(actionElement->get_ActionType(&actionType));

        switch (actionType)
        {
        case ABI::AdaptiveCards::Rendering::Uwp::ActionType_ToggleVisibility:
        {
            return HandleToggleVisibilityClick(m_frameworkElement.Get(), actionElement);
        }

        case ABI::AdaptiveCards::Rendering::Uwp::ActionType_ShowCard:
        {
            ComPtr<IAdaptiveActionsConfig> actionConfig;
            RETURN_IF_FAILED(m_originatingHostConfig->get_Actions(&actionConfig));

            ComPtr<IAdaptiveShowCardActionConfig> showCardConfig;
            RETURN_IF_FAILED(actionConfig->get_ShowCard(&showCardConfig));

            ABI::AdaptiveCards::Rendering::Uwp::ActionMode actionMode;
            RETURN_IF_FAILED(showCardConfig->get_ActionMode(&actionMode));

            if (actionMode == ABI::AdaptiveCards::Rendering::Uwp::ActionMode_Inline)
            {
                return HandleInlineShowCardEvent(actionElement);
            }
            // else fallthrough
        }
        case ABI::AdaptiveCards::Rendering::Uwp::ActionType_Submit:
        {
            ComPtr<IAdaptiveActionElement> localActionElement(actionElement);
            ComPtr<IAdaptiveSubmitAction> submitAction;
            RETURN_IF_FAILED(localActionElement.As(&submitAction));

            boolean inputsAreValid;
            RETURN_IF_FAILED(gatheredInputs->ValidateInputs(submitAction.Get(), &inputsAreValid));

            if (!inputsAreValid)
            {
                return S_OK;
            }
        }
        case ABI::AdaptiveCards::Rendering::Uwp::ActionType_OpenUrl:
        case ABI::AdaptiveCards::Rendering::Uwp::ActionType_Custom:
        default:
        {
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

    void RenderedAdaptiveCard::SetOriginatingCard(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* value)
    {
        m_originatingCard = value;
    }

    void RenderedAdaptiveCard::SetOriginatingHostConfig(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* value)
    {
        m_originatingHostConfig = value;
    }

    HRESULT RenderedAdaptiveCard::AddInlineShowCard(_In_ IAdaptiveActionSet* actionSet,
                                                    _In_ IAdaptiveShowCardAction* showCardAction,
                                                    _In_ ABI::Windows::UI::Xaml::IUIElement* showCardFrameworkElement,
                                                    ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs)
    try
    {
        InternalId actionSetId;
        ComPtr<AdaptiveNamespace::AdaptiveActionSet> actionSetImpl = PeekInnards<AdaptiveNamespace::AdaptiveActionSet>(actionSet);
        actionSetId = actionSetImpl->GetInternalId();

        RETURN_IF_FAILED(AddInlineShowCardHelper(actionSetId, showCardAction, showCardFrameworkElement, renderArgs));

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT RenderedAdaptiveCard::AddInlineShowCard(ABI::AdaptiveNamespace::IAdaptiveCard* adaptiveCard,
                                                    ABI::AdaptiveNamespace::IAdaptiveShowCardAction* showCardAction,
                                                    ABI::Windows::UI::Xaml::IUIElement* showCardFrameworkElement,
                                                    ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs)
    try
    {
        InternalId actionSetId;
        ComPtr<AdaptiveNamespace::AdaptiveCard> adaptiveCardImpl = PeekInnards<AdaptiveNamespace::AdaptiveCard>(adaptiveCard);
        actionSetId = adaptiveCardImpl->GetInternalId();

        RETURN_IF_FAILED(AddInlineShowCardHelper(actionSetId, showCardAction, showCardFrameworkElement, renderArgs));

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT RenderedAdaptiveCard::AddInlineShowCardHelper(AdaptiveCards::InternalId& actionSetId,
                                                          ABI::AdaptiveNamespace::IAdaptiveShowCardAction* showCardAction,
                                                          ABI::Windows::UI::Xaml::IUIElement* showCardFrameworkElement,
                                                          ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs)
    try
    {
        ComPtr<AdaptiveNamespace::AdaptiveShowCardAction> showCardImpl =
            PeekInnards<AdaptiveNamespace::AdaptiveShowCardAction>(showCardAction);
        InternalId showCardActionId = showCardImpl->GetInternalId();

        m_showCards.emplace(std::make_pair(showCardActionId, std::make_pair(actionSetId, showCardFrameworkElement)));

        // We also add the parent card relationship here
        ComPtr<IAdaptiveShowCardAction> localShowCardAction(showCardAction);
        ComPtr<IAdaptiveCard> card;
        RETURN_IF_FAILED(localShowCardAction->get_Card(card.GetAddressOf()));

        RETURN_IF_FAILED(LinkCardToParent(card.Get(), renderArgs));

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT RenderedAdaptiveCard::AddInputValue(_In_ IAdaptiveInputValue* inputItem, _In_ IAdaptiveRenderArgs* renderArgs)
    {
        return m_inputs->AddInputValue(inputItem, renderArgs);
    }

    HRESULT RenderedAdaptiveCard::LinkSubmitActionToCard(_In_ ABI::AdaptiveNamespace::IAdaptiveSubmitAction* submitAction,
                                                         _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs)
    {
        return m_inputs->LinkSubmitActionToCard(submitAction, renderArgs);
    }

    InternalId GetInternalIdFromCard(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* card)
    {
        ComPtr<AdaptiveCard> cardImpl = PeekInnards<AdaptiveNamespace::AdaptiveCard>(card);
        return cardImpl->GetInternalId();
    }

    HRESULT RenderedAdaptiveCard::LinkCardToParent(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* card,
                                                   _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs)
    {
        // We get the card internal id from the showcard action
        InternalId cardId = GetInternalIdFromCard(card);

        // Then we get the parent card internal id from the renderArgs
        ComPtr<IAdaptiveRenderArgs> localRenderArgs(renderArgs);
        InternalId parentCardId = InternalId();
        if (renderArgs)
        {
            ComPtr<IAdaptiveCard> parentCard;
            RETURN_IF_FAILED(localRenderArgs->get_ParentCard(parentCard.GetAddressOf()));

            if (parentCard)
            {
                parentCardId = GetInternalIdFromCard(parentCard.Get());
            }
        }

        return m_inputs->LinkCardToParent(cardId, parentCardId);
    }

    HRESULT RenderedAdaptiveCard::GetInputValue(_In_ ABI::AdaptiveNamespace::IAdaptiveInputElement* inputElement,
                                                _In_ ABI::AdaptiveNamespace::IAdaptiveInputValue** inputValue)
    {
        return m_inputs->GetInputValue(inputElement, inputValue);
    }

}
