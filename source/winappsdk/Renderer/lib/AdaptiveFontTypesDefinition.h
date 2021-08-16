// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::WinAppSDK
{
    class AdaptiveFontTypesDefinition
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontTypesDefinition>
    {
        AdaptiveRuntime(AdaptiveFontTypesDefinition);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(FontTypesDefinition fontTypesDefinition) noexcept;

        IFACEMETHODIMP get_Default(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontTypeDefinition** value);
        IFACEMETHODIMP put_Default(_In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontTypeDefinition* value);

        IFACEMETHODIMP get_Monospace(_COM_Outptr_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontTypeDefinition** value);
        IFACEMETHODIMP put_Monospace(_In_ ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontTypeDefinition* value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontTypeDefinition> m_default;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::WinAppSDK::IAdaptiveFontTypeDefinition> m_monospace;
    };

    ActivatableClass(AdaptiveFontTypesDefinition);
}
