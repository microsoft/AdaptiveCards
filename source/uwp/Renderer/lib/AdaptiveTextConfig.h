// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveNamespace
{
    class AdaptiveTextConfig
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveTextConfig>
    {
        AdaptiveRuntime(AdaptiveTextConfig);

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(TextConfig textConfig) noexcept;

        IFACEMETHODIMP get_Weight(_Out_ ABI::AdaptiveNamespace::TextWeight* textWeight);
        IFACEMETHODIMP put_Weight(ABI::AdaptiveNamespace::TextWeight textWeight);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveNamespace::TextSize* textSize);
        IFACEMETHODIMP put_Size(ABI::AdaptiveNamespace::TextSize textSize);

        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveNamespace::ForegroundColor* textColor);
        IFACEMETHODIMP put_Color(ABI::AdaptiveNamespace::ForegroundColor textColor);

        IFACEMETHODIMP get_IsSubtle(_Out_ boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(boolean isSubtle);

        IFACEMETHODIMP get_Wrap(_Out_ boolean* wrap);
        IFACEMETHODIMP put_Wrap(boolean wrap);

        IFACEMETHODIMP get_MaxWidth(_Out_ UINT32* maxWidth);
        IFACEMETHODIMP put_MaxWidth(UINT32 maxWidth);

    private:
        ABI::AdaptiveNamespace::TextWeight m_textWeight;
        ABI::AdaptiveNamespace::TextSize m_textSize;
        ABI::AdaptiveNamespace::ForegroundColor m_textColor;
        boolean m_isSubtle;
        boolean m_wrap;
        UINT32 m_maxWidth;
    };

    ActivatableClass(AdaptiveTextConfig);
}
