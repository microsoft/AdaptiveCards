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
#include "vector.h"
#include <windows.foundation.collections.h>
#include <Windows.UI.Xaml.h>
#include "XamlBuilder.h"
#include "XamlHelpers.h"

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
            return XamlBuilder::HandleToggleVisibilityClick(m_frameworkElement.Get(), actionElement);

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

        case ABI::AdaptiveCards::Rendering::Uwp::ActionType_OpenUrl:
        case ABI::AdaptiveCards::Rendering::Uwp::ActionType_Submit:
        case ABI::AdaptiveCards::Rendering::Uwp::ActionType_Custom:
        default:
            return m_actionEvents->InvokeAll(this, eventArgs.Get());
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
                                                    _In_ ABI::Windows::UI::Xaml::IUIElement* showCardFrameworkElement) try
    {
        InternalId actionSetId;
        ComPtr<AdaptiveNamespace::AdaptiveActionSet> actionSetImpl = PeekInnards<AdaptiveNamespace::AdaptiveActionSet>(actionSet);
        actionSetId = actionSetImpl->GetInternalId();

        RETURN_IF_FAILED(AddInlineShowCardHelper(actionSetId, showCardAction, showCardFrameworkElement));

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT RenderedAdaptiveCard::AddInlineShowCard(ABI::AdaptiveNamespace::IAdaptiveCard* adaptiveCard,
                                                    ABI::AdaptiveNamespace::IAdaptiveShowCardAction* showCardAction,
                                                    ABI::Windows::UI::Xaml::IUIElement* showCardFrameworkElement) try
    {
        InternalId actionSetId;
        ComPtr<AdaptiveNamespace::AdaptiveCard> adaptiveCardImpl = PeekInnards<AdaptiveNamespace::AdaptiveCard>(adaptiveCard);
        actionSetId = adaptiveCardImpl->GetInternalId();

        RETURN_IF_FAILED(AddInlineShowCardHelper(actionSetId, showCardAction, showCardFrameworkElement));

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT RenderedAdaptiveCard::AddInlineShowCardHelper(AdaptiveCards::InternalId& actionSetId,
                                                          ABI::AdaptiveNamespace::IAdaptiveShowCardAction* showCardAction,
                                                          ABI::Windows::UI::Xaml::IUIElement* showCardFrameworkElement) try
    {
        ComPtr<AdaptiveNamespace::AdaptiveShowCardAction> showCardImpl =
            PeekInnards<AdaptiveNamespace::AdaptiveShowCardAction>(showCardAction);
        InternalId showCardActionId = showCardImpl->GetInternalId();

        m_showCards.emplace(std::make_pair(showCardActionId, std::make_pair(actionSetId, showCardFrameworkElement)));

        return S_OK;
    }
    CATCH_RETURN;

    HRESULT RenderedAdaptiveCard::AddInputValue(_In_ IAdaptiveInputValue* inputItem)
    {
        return m_inputs->AddInputValue(inputItem);
    }
}
