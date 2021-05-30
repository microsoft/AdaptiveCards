// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "util.h"
#include "InputValue.h"
#include "AdaptiveInputs.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class DECLSPEC_UUID("F25E0D36-0B5B-4398-AFC8-F84105EC46A2") RenderedAdaptiveCard
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<IWeakReferenceSource>,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveCards::Rendering::Uwp::IRenderedAdaptiveCard>>
    {
        AdaptiveRuntime(RenderedAdaptiveCard);

    public:
        RenderedAdaptiveCard();

        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveError*>* errors,
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>* warnings);

        // IRenderedAdaptiveCard
        IFACEMETHODIMP get_OriginatingCard(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCard** value) override;
        IFACEMETHODIMP get_OriginatingHostConfig(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig** value) override;
        IFACEMETHODIMP get_FrameworkElement(_COM_Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** value) override;
        IFACEMETHODIMP get_UserInputs(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputs** value) override;
        IFACEMETHODIMP add_Action(
            _In_ ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard*,
                                                              ABI::AdaptiveCards::Rendering::Uwp::AdaptiveActionEventArgs*>* handler,
            _Out_ EventRegistrationToken* token) override;
        IFACEMETHODIMP remove_Action(EventRegistrationToken token) override;

        IFACEMETHODIMP add_MediaClicked(
            _In_ ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard*,
                                                              ABI::AdaptiveCards::Rendering::Uwp::AdaptiveMediaEventArgs*>* handler,
            _Out_ EventRegistrationToken* token) override;
        IFACEMETHODIMP remove_MediaClicked(EventRegistrationToken token) override;

        IFACEMETHODIMP get_Errors(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveError*>** value) override;
        IFACEMETHODIMP get_Warnings(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>** value) override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        HRESULT AddInlineShowCard(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionSet* actionSet,
                                  _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveShowCardAction* showCardAction,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* showCardFrameworkElement,
                                  _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs);

        HRESULT AddInlineShowCard(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCard* adaptiveCard,
                                  _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveShowCardAction* showCardAction,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* showCardFrameworkElement,
                                  _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs);

        HRESULT AddInputValue(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputValue* inputValue,
                              _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* containerCardId);
        HRESULT LinkActionToCard(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement* submitAction,
                                 _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs);
        HRESULT LinkCardToParent(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCard* card,
                                 _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs);
        HRESULT GetInputValue(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputElement* inputElement,
                              _COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputValue** inputValue);

        void SetFrameworkElement(_In_ ABI::Windows::UI::Xaml::IFrameworkElement* value);
        void SetOriginatingCard(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCard* value);
        void SetOriginatingHostConfig(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig* value);
        HRESULT SendActionEvent(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement* eventArgs);
        HRESULT SendMediaClickedEvent(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveMedia* eventArgs);

    private:
        HRESULT HandleInlineShowCardEvent(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement* actionElement);

        HRESULT AddInlineShowCardHelper(AdaptiveCards::InternalId& internalId,
                                        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveShowCardAction* showCardAction,
                                        _In_ ABI::Windows::UI::Xaml::IUIElement* showCardFrameworkElement,
                                        _In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs* renderArgs);

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCard> m_originatingCard;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHostConfig> m_originatingHostConfig;
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::Uwp::AdaptiveInputs> m_inputs;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IFrameworkElement> m_frameworkElement;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveError*>> m_errors;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::AdaptiveWarning*>> m_warnings;
        std::shared_ptr<ActionEventSource> m_actionEvents;
        std::shared_ptr<MediaEventSource> m_mediaClickedEvents;

        // Map of rendered show cards. The key is the id of the show card action, and the value is a pair made up of the
        // id of the action set (InvalidId for actions in the bottom action bar) and the UIElement for the card.
        std::unordered_map<AdaptiveCards::InternalId, std::pair<AdaptiveCards::InternalId, Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement>>, InternalIdKeyHash> m_showCards;
    };

    ActivatableClass(RenderedAdaptiveCard);
}
