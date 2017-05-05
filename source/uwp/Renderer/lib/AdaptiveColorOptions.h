#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostOptions.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveColorOptions :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOptions>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveColorOptions, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ColorOptions colorOptions) noexcept;

        IFACEMETHODIMP get_Default(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** value);
        IFACEMETHODIMP put_Default(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value);

        IFACEMETHODIMP get_Accent(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** value);
        IFACEMETHODIMP put_Accent(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value);

        IFACEMETHODIMP get_Dark(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** value);
        IFACEMETHODIMP put_Dark(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value);

        IFACEMETHODIMP get_Light(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** value);
        IFACEMETHODIMP put_Light(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value);

        IFACEMETHODIMP get_Good(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** value);
        IFACEMETHODIMP put_Good(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value);

        IFACEMETHODIMP get_Warning(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** value);
        IFACEMETHODIMP put_Warning(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value);

        IFACEMETHODIMP get_Attention(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** value);
        IFACEMETHODIMP put_Attention(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value);

    private:
        ColorOptions m_sharedColorOptions;
    };

    ActivatableClass(AdaptiveColorOptions);
}
}