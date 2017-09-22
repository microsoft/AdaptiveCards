#pragma once

#include "pch.h"
#include "AdaptiveCards.XamlCardRenderer.h"
#include "util.h"
#include "InputItem.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveRenderResult :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::Implements<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveRenderResult>,
            Microsoft::WRL::FtmBase>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveRenderResult, BaseTrust)

    public:
        AdaptiveRenderResult();

        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(
            bool isValid,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* card,
            ABI::Windows::UI::Xaml::IUIElement* uiElement,
            std::shared_ptr<std::vector<InputItem>> inputs);

        // IAdaptiveRenderResult
        IFACEMETHODIMP add_Action(
            _In_ ABI::Windows::Foundation::ITypedEventHandler<ABI::AdaptiveCards::XamlCardRenderer::AdaptiveRenderResult*, ABI::AdaptiveCards::XamlCardRenderer::AdaptiveActionEventArgs*>* handler,
            _Out_ EventRegistrationToken* token);

        IFACEMETHODIMP remove_Action(
            _In_ EventRegistrationToken token);

        IFACEMETHODIMP get_Card(_COM_Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard** value);
        IFACEMETHODIMP get_UI(_COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** value);
        IFACEMETHODIMP get_InputValuesJson(_Out_ HSTRING* value);
        IFACEMETHODIMP IsValid(_Out_ boolean* value);

        HRESULT SendActionEvent(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionEventArgs* eventArgs);

    private:
        bool m_isValid;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard> m_card;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IUIElement> m_uiElement;
        std::shared_ptr<std::vector<InputItem>> m_inputs;
    };

    ActivatableClass(AdaptiveRenderResult);
}}