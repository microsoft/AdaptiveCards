#pragma once
#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class RenderingActionEventArgs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
        ABI::AdaptiveCards::XamlCardRenderer::IRenderingActionEventArgs>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_RenderingActionEventArgs, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize();
        HRESULT RuntimeClassInitialize(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement* action);

        IFACEMETHODIMP get_Action(_Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement** action);

        IFACEMETHODIMP get_CustomFrameworkElement(_COM_Outptr_ ABI::Windows::UI::Xaml::IFrameworkElement** customFrameworkElement);
        //IFACEMETHODIMP put_CustomFrameworkElement(_In_ ABI::Windows::UI::Xaml::IFrameworkElement* customFrameworkElement);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionElement> m_action;
        Microsoft::WRL::ComPtr<ABI::Windows::UI::Xaml::IFrameworkElement> m_customFrameworkElement;
    };
}}