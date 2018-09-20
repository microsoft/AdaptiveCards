#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "Separator.h"

AdaptiveNamespaceStart
    class AdaptiveSeparator :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveNamespace::IAdaptiveSeparator>
    {
        AdaptiveRuntime(AdaptiveSeparator)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveSharedNamespace::Separator>& sharedSeparator);

        // IAdaptiveSeparator
        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveNamespace::ForegroundColor* color);
        IFACEMETHODIMP put_Color(_In_ ABI::AdaptiveNamespace::ForegroundColor color);

        IFACEMETHODIMP get_Thickness(_Out_ ABI::AdaptiveNamespace::SeparatorThickness* thickness);
        IFACEMETHODIMP put_Thickness(_In_ ABI::AdaptiveNamespace::SeparatorThickness thickness);

    private:
        std::shared_ptr<AdaptiveSharedNamespace::Separator> m_sharedSeparator;
    };

    ActivatableClass(AdaptiveSeparator);
AdaptiveNamespaceEnd