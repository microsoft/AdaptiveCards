#pragma once

#include "pch.h"
#include "AdaptiveCards.Uwp.h"
#include "util.h"
#include "InputItem.h"
#include "AdaptiveInputs.h"

namespace AdaptiveCards { namespace Uwp
{
    class RenderedAdaptiveCard :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::Implements<ABI::AdaptiveCards::Uwp::IRenderedAdaptiveCard>>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_RenderedAdaptiveCard, BaseTrust)

    public:
        RenderedAdaptiveCard();

        HRESULT RuntimeClassInitialize();

        // IRenderedAdaptiveCard
        IFACEMETHODIMP get_OriginatingCard(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveCard** value);
        IFACEMETHODIMP get_FrameworkElement(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** value);
        IFACEMETHODIMP get_UserInputs(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveInputs** value);
        IFACEMETHODIMP add_Action(
            _In_ ABI::Windows::Foundation::ITypedEventHandler<
                ABI::AdaptiveCards::Uwp::RenderedAdaptiveCard*,
                ABI::AdaptiveCards::Uwp::AdaptiveActionEventArgs*>* handler,
            _Out_ EventRegistrationToken* token);
        IFACEMETHODIMP remove_Action(_In_ EventRegistrationToken token);

        HRESULT get_Errors(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<HSTRING>** value);
        HRESULT get_Warnings(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<HSTRING>** value);
        std::shared_ptr<std::vector<InputItem>> GetInputItems();
        void SetFrameworkElement(ABI::Windows::UI::Xaml::IUIElement* value);
        void SetOriginatingCard(ABI::AdaptiveCards::Uwp::IAdaptiveCard* value);
        HRESULT SendActionEvent(ABI::AdaptiveCards::Uwp::IAdaptiveActionElement* eventArgs);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveCard> m_originatingCard;
        Microsoft::WRL::ComPtr<AdaptiveCards::Uwp::AdaptiveInputs> m_inputs;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_frameworkElement;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<HSTRING>> m_errors;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<HSTRING>> m_warnings;
        std::shared_ptr<ActionEventSource> m_events;
    };

    ActivatableClass(RenderedAdaptiveCard);
}}