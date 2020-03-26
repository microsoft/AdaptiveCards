// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "Separator.h"

namespace AdaptiveNamespace
{
    class AdaptiveSeparator
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveSeparator>
    {
        AdaptiveRuntime(AdaptiveSeparator);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::Separator>& sharedSeparator);

        // IAdaptiveSeparator
        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveNamespace::ForegroundColor* color);
        IFACEMETHODIMP put_Color(ABI::AdaptiveNamespace::ForegroundColor color);

        IFACEMETHODIMP get_Thickness(_Out_ ABI::AdaptiveNamespace::SeparatorThickness* thickness);
        IFACEMETHODIMP put_Thickness(ABI::AdaptiveNamespace::SeparatorThickness thickness);

    private:
        std::shared_ptr<AdaptiveSharedNamespace::Separator> m_sharedSeparator;
    };

    ActivatableClass(AdaptiveSeparator);
}
