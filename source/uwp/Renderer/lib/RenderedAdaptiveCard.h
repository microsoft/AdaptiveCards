// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "util.h"
#include "InputValue.h"
#include "AdaptiveInputs.h"

namespace AdaptiveNamespace
{
    class DECLSPEC_UUID("F25E0D36-0B5B-4398-AFC8-F84105EC46A2") RenderedAdaptiveCard
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<IWeakReferenceSource>,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveNamespace::IRenderedAdaptiveCard>>
    {
        AdaptiveRuntime(RenderedAdaptiveCard);

    public:
        RenderedAdaptiveCard();

        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveError*>* errors,
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>* warnings);

        // IRenderedAdaptiveCard
        IFACEMETHODIMP get_OriginatingCard(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveCard** value) override;
        IFACEMETHODIMP get_OriginatingHostConfig(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveHostConfig** value) override;
        IFACEMETHODIMP get_FrameworkElement(_COM_Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** value) override;
        IFACEMETHODIMP get_UserInputs(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveInputs** value) override;
        IFACEMETHODIMP add_Action(_In_ ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveNamespace::RenderedAdaptiveCard*,
                                                                                    ABI::AdaptiveNamespace::AdaptiveActionEventArgs*>* handler,
                                  _Out_ EventRegistrationToken* token) override;
        IFACEMETHODIMP remove_Action(EventRegistrationToken token) override;

        IFACEMETHODIMP add_MediaClicked(
            _In_ ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveNamespace::RenderedAdaptiveCard*, ABI::AdaptiveNamespace::AdaptiveMediaEventArgs*>* handler,
            _Out_ EventRegistrationToken* token) override;
        IFACEMETHODIMP remove_MediaClicked(EventRegistrationToken token) override;

        IFACEMETHODIMP get_Errors(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveError*>** value) override;
        IFACEMETHODIMP get_Warnings(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>** value) override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        HRESULT AddInlineShowCard(_In_ ABI::AdaptiveNamespace::IAdaptiveActionSet* actionSet,
                                  _In_ ABI::AdaptiveNamespace::IAdaptiveShowCardAction* showCardAction,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* showCardFrameworkElement,
                                  _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs);

        HRESULT AddInlineShowCard(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* adaptiveCard,
                                  _In_ ABI::AdaptiveNamespace::IAdaptiveShowCardAction* showCardAction,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* showCardFrameworkElement,
                                  _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs);

        HRESULT AddInputValue(_In_ ABI::AdaptiveNamespace::IAdaptiveInputValue* inputValue,
                              _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* containerCardId);
        HRESULT LinkSubmitActionToCard(_In_ ABI::AdaptiveNamespace::IAdaptiveSubmitAction* submitAction,
                                       _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs);
        HRESULT LinkCardToParent(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* card,
                                 _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs);

        void SetFrameworkElement(_In_ ABI::Windows::UI::Xaml::IFrameworkElement* value);
        void SetOriginatingCard(_In_ ABI::AdaptiveNamespace::IAdaptiveCard* value);
        void SetOriginatingHostConfig(_In_ ABI::AdaptiveNamespace::IAdaptiveHostConfig* value);
        HRESULT SendActionEvent(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* eventArgs);
        HRESULT SendMediaClickedEvent(_In_ ABI::AdaptiveNamespace::IAdaptiveMedia* eventArgs);

    private:
        HRESULT HandleInlineShowCardEvent(_In_ ABI::AdaptiveNamespace::IAdaptiveActionElement* actionElement);

        HRESULT AddInlineShowCardHelper(AdaptiveCards::InternalId& internalId,
                                        _In_ ABI::AdaptiveNamespace::IAdaptiveShowCardAction* showCardAction,
                                        _In_ ABI::Windows::UI::Xaml::IUIElement* showCardFrameworkElement,
                                        _In_ ABI::AdaptiveNamespace::IAdaptiveRenderArgs* renderArgs);

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveCard> m_originatingCard;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveHostConfig> m_originatingHostConfig;
        Microsoft::WRL::ComPtr<AdaptiveNamespace::AdaptiveInputs> m_inputs;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IFrameworkElement> m_frameworkElement;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveError*>> m_errors;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespace::AdaptiveWarning*>> m_warnings;
        std::shared_ptr<ActionEventSource> m_actionEvents;
        std::shared_ptr<MediaEventSource> m_mediaClickedEvents;

        // Map of rendered show cards. The key is the id of the show card action, and the value is a pair made up of the
        // id of the action set (InvalidId for actions in the bottom action bar) and the UIElement for the card.
        std::unordered_map<AdaptiveSharedNamespace::InternalId, std::pair<AdaptiveSharedNamespace::InternalId, Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement>>, InternalIdKeyHash> m_showCards;        
    };

    ActivatableClass(RenderedAdaptiveCard);
}
