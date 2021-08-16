// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveFactSetConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFactSetConfig>
    {
        AdaptiveRuntime(AdaptiveFactSetConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(FactSetConfig factSetConfig) noexcept;

        IFACEMETHODIMP get_Title(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFactSetTextConfig** titleTextConfig);
        IFACEMETHODIMP put_Title(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFactSetTextConfig* titleTextConfig);

        IFACEMETHODIMP get_Value(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFactSetTextConfig** valueTextConfig);
        IFACEMETHODIMP put_Value(_In_ ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFactSetTextConfig* valueTextConfig);

        IFACEMETHODIMP get_Spacing(_Out_ UINT32* value);
        IFACEMETHODIMP put_Spacing(UINT32 value);

    private:
        UINT m_spacing;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFactSetTextConfig> m_title;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveFactSetTextConfig> m_value;
    };

    ActivatableClass(AdaptiveFactSetConfig);
}
