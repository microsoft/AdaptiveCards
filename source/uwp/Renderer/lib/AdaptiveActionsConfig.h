#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveActionsConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespace::IAdaptiveActionsConfig>
    {
        AdaptiveRuntime(AdaptiveActionsConfig)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveSharedNamespace::ActionsConfig actionsConfig) noexcept;

        IFACEMETHODIMP get_ShowCard(_Out_ ABI::AdaptiveNamespace::IAdaptiveShowCardActionConfig** value);
        IFACEMETHODIMP put_ShowCard(_In_ ABI::AdaptiveNamespace::IAdaptiveShowCardActionConfig* value);

        IFACEMETHODIMP get_ActionsOrientation(_Out_ ABI::AdaptiveNamespace::ActionsOrientation* value);
        IFACEMETHODIMP put_ActionsOrientation(_In_ ABI::AdaptiveNamespace::ActionsOrientation value);

        IFACEMETHODIMP get_ActionAlignment(_Out_ ABI::AdaptiveNamespace::ActionAlignment* value);
        IFACEMETHODIMP put_ActionAlignment(_In_ ABI::AdaptiveNamespace::ActionAlignment value);

        IFACEMETHODIMP get_ButtonSpacing(_Out_ UINT32* value);
        IFACEMETHODIMP put_ButtonSpacing(_In_ UINT32 value);

        IFACEMETHODIMP get_MaxActions(_Out_ UINT32* value);
        IFACEMETHODIMP put_MaxActions(_In_ UINT32 value);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveNamespace::Spacing* value);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveNamespace::Spacing value);

        IFACEMETHODIMP get_IconPlacement(_Out_ ABI::AdaptiveNamespace::IconPlacement* value);
        IFACEMETHODIMP put_IconPlacement(_In_ ABI::AdaptiveNamespace::IconPlacement value);

    private:
        ABI::AdaptiveNamespace::ActionAlignment m_actionAlignment;
        ABI::AdaptiveNamespace::ActionsOrientation m_actionsOrientation;
        UINT m_buttonSpacing;
        UINT m_maxActions;
        ABI::AdaptiveNamespace::Spacing m_spacing;
        ABI::AdaptiveNamespace::IconPlacement m_iconPlacement;

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveShowCardActionConfig> m_showCardActionConfig;
    };

    ActivatableClass(AdaptiveActionsConfig);
AdaptiveNamespaceEnd
