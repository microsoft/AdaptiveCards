// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveNamespace
{
    class AdaptiveInputLabelConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveInputLabelConfig>
    {
        AdaptiveRuntime(AdaptiveInputLabelConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(InputLabelConfig inputLabelConfig) noexcept;

        IFACEMETHODIMP get_Color(_Outptr_ ABI::AdaptiveNamespace::ForegroundColor* color);
        IFACEMETHODIMP put_Color(_In_ ABI::AdaptiveNamespace::ForegroundColor color);

        IFACEMETHODIMP get_Size(_Outptr_ ABI::AdaptiveNamespace::TextSize* size);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveNamespace::TextSize size);

        IFACEMETHODIMP get_Spacing(_Outptr_ ABI::AdaptiveNamespace::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveNamespace::Spacing spacing);

        IFACEMETHODIMP get_Suffix(_Outptr_ HSTRING* suffix);
        IFACEMETHODIMP put_Suffix(_In_ HSTRING suffix);

    private:
        ABI::AdaptiveNamespace::ForegroundColor m_color;
        ABI::AdaptiveNamespace::TextSize m_size;
        ABI::AdaptiveNamespace::Spacing m_spacing;
        Microsoft::WRL::Wrappers::HString m_suffix;

    };
    ActivatableClass(AdaptiveInputLabelConfig);
}
