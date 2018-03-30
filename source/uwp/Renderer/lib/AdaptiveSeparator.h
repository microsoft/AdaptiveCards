#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Separator.h"

AdaptiveNamespaceStart
    class AdaptiveSeparator :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespaceRef::IAdaptiveSeparator>
    {
        AdaptiveRuntime(AdaptiveSeparator)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::Separator>& sharedSeparator);

        // IAdaptiveSeparator
        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveNamespaceRef::ForegroundColor* color);
        IFACEMETHODIMP put_Color(_In_ ABI::AdaptiveNamespaceRef::ForegroundColor color);

        IFACEMETHODIMP get_Thickness(_Out_ ABI::AdaptiveNamespaceRef::SeparatorThickness* thickness);
        IFACEMETHODIMP put_Thickness(_In_ ABI::AdaptiveNamespaceRef::SeparatorThickness thickness);

    private:
        std::shared_ptr<AdaptiveCards::Separator> m_sharedSeparator;
    };

    ActivatableClass(AdaptiveSeparator);
AdaptiveNamespaceEnd