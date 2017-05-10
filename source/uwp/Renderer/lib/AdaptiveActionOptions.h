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

        IFACEMETHODIMP get_ActionAlignment(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment* value);
        IFACEMETHODIMP put_ActionAlignment(_In_ ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment value);

        IFACEMETHODIMP get_ButtonSpacing(_Out_ UINT32 *value);
        IFACEMETHODIMP put_ButtonSpacing(_In_ UINT32 value);

        IFACEMETHODIMP get_MaxActions(_Out_ UINT32 *value);
        IFACEMETHODIMP put_MaxActions(_In_ UINT32 value);

        IFACEMETHODIMP get_Separation(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions** separationOptions);
        IFACEMETHODIMP put_Separation(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions* separationOptions);

    private:
        AdaptiveCards::ActionOptions m_sharedActionOptions;
    };

    ActivatableClass(AdaptiveActionOptions);
}
}