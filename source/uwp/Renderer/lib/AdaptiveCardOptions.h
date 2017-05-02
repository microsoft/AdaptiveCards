#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostOptions.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveCardOptions :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCardOptions>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveCardOptions, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::AdaptiveCardOptions adaptiveCardOptions) noexcept;

        IFACEMETHODIMP get_Padding(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveBoundaryOptions** value);
        IFACEMETHODIMP put_Padding(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveBoundaryOptions* value);

        IFACEMETHODIMP get_MaxActions(_Out_ INT32 *value);
        IFACEMETHODIMP put_MaxActions(_In_ INT32 value);

        IFACEMETHODIMP get_ActionAlignment(_Out_ ABI::AdaptiveCards::XamlCardRenderer::HAlignment* value);
        IFACEMETHODIMP put_ActionAlignment(_In_ ABI::AdaptiveCards::XamlCardRenderer::HAlignment value);

        IFACEMETHODIMP get_ActionsOrientation(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation* value);
        IFACEMETHODIMP put_ActionsOrientation(_In_ ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation value);

        IFACEMETHODIMP get_BorderColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_BorderColor(_In_ ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_TextColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_TextColor(_In_ ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_BackgroundColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_BackgroundColor(_In_ ABI::Windows::UI::Color value);

    private:
        AdaptiveCards::AdaptiveCardOptions m_sharedAdaptiveCardOptions;
    };

    ActivatableClass(AdaptiveCardOptions);
}
}