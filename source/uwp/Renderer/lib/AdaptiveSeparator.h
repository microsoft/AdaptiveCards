// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Separator.h"

namespace AdaptiveCards::Rendering::Uwp
{
    class AdaptiveSeparator
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
                                              ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveSeparator>
    {
        AdaptiveRuntime(AdaptiveSeparator);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::Separator>& sharedSeparator);

        // IAdaptiveSeparator
        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor* color);
        IFACEMETHODIMP put_Color(ABI::AdaptiveCards::Rendering::Uwp::ForegroundColor color);

        IFACEMETHODIMP get_Thickness(_Out_ ABI::AdaptiveCards::Rendering::Uwp::SeparatorThickness* thickness);
        IFACEMETHODIMP put_Thickness(ABI::AdaptiveCards::Rendering::Uwp::SeparatorThickness thickness);

    private:
        std::shared_ptr<AdaptiveCards::Separator> m_sharedSeparator;
    };

    ActivatableClass(AdaptiveSeparator);
}
