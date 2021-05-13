// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveCardConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardConfig>
    {
        AdaptiveRuntime(AdaptiveCardConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::AdaptiveCardConfig adaptiveCardConfig) noexcept;

        IFACEMETHODIMP get_AllowCustomStyle(_Out_ boolean* allowCustomStyle);
        IFACEMETHODIMP put_AllowCustomStyle(boolean allowCustomStyle);

    private:
        boolean m_allowCustomStyle;
    };

    ActivatableClass(AdaptiveCardConfig);
}
