// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    class AdaptiveContainerStylesDefinition
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveContainerStylesDefinition>
    {
        AdaptiveRuntime(AdaptiveContainerStylesDefinition);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ContainerStylesDefinition stylesDefinition) noexcept;

        IFACEMETHODIMP get_Default(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Default(_In_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Emphasis(_COM_Outptr_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Emphasis(_In_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Good(_Out_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Good(_In_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Attention(_Out_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Attention(_In_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Warning(_Out_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Warning(_In_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Accent(_Out_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Accent(_In_ ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition* value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition> m_default;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition> m_emphasis;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition> m_good;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition> m_attention;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition> m_warning;
        Microsoft::WRL::ComPtr<ABI::AdaptiveNamespace::IAdaptiveContainerStyleDefinition> m_accent;
    };

    ActivatableClass(AdaptiveContainerStylesDefinition);
}
