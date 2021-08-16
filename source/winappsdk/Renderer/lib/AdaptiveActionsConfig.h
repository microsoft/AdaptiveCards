// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveActionsConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveActionsConfig>
    {
        AdaptiveRuntime(AdaptiveActionsConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::ActionsConfig actionsConfig) noexcept;

        IFACEMETHODIMP get_ShowCard(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveShowCardActionConfig** value);
        IFACEMETHODIMP put_ShowCard(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveShowCardActionConfig* value);

        IFACEMETHODIMP get_ActionsOrientation(_Out_ ABI::AdaptiveCards::Rendering::WinUI3::ActionsOrientation* value);
        IFACEMETHODIMP put_ActionsOrientation(ABI::AdaptiveCards::Rendering::WinUI3::ActionsOrientation value);

        IFACEMETHODIMP get_ActionAlignment(_Out_ ABI::AdaptiveCards::Rendering::WinUI3::ActionAlignment* value);
        IFACEMETHODIMP put_ActionAlignment(ABI::AdaptiveCards::Rendering::WinUI3::ActionAlignment value);

        IFACEMETHODIMP get_ButtonSpacing(_Out_ UINT32* value);
        IFACEMETHODIMP put_ButtonSpacing(UINT32 value);

        IFACEMETHODIMP get_MaxActions(_Out_ UINT32* value);
        IFACEMETHODIMP put_MaxActions(UINT32 value);

        IFACEMETHODIMP get_Spacing(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing* value);
        IFACEMETHODIMP put_Spacing(ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing value);

        IFACEMETHODIMP get_IconPlacement(_Out_ ABI::AdaptiveCards::Rendering::WinUI3::IconPlacement* value);
        IFACEMETHODIMP put_IconPlacement(ABI::AdaptiveCards::Rendering::WinUI3::IconPlacement value);

        IFACEMETHODIMP get_IconSize(_Out_ UINT32* value);
        IFACEMETHODIMP put_IconSize(UINT32 value);

    private:
        ABI::AdaptiveCards::Rendering::WinUI3::ActionAlignment m_actionAlignment;
        ABI::AdaptiveCards::Rendering::WinUI3::ActionsOrientation m_actionsOrientation;
        UINT m_buttonSpacing;
        UINT m_maxActions;
        ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing m_spacing;
        ABI::AdaptiveCards::Rendering::WinUI3::IconPlacement m_iconPlacement;
        UINT m_iconSize;

        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveShowCardActionConfig> m_showCardActionConfig;
    };

    ActivatableClass(AdaptiveActionsConfig);
}
