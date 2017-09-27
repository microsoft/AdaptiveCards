#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveSeparatorConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparatorConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveSeparatorConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(SeparatorConfig SeparatorConfig) noexcept;

        IFACEMETHODIMP get_LineThickness(_Out_ UINT32* value);
        IFACEMETHODIMP put_LineThickness(_In_ UINT32 value);

        IFACEMETHODIMP get_LineColor(_Out_ ABI::Windows::UI::Color* value);
        IFACEMETHODIMP put_LineColor(_In_ ABI::Windows::UI::Color value);

    private:
        SeparatorConfig m_sharedSeparatorConfig;
    };

    ActivatableClass(AdaptiveSeparatorConfig);
}}