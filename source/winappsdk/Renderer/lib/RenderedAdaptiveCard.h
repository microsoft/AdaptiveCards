// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.WinUI3.h"
#include "util.h"
#include "InputValue.h"
#include "AdaptiveInputs.h"

namespace AdaptiveCards::Rendering::WinUI3
{
    class DECLSPEC_UUID("F25E0D36-0B5B-4398-AFC8-F84105EC46A2") RenderedAdaptiveCard
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              Microsoft::WRL::Implements<IWeakReferenceSource>,
                                              Microsoft::WRL::CloakedIid<ITypePeek>,
                                              Microsoft::WRL::Implements<ABI::AdaptiveCards::Rendering::WinUI3::IRenderedAdaptiveCard>>
    {
        AdaptiveRuntime(RenderedAdaptiveCard);

    public:
        RenderedAdaptiveCard();

        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveError*>* errors,
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning*>* warnings);

        // IRenderedAdaptiveCard
        IFACEMETHODIMP get_OriginatingCard(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard** value) override;
        IFACEMETHODIMP get_OriginatingHostConfig(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig** value) override;
        IFACEMETHODIMP get_FrameworkElement(_COM_Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** value) override;
        IFACEMETHODIMP get_UserInputs(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputs** value) override;
        IFACEMETHODIMP add_Action(
            _In_ ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::Rendering::WinUI3::RenderedAdaptiveCard*,
                                                              ABI::AdaptiveCards::Rendering::WinUI3::AdaptiveActionEventArgs*>* handler,
            _Out_ EventRegistrationToken* token) override;
        IFACEMETHODIMP remove_Action(EventRegistrationToken token) override;

        IFACEMETHODIMP add_MediaClicked(
            _In_ ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::Rendering::WinUI3::RenderedAdaptiveCard*,
                                                              ABI::AdaptiveCards::Rendering::WinUI3::AdaptiveMediaEventArgs*>* handler,
            _Out_ EventRegistrationToken* token) override;
        IFACEMETHODIMP remove_MediaClicked(EventRegistrationToken token) override;

        IFACEMETHODIMP get_Errors(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveError*>** value) override;
        IFACEMETHODIMP get_Warnings(
            _COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning*>** value) override;

        // ITypePeek method
        void* PeekAt(REFIID riid) override { return PeekHelper(riid, this); }

        HRESULT AddInlineShowCard(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionSet* actionSet,
                                  _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveShowCardAction* showCardAction,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionButtonUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionOverflowUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                  UINT32 primaryButtonIndex,
                                  _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs);

        HRESULT AddInlineShowCard(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* adaptiveCard,
                                  _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveShowCardAction* showCardAction,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionButtonUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionOverflowUIElement,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                  UINT32 primaryButtonIndex,
                                  _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs);

        HRESULT AddOverflowButton(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionSet* actionSet,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionUIElement);

        HRESULT AddOverflowButton(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* actionCard,
                                  _In_ ABI::Windows::UI::Xaml::IUIElement* actionUIElement);

        HRESULT AddInputValue(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputValue* inputValue,
                              _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* containerCardId);
        HRESULT LinkActionToCard(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* submitAction,
                                 _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs);
        HRESULT LinkCardToParent(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* card,
                                 _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs);
        HRESULT GetInputValue(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveInputElement* inputElement,
                              _COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveInputValue** inputValue);

        void SetFrameworkElement(_In_ ABI::Windows::UI::Xaml::IFrameworkElement* value);
        void SetOriginatingCard(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard* value);
        void SetOriginatingHostConfig(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig* value);
        HRESULT SendActionEvent(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* eventArgs);
        HRESULT SendMediaClickedEvent(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveMedia* eventArgs);

    private:
        HRESULT HandleInlineShowCardEvent(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement* actionElement);

        HRESULT AddInlineShowCardHelper(UINT32 internalId,
                                        _In_ ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveShowCardAction* showCardAction,
                                        _In_ ABI::Windows::UI::Xaml::IUIElement* actionButtonUIElement,
                                        _In_ ABI::Windows::UI::Xaml::IUIElement* actionOverflowUIElement,
                                        _In_ ABI::Windows::UI::Xaml::IUIElement* showCardUIElement,
                                        UINT32 primaryButtonIndex,
                                        _In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveRenderArgs* renderArgs);

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveCard> m_originatingCard;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveHostConfig> m_originatingHostConfig;
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::WinUI3::AdaptiveInputs> m_inputs;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IFrameworkElement> m_frameworkElement;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveError*>> m_errors;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::ObjectModel::WinUI3::AdaptiveWarning*>> m_warnings;
        std::shared_ptr<ActionEventSource> m_actionEvents;
        std::shared_ptr<MediaEventSource> m_mediaClickedEvents;

        // Map of rendered show cards. The key is the id of the show card action, and the value is the ShowCardInfo structure for that show card
        std::unordered_map<UINT32, std::shared_ptr<ShowCardInfo>> m_showCards;

        // Map of the rendered overflow buttons keyed on action set Id. This is needed to move buttons around when a
        // show card from an overflow menu needs to be moved to a primary button in the action set
        std::unordered_map<UINT32, Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement>> m_overflowButtons;
    };

    ActivatableClass(RenderedAdaptiveCard);
}
