#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostOptions.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveShowCardOptions :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveShowCardOptions>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveShowCardOptions, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::ShowCardOptions showCardOptions) noexcept;

        IFACEMETHODIMP get_ActionMode(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ActionMode* value);
        IFACEMETHODIMP put_ActionMode(_In_ ABI::AdaptiveCards::XamlCardRenderer::ActionMode value);

        IFACEMETHODIMP get_BackgroundColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_BackgroundColor(_In_ ABI::Windows::UI::Color value);

        IFACEMETHODIMP get_Padding(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveBoundaryOptions** value);
        IFACEMETHODIMP put_Padding(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveBoundaryOptions* value);

        IFACEMETHODIMP get_InlineTopMargin(_Out_ UINT32* value);
        IFACEMETHODIMP put_InlineTopMargin(_In_ UINT32 value);

    private:
        AdaptiveCards::ShowCardOptions m_sharedShowCardOptions;
    };

    ActivatableClass(AdaptiveShowCardOptions);
}
}