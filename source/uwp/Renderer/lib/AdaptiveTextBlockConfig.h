// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveTextBlockConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveTextBlockConfig>
    {
        AdaptiveRuntime(AdaptiveTextBlockConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(TextBlockConfig headingLevelsConfig) noexcept;

        IFACEMETHODIMP get_HeadingLevel(UINT32* value) override;
        IFACEMETHODIMP put_HeadingLevel(UINT32 value) override;

    private:
        UINT32 m_headingLevel;
    };
    ActivatableClass(AdaptiveTextBlockConfig);
}
