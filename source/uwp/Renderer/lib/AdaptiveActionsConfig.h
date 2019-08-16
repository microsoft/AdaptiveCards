// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    class AdaptiveActionsConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveActionsConfig>
    {
        AdaptiveRuntime(AdaptiveActionsConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveSharedNamespace::ActionsConfig actionsConfig) noexcept;

        IFACEMETHODIMP get_ShowCard(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveShowCardActionConfig** value);
        IFACEMETHODIMP put_ShowCard(_In_ ABI::AdaptiveNamespace::IAdaptiveShowCardActionConfig* value);

        IFACEMETHODIMP get_ActionsOrientation(_Out_ ABI::AdaptiveNamespace::ActionsOrientation* value);
        IFACEMETHODIMP put_ActionsOrientation(ABI::AdaptiveNamespace::ActionsOrientation value);

        IFACEMETHODIMP get_ActionAlignment(_Out_ ABI::AdaptiveNamespace::ActionAlignment* value);
        IFACEMETHODIMP put_ActionAlignment(ABI::AdaptiveNamespace::ActionAlignment value);

        IFACEMETHODIMP get_ButtonSpacing(_Out_ UINT32* value);
        IFACEMETHODIMP put_ButtonSpacing(UINT32 value);

        IFACEMETHODIMP get_MaxActions(_Out_ UINT32* value);
        IFACEMETHODIMP put_MaxActions(UINT32 value);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveNamespace::Spacing* value);
        IFACEMETHODIMP put_Spacing(ABI::AdaptiveNamespace::Spacing value);

        IFACEMETHODIMP get_IconPlacement(_Out_ ABI::AdaptiveNamespace::IconPlacement* value);
        IFACEMETHODIMP put_IconPlacement(ABI::AdaptiveNamespace::IconPlacement value);

        IFACEMETHODIMP get_IconSize(_Out_ UINT32* value);
        IFACEMETHODIMP put_IconSize(UINT32 value);

    private:
        ABI::AdaptiveNamespace::ActionAlignment m_actionAlignment;
        ABI::AdaptiveNamespace::ActionsOrientation m_actionsOrientation;
        UINT m_buttonSpacing;
        UINT m_maxActions;
        ABI::AdaptiveNamespace::Spacing m_spacing;
        ABI::AdaptiveNamespace::IconPlacement m_iconPlacement;
        UINT m_iconSize;

        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveShowCardActionConfig> m_showCardActionConfig;
    };

    ActivatableClass(AdaptiveActionsConfig);
}
