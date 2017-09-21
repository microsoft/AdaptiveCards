#pragma once

#include "pch.h"
#include "AdaptiveCards.XamlCardRenderer.h"
#include "util.h"
#include "InputItem.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class RenderedAdaptiveCard :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::Implements<ABI::AdaptiveCards::XamlCardRenderer::IRenderedAdaptiveCard>>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_RenderedAdaptiveCard, BaseTrust)

    public:
        RenderedAdaptiveCard();

        HRESULT RuntimeClassInitialize();

        // IRenderedAdaptiveCard
        IFACEMETHODIMP get_OriginatingCard(_COM_Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard** value);
        IFACEMETHODIMP get_FrameworkElement(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** value);
        IFACEMETHODIMP get_Errors(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<HSTRING> ** value);
        IFACEMETHODIMP get_Warnings(_COM_Outptr_ ABI::Windows::Foundation::Collections::IVector<HSTRING> ** value);
        IFACEMETHODIMP get_IsRenderedSuccessfully(_Out_ boolean* value);
        IFACEMETHODIMP add_Action(
            _In_ ABI::Windows::Foundation::ITypedEventHandler<
                ABI::AdaptiveCards::XamlCardRenderer::RenderedAdaptiveCard*,
                ABI::AdaptiveCards::XamlCardRenderer::AdaptiveActionEventArgs*>* handler,
            _Out_ EventRegistrationToken* token);
        IFACEMETHODIMP remove_Action(_In_ EventRegistrationToken token);

        std::shared_ptr<std::vector<InputItem>> GetInputItems();
        void SetFrameworkElement(ABI::Windows::UI::Xaml::IUIElement* value);
        void SetOriginatingCard(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* value);
        void SetInputItems(std::shared_ptr<std::vector<InputItem>> value);
        HRESULT SendActionEvent(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionEventArgs* eventArgs);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard> m_originatingCard;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_frameworkElement;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<HSTRING>> m_errors;
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::Collections::IVector<HSTRING>> m_warnings;
        std::shared_ptr<std::vector<InputItem>> m_inputs;
        std::shared_ptr<ActionEventSource> m_events;
    };

    ActivatableClass(RenderedAdaptiveCard);
}}