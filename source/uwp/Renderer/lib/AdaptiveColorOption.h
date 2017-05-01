#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostOptions.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveColorOption :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveColorOption, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ColorOption colorOption) noexcept;

        IFACEMETHODIMP get_Normal(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_Normal(_In_ ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_Subtle(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_Subtle(_In_ ABI::Windows::UI::Color value);

    private:
        ColorOption m_sharedColorOption;
    };

    ActivatableClass(AdaptiveColorOption);
}
}