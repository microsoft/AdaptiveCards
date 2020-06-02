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

        IFACEMETHODIMP get_IsSubtle(_Outptr_ boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(_In_ boolean isSubtle);

        IFACEMETHODIMP get_Size(_Outptr_ ABI::AdaptiveNamespace::TextSize* size);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveNamespace::TextSize size);

        IFACEMETHODIMP get_Weight(_Outptr_ ABI::AdaptiveNamespace::TextWeight* weight);
        IFACEMETHODIMP put_Weight(_In_ ABI::AdaptiveNamespace::TextWeight weight);

    private:
        ABI::AdaptiveNamespace::ForegroundColor m_color;
        boolean m_isSubtle;
        ABI::AdaptiveNamespace::TextSize m_size;
        ABI::AdaptiveNamespace::TextWeight m_weight;

    };
    ActivatableClass(AdaptiveInputLabelConfig);
}
