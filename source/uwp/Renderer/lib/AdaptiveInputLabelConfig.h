// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveInputLabelConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveInputLabelConfig>
    {
        AdaptiveRuntime(AdaptiveInputLabelConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(InputLabelConfig inputLabelConfig) noexcept;

        IFACEMETHODIMP get_Color(_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::ForegroundColor* color);
        IFACEMETHODIMP put_Color(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::ForegroundColor color);

        IFACEMETHODIMP get_IsSubtle(_Outptr_ boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(_In_ boolean isSubtle);

        IFACEMETHODIMP get_Size(_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::TextSize* size);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::TextSize size);

        IFACEMETHODIMP get_Suffix(_Outptr_ HSTRING* suffix);
        IFACEMETHODIMP put_Suffix(_In_ HSTRING suffix);

        IFACEMETHODIMP get_Weight(_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight* weight);
        IFACEMETHODIMP put_Weight(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight weight);

    private:
        ABI::AdaptiveCards::ObjectModel::Uwp::ForegroundColor m_color;
        boolean m_isSubtle;
        ABI::AdaptiveCards::ObjectModel::Uwp::TextSize m_size;
        Microsoft::WRL::Wrappers::HString m_suffix;
        ABI::AdaptiveCards::ObjectModel::Uwp::TextWeight m_weight;
    };
    ActivatableClass(AdaptiveInputLabelConfig);
}
