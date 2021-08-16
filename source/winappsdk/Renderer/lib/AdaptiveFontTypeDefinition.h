// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::WinAppSDK
{
    class AdaptiveFontTypeDefinition
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontTypeDefinition>
    {
        AdaptiveRuntime(AdaptiveFontTypeDefinition);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(FontTypeDefinition fontTypeDefinition) noexcept;

        IFACEMETHODIMP get_FontFamily(_Outptr_ HSTRING* value);
        IFACEMETHODIMP put_FontFamily(_In_ HSTRING value);

        IFACEMETHODIMP get_FontWeights(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontWeightsConfig** weightsConfig);
        IFACEMETHODIMP put_FontWeights(_In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontWeightsConfig* weightsConfig);

        IFACEMETHODIMP get_FontSizes(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontSizesConfig** sizesConfig);
        IFACEMETHODIMP put_FontSizes(_In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontSizesConfig* sizesConfig);

    private:
        Microsoft::WRL::Wrappers::HString m_fontFamily;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontWeightsConfig> m_fontWeights;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontSizesConfig> m_fontSizes;
    };

    ActivatableClass(AdaptiveFontTypeDefinition);
}
