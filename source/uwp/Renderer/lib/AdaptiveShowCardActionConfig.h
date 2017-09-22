#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveShowCardActionConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveShowCardActionConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveShowCardActionConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(AdaptiveCards::ShowCardActionConfig showCardActionConfig) noexcept;

        IFACEMETHODIMP get_ActionMode(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ActionMode* value);
        IFACEMETHODIMP put_ActionMode(_In_ ABI::AdaptiveCards::XamlCardRenderer::ActionMode value);

        IFACEMETHODIMP get_Style(_Out_ ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle* style);
        IFACEMETHODIMP put_Style(_In_ ABI::AdaptiveCards::XamlCardRenderer::ContainerStyle style);

        IFACEMETHODIMP get_Padding(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingDefinition** value);
        IFACEMETHODIMP put_Padding(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSpacingDefinition* value);

        IFACEMETHODIMP get_InlineTopMargin(_Out_ UINT32* value);
        IFACEMETHODIMP put_InlineTopMargin(_In_ UINT32 value);

    private:
        AdaptiveCards::ShowCardActionConfig m_sharedShowCardActionConfig;
    };

    ActivatableClass(AdaptiveShowCardActionConfig);
}
}