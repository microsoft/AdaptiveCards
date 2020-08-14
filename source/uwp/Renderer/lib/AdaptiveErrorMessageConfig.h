// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    class AdaptiveErrorMessageConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveErrorMessageConfig>
    {
        AdaptiveRuntime(AdaptiveErrorMessageConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ErrorMessageConfig errorMessageConfig) noexcept;

        IFACEMETHODIMP get_Size(_Outptr_ ABI::AdaptiveNamespace::TextSize* size);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveNamespace::TextSize size);

        IFACEMETHODIMP get_Spacing(_Outptr_ ABI::AdaptiveNamespace::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveNamespace::Spacing spacing);

        IFACEMETHODIMP get_Weight(_Outptr_ ABI::AdaptiveNamespace::TextWeight* weight);
        IFACEMETHODIMP put_Weight(_In_ ABI::AdaptiveNamespace::TextWeight weight);

    private:
        ABI::AdaptiveNamespace::TextSize m_size;
        ABI::AdaptiveNamespace::Spacing m_spacing;
        ABI::AdaptiveNamespace::TextWeight m_weight;

    };
    ActivatableClass(AdaptiveErrorMessageConfig);
}
