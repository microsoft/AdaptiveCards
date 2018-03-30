#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "util.h"
#include "InputValue.h"
#include "AdaptiveInputs.h"

AdaptiveNamespaceStart
    class RenderedAdaptiveCard :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::Implements<ABI::AdaptiveNamespaceRef::IRenderedAdaptiveCard>>
    {
        AdaptiveRuntime(RenderedAdaptiveCard)

    public:
        RenderedAdaptiveCard();

        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveError*>* errors,
            _In_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveWarning*>* warnings);

        // IRenderedAdaptiveCard
        IFACEMETHODIMP get_OriginatingCard(_COM_Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveCard** value);
        IFACEMETHODIMP get_FrameworkElement(_COM_Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** value);
        IFACEMETHODIMP get_UserInputs(_COM_Outptr_ ABI::AdaptiveNamespaceRef::IAdaptiveInputs** value);
        IFACEMETHODIMP add_Action(
            _In_ ABI::Windows::Foundation::ITypedEventHandler<
                ABI::AdaptiveNamespaceRef::RenderedAdaptiveCard*,
                ABI::AdaptiveNamespaceRef::AdaptiveActionEventArgs*>* handler,
            _Out_ EventRegistrationToken* token);
        IFACEMETHODIMP remove_Action(_In_ EventRegistrationToken token);

        IFACEMETHODIMP get_Errors(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveError*>** value);
        IFACEMETHODIMP get_Warnings(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveWarning*>** value);

        HRESULT AddInputValue(ABI::AdaptiveNamespaceRef::IAdaptiveInputValue* inputValue);
        void SetFrameworkElement(ABI::Windows::UI::Xaml::IFrameworkElement* value);
        void SetOriginatingCard(ABI::AdaptiveNamespaceRef::IAdaptiveCard* value);
        HRESULT SendActionEvent(ABI::AdaptiveNamespaceRef::IAdaptiveActionElement* eventArgs);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveCard> m_originatingCard;
        Microsoft::WRL::ComPtr<AdaptiveNamespaceRef::AdaptiveInputs> m_inputs;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IFrameworkElement> m_frameworkElement;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveError*>> m_errors;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveNamespaceRef::IAdaptiveWarning*>> m_warnings;
        std::shared_ptr<ActionEventSource> m_events;
    };

    ActivatableClass(RenderedAdaptiveCard);
AdaptiveNamespaceEnd