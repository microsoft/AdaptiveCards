// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveHeadingsConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveHeadingsConfig>
    {
        AdaptiveRuntime(AdaptiveHeadingsConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(HeadingsConfig headingsConfig) noexcept;

        IFACEMETHODIMP get_Level(UINT32* value) override;
        IFACEMETHODIMP put_Level(UINT32 value) override;

    private:
        UINT32 m_level;
    };
    ActivatableClass(AdaptiveHeadingsConfig);
}
