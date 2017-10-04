#pragma once

#include "AdaptiveCards.Uwp.h"
#include "RenderedAdaptiveCard.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveRenderContext :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Uwp::IAdaptiveRenderContext>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveRenderContext, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(
            ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig* hostConfig,
            ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration* elementRendererRegistration,
            ABI::AdaptiveCards::Uwp::IAdaptiveActionRendererRegistration* actionRendererRegistration,
            AdaptiveCards::Uwp::RenderedAdaptiveCard* renderResult) noexcept;

        IFACEMETHODIMP get_HostConfig(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig** value);
        IFACEMETHODIMP get_ElementRenderers(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration** value);
        IFACEMETHODIMP get_ActionRenderers(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveActionRendererRegistration** value);
        IFACEMETHODIMP AddInputItem(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveCardElement* cardElement, _In_ ABI::Windows::UI::Xaml::IUIElement* uiElement);
        IFACEMETHODIMP SendActionEvent(ABI::AdaptiveCards::Uwp::IAdaptiveActionEventArgs* eventArgs);
        IFACEMETHODIMP get_UserInputs(_COM_Outptr_ ABI::AdaptiveCards::Uwp::IAdaptiveInputs** value);

        IFACEMETHODIMP get_ParentContainerStyle(_Out_ ABI::AdaptiveCards::Uwp::ContainerStyle *value);
        IFACEMETHODIMP put_ParentContainerStyle(_In_ ABI::AdaptiveCards::Uwp::ContainerStyle value);


    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveHostConfig> m_hostConfig;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveElementRendererRegistration> m_elementRendererRegistration;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Uwp::IAdaptiveActionRendererRegistration> m_actionRendererRegistration;
        Microsoft::WRL::ComPtr<AdaptiveCards::Uwp::RenderedAdaptiveCard> m_renderResult;
        ABI::AdaptiveCards::Uwp::ContainerStyle m_containerStyle;
    };

    ActivatableClass(AdaptiveRenderContext);
}}
