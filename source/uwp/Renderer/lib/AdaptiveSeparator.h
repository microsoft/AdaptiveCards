#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "Separator.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveSeparator :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparator>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveSeparator, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(_In_ const std::shared_ptr<AdaptiveCards::Separator>& sharedSeparator);

        // IAdaptiveSeparator
        IFACEMETHODIMP get_Color(_Out_ ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor* color);
        IFACEMETHODIMP put_Color(_In_ ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor color);

        IFACEMETHODIMP get_Thickness(_Out_ ABI::AdaptiveCards::XamlCardRenderer::SeparatorThickness* thickness);
        IFACEMETHODIMP put_Thickness(_In_ ABI::AdaptiveCards::XamlCardRenderer::SeparatorThickness thickness);

    private:
        std::shared_ptr<AdaptiveCards::Separator> m_sharedSeparator;
    };

    ActivatableClass(AdaptiveSeparator);
}}