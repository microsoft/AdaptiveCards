#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "util.h"
#include "InputItem.h"
#include "AdaptiveInputs.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{

    class RenderedAdaptiveCard :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::Implements<ABI::AdaptiveCards::Rendering::Uwp::IRenderedAdaptiveCard>>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_RenderedAdaptiveCard, BaseTrust)

    public:
        RenderedAdaptiveCard();

        HRESULT RuntimeClassInitialize();

        // IRenderedAdaptiveCard
        IFACEMETHODIMP get_OriginatingCard(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCard** value);
        IFACEMETHODIMP get_FrameworkElement(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** value);
        IFACEMETHODIMP get_UserInputs(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputs** value);
        IFACEMETHODIMP add_Action(
            _In_ ABI::Windows::Foundation::ITypedEventHandler<
                ABI::AdaptiveCards::Rendering::Uwp::RenderedAdaptiveCard*,
                ABI::AdaptiveCards::Rendering::Uwp::AdaptiveActionEventArgs*>* handler,
            _Out_ EventRegistrationToken* token);
        IFACEMETHODIMP remove_Action(_In_ EventRegistrationToken token);

        IFACEMETHODIMP get_Errors(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveError*>** value);
        IFACEMETHODIMP get_Warnings(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveWarning*>** value);

        std::shared_ptr<std::vector<InputItem>> GetInputItems();
        void SetFrameworkElement(ABI::Windows::UI::Xaml::IUIElement* value);
        void SetOriginatingCard(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCard* value);
        HRESULT SendActionEvent(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveActionElement* eventArgs);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCard> m_originatingCard;
        Microsoft::WRL::ComPtr<AdaptiveCards::Rendering::Uwp::AdaptiveInputs> m_inputs;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_frameworkElement;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveError*>> m_errors;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveWarning*>> m_warnings;
        std::shared_ptr<ActionEventSource> m_events;
    };

    ActivatableClass(RenderedAdaptiveCard);
}}}