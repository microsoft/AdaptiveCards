#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveActionsConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveActionsConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveActionsConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::ActionsConfig actionsConfig) noexcept;

        IFACEMETHODIMP get_ShowCard(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveShowCardActionConfig** value);
        IFACEMETHODIMP put_ShowCard(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveShowCardActionConfig* value);

        IFACEMETHODIMP get_ActionsOrientation(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation* value);
        IFACEMETHODIMP put_ActionsOrientation(_In_ ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation value);

        IFACEMETHODIMP get_ActionAlignment(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment* value);
        IFACEMETHODIMP put_ActionAlignment(_In_ ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment value);

        IFACEMETHODIMP get_ButtonSpacing(_Out_ UINT32 *value);
        IFACEMETHODIMP put_ButtonSpacing(_In_ UINT32 value);

        IFACEMETHODIMP get_MaxActions(_Out_ UINT32 *value);
        IFACEMETHODIMP put_MaxActions(_In_ UINT32 value);

        IFACEMETHODIMP get_Spacing(ABI::AdaptiveCards::XamlCardRenderer::Spacing* value);
        IFACEMETHODIMP put_Spacing(ABI::AdaptiveCards::XamlCardRenderer::Spacing value);

    private:
        AdaptiveCards::ActionsConfig m_sharedActionsConfig;
    };

    ActivatableClass(AdaptiveActionsConfig);
}
}