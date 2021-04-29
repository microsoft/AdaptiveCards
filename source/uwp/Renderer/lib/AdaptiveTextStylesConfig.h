// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    class AdaptiveTextStylesConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveTextStylesConfig>
    {
        AdaptiveRuntime(AdaptiveTextStylesConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(TextStylesConfig textConfig) noexcept;

        IFACEMETHODIMP get_Heading(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveTextStyleConfig** headingStyle) override;
        IFACEMETHODIMP put_Heading(_In_ ABI::AdaptiveNamespace::IAdaptiveTextStyleConfig* headingStyle) override;

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveTextStyleConfig> m_headingStyle;
    };

    ActivatableClass(AdaptiveTextStylesConfig);
}
