#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostOptions.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveSeparationOptions :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveSeparationOptions, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(SeparationOptions separationOptions) noexcept;

        IFACEMETHODIMP get_Spacing(_Out_ INT32* value);
        IFACEMETHODIMP put_Spacing(_In_ INT32 value);

        IFACEMETHODIMP get_LineThickness(_Out_ INT32* value);
        IFACEMETHODIMP put_LineThickness(_In_ INT32 value);

        IFACEMETHODIMP get_LineColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_LineColor(_In_ ABI::Windows::UI::Color value);

    private:
        SeparationOptions m_sharedSeparationOptions;
    };

    ActivatableClass(AdaptiveSeparationOptions);
}
}