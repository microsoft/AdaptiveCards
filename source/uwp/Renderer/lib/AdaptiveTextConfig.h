#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

AdaptiveNamespaceStart
    class AdaptiveTextConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespaceRef::IAdaptiveTextConfig>
    {
        AdaptiveRuntime(AdaptiveTextConfig)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(TextConfig textConfig) noexcept;

        IFACEMETHODIMP get_Weight(_Out_ ABI::AdaptiveNamespaceRef::TextWeight* textWeight);
        IFACEMETHODIMP put_Weight(_In_ ABI::AdaptiveNamespaceRef::TextWeight textWeight);

        IFACEMETHODIMP get_Size(_Out_ ABI::AdaptiveNamespaceRef::TextSize* textSize);
        IFACEMETHODIMP put_Size(_In_ ABI::AdaptiveNamespaceRef::TextSize textSize);

        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveNamespaceRef::ForegroundColor* textColor);
        IFACEMETHODIMP put_Color(_In_ ABI::AdaptiveNamespaceRef::ForegroundColor textColor);

        IFACEMETHODIMP get_IsSubtle(_Out_ boolean* isSubtle);
        IFACEMETHODIMP put_IsSubtle(_In_ boolean isSubtle);

        IFACEMETHODIMP get_Wrap(_Out_ boolean* wrap);
        IFACEMETHODIMP put_Wrap(_In_ boolean wrap);

        IFACEMETHODIMP get_MaxWidth(_Out_ UINT32* maxWidth);
        IFACEMETHODIMP put_MaxWidth(_In_ UINT32 maxWidth);

    private:
        ABI::AdaptiveNamespaceRef::TextWeight m_textWeight;
        ABI::AdaptiveNamespaceRef::TextSize m_textSize;
        ABI::AdaptiveNamespaceRef::ForegroundColor m_textColor;
        boolean m_isSubtle;
        boolean m_wrap;
        UINT32 m_maxWidth;
    };

    ActivatableClass(AdaptiveTextConfig);
AdaptiveNamespaceEnd
