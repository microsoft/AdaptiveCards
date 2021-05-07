// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveErrorMessageConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveErrorMessageConfig>
    {
        AdaptiveRuntime(AdaptiveErrorMessageConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ErrorMessageConfig errorMessageConfig) noexcept;

        IFACEMETHODIMP get_Size(_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::TextSize* size);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveCards::Rendering::Uwp::TextSize size);

        IFACEMETHODIMP get_Spacing(_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::Rendering::Uwp::Spacing spacing);

        IFACEMETHODIMP get_Weight(_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::TextWeight* weight);
        IFACEMETHODIMP put_Weight(_In_ ABI::AdaptiveCards::Rendering::Uwp::TextWeight weight);

    private:
        ABI::AdaptiveCards::Rendering::Uwp::TextSize m_size;
        ABI::AdaptiveCards::Rendering::Uwp::Spacing m_spacing;
        ABI::AdaptiveCards::Rendering::Uwp::TextWeight m_weight;
    };
    ActivatableClass(AdaptiveErrorMessageConfig);
}
