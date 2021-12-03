// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveContainerStylesDefinition
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStylesDefinition>
    {
        AdaptiveRuntime(AdaptiveContainerStylesDefinition);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ContainerStylesDefinition stylesDefinition) noexcept;

        IFACEMETHODIMP get_Default(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Default(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Emphasis(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Emphasis(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Good(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Good(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Attention(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Attention(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Warning(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Warning(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Accent(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Accent(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition* value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition> m_default;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition> m_emphasis;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition> m_good;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition> m_attention;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition> m_warning;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition> m_accent;
    };

    ActivatableClass(AdaptiveContainerStylesDefinition);
}
