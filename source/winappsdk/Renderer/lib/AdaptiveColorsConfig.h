// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveColorsConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorsConfig>
    {
        AdaptiveRuntime(AdaptiveColorsConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ColorsConfig colorsConfig) noexcept;

        IFACEMETHODIMP get_Default(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Default(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Accent(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Accent(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Dark(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Dark(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Light(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Light(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Good(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Good(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Warning(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Warning(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Attention(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Attention(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig* value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig> m_default;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig> m_accent;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig> m_dark;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig> m_light;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig> m_good;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig> m_warning;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveColorConfig> m_attention;
    };

    ActivatableClass(AdaptiveColorsConfig);
}
