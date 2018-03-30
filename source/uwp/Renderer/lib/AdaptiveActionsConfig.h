#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveActionsConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespaceRef::IAdaptiveActionsConfig>
    {
        AdaptiveRuntime(AdaptiveActionsConfig)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::ActionsConfig actionsConfig) noexcept;

        IFACEMETHODIMP get_ShowCard(_Out_ ABI::AdaptiveNamespaceRef::IAdaptiveShowCardActionConfig** value);
        IFACEMETHODIMP put_ShowCard(_In_ ABI::AdaptiveNamespaceRef::IAdaptiveShowCardActionConfig* value);

        IFACEMETHODIMP get_ActionsOrientation(_Out_ ABI::AdaptiveNamespaceRef::ActionsOrientation* value);
        IFACEMETHODIMP put_ActionsOrientation(_In_ ABI::AdaptiveNamespaceRef::ActionsOrientation value);

        IFACEMETHODIMP get_ActionAlignment(_Out_ ABI::AdaptiveNamespaceRef::ActionAlignment* value);
        IFACEMETHODIMP put_ActionAlignment(_In_ ABI::AdaptiveNamespaceRef::ActionAlignment value);

        IFACEMETHODIMP get_ButtonSpacing(_Out_ UINT32* value);
        IFACEMETHODIMP put_ButtonSpacing(_In_ UINT32 value);

        IFACEMETHODIMP get_MaxActions(_Out_ UINT32* value);
        IFACEMETHODIMP put_MaxActions(_In_ UINT32 value);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveNamespaceRef::Spacing* value);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveNamespaceRef::Spacing value);

    private:
        ABI::AdaptiveNamespaceRef::ActionAlignment m_actionAlignment;
        ABI::AdaptiveNamespaceRef::ActionsOrientation m_actionsOrientation;
        UINT m_buttonSpacing;
        UINT m_maxActions;
        ABI::AdaptiveNamespaceRef::Spacing m_spacing;

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespaceRef::IAdaptiveShowCardActionConfig> m_showCardActionConfig;
    };

    ActivatableClass(AdaptiveActionsConfig);
AdaptiveNamespaceEnd
