// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveTableConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTableConfig>
    {
        AdaptiveRuntime(AdaptiveTableConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(TableConfig tableConfig) noexcept;

        IFACEMETHODIMP get_CellSpacing(UINT32* value) override;
        IFACEMETHODIMP put_CellSpacing(UINT32 value) override;

    private:
        UINT32 m_cellSpacing;
    };
    ActivatableClass(AdaptiveTableConfig);
}
