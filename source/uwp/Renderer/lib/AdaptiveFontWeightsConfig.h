// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveFontWeightsConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveFontWeightsConfig>
    {
        AdaptiveRuntime(AdaptiveFontWeightsConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(FontWeightsConfig fontWeightsConfig) noexcept;

        IFACEMETHODIMP get_Lighter(_Out_ UINT16* value);
        IFACEMETHODIMP put_Lighter(UINT16 value);

        IFACEMETHODIMP get_Default(_Out_ UINT16* value);
        IFACEMETHODIMP put_Default(UINT16 value);

        IFACEMETHODIMP get_Bolder(_Out_ UINT16* value);
        IFACEMETHODIMP put_Bolder(UINT16 value);

    private:
        UINT16 m_default;
        UINT16 m_lighter;
        UINT16 m_bolder;
    };

    ActivatableClass(AdaptiveFontWeightsConfig);
}
