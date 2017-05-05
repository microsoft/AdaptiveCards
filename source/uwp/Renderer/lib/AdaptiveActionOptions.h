#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostOptions.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveActionOptions :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionOptions>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveActionOptions, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::ActionOptions actionOptions) noexcept;

        IFACEMETHODIMP get_ShowCard(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveShowCardOptions** value);
        IFACEMETHODIMP put_ShowCard(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveShowCardOptions* value);

        IFACEMETHODIMP get_ActionsOrientation(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation* value);
        IFACEMETHODIMP put_ActionsOrientation(_In_ ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation value);

        IFACEMETHODIMP get_ActionAlignment(_Out_ ABI::AdaptiveCards::XamlCardRenderer::HAlignment* value);
        IFACEMETHODIMP put_ActionAlignment(_In_ ABI::AdaptiveCards::XamlCardRenderer::HAlignment value);

        IFACEMETHODIMP get_BackgroundColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_BackgroundColor(_In_ ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_BorderColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_BorderColor(_In_ ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_TextColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_TextColor(_In_ ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_BorderThickness(_Out_ UINT32 *value);
        IFACEMETHODIMP put_BorderThickness(_In_ UINT32 value);

        IFACEMETHODIMP get_FontWeight(_Out_ UINT32 *value);
        IFACEMETHODIMP put_FontWeight(_In_ UINT32 value);

        IFACEMETHODIMP get_FontSize(_Out_ UINT32 *value);
        IFACEMETHODIMP put_FontSize(_In_ UINT32 value);

        IFACEMETHODIMP get_Spacing(_Out_ UINT32 *value);
        IFACEMETHODIMP put_Spacing(_In_ UINT32 value);

        IFACEMETHODIMP get_Padding(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveBoundaryOptions** value);
        IFACEMETHODIMP put_Padding(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveBoundaryOptions* value);

    private:
        AdaptiveCards::ActionOptions m_sharedActionOptions;
    };

    ActivatableClass(AdaptiveActionOptions);
}
}