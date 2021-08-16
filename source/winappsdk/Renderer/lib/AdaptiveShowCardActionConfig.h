// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveShowCardActionConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveShowCardActionConfig>
    {
        AdaptiveRuntime(AdaptiveShowCardActionConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::ShowCardActionConfig showCardActionConfig) noexcept;

        IFACEMETHODIMP get_ActionMode(_Out_ ABI::AdaptiveCards::Rendering::WinUI3::ActionMode* value);
        IFACEMETHODIMP put_ActionMode(ABI::AdaptiveCards::Rendering::WinUI3::ActionMode value);

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle* style);
        IFACEMETHODIMP put_Style(ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle style);

        IFACEMETHODIMP get_InlineTopMargin(_Out_ UINT32* value);
        IFACEMETHODIMP put_InlineTopMargin(UINT32 value);

    private:
        ABI::AdaptiveCards::Rendering::WinUI3::ActionMode m_actionMode;
        ABI::AdaptiveCards::ObjectModel::WinUI3::ContainerStyle m_containerStyle;
        UINT32 m_inlineTopMargin;
    };

    ActivatableClass(AdaptiveShowCardActionConfig);
}
