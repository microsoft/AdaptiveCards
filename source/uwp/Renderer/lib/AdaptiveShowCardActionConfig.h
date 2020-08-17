// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    class AdaptiveShowCardActionConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveShowCardActionConfig>
    {
        AdaptiveRuntime(AdaptiveShowCardActionConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveSharedNamespace::ShowCardActionConfig showCardActionConfig) noexcept;

        IFACEMETHODIMP get_ActionMode(_Out_ ABI::AdaptiveNamespace::ActionMode* value);
        IFACEMETHODIMP put_ActionMode(ABI::AdaptiveNamespace::ActionMode value);

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveNamespace::ContainerStyle* style);
        IFACEMETHODIMP put_Style(ABI::AdaptiveNamespace::ContainerStyle style);

        IFACEMETHODIMP get_InlineTopMargin(_Out_ UINT32* value);
        IFACEMETHODIMP put_InlineTopMargin(UINT32 value);

    private:
        ABI::AdaptiveNamespace::ActionMode m_actionMode;
        ABI::AdaptiveNamespace::ContainerStyle m_containerStyle;
        UINT32 m_inlineTopMargin;
    };

    ActivatableClass(AdaptiveShowCardActionConfig);
}
