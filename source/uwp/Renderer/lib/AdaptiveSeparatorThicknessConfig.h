#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveSeparatorThicknessConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparatorThicknessConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveSeparatorThicknessConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(SeparatorThicknessConfig SeparatorThicknessConfig) noexcept;

        IFACEMETHODIMP get_Default(_Out_ UINT32 *value);
        IFACEMETHODIMP put_Default(_In_ UINT32 value);

        IFACEMETHODIMP get_Thick(_Out_ UINT32 *value);
        IFACEMETHODIMP put_Thick(_In_ UINT32 value);

    private:
        SeparatorThicknessConfig m_sharedSeparatorThicknessConfig;
    };

    ActivatableClass(AdaptiveSeparatorThicknessConfig);
}}