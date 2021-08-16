// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

namespace AdaptiveCards::Rendering::WinUI3
{
    class AdaptiveErrorMessageConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::WinUI3::IAdaptiveErrorMessageConfig>
    {
        AdaptiveRuntime(AdaptiveErrorMessageConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ErrorMessageConfig errorMessageConfig) noexcept;

        IFACEMETHODIMP get_Size(_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize* size);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize size);

        IFACEMETHODIMP get_Spacing(_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing* spacing);
        IFACEMETHODIMP put_Spacing(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing spacing);

        IFACEMETHODIMP get_Weight(_Outptr_ ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight* weight);
        IFACEMETHODIMP put_Weight(_In_ ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight weight);

    private:
        ABI::AdaptiveCards::ObjectModel::WinUI3::TextSize m_size;
        ABI::AdaptiveCards::ObjectModel::WinUI3::Spacing m_spacing;
        ABI::AdaptiveCards::ObjectModel::WinUI3::TextWeight m_weight;
    };
    ActivatableClass(AdaptiveErrorMessageConfig);
}
