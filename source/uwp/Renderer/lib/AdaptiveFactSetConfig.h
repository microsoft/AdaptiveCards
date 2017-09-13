#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveFactSetConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFactSetConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveFactSetConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(FactSetConfig factSetConfig) noexcept;

        IFACEMETHODIMP get_Title(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig** titleTextConfig);
        IFACEMETHODIMP put_Title(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig* titleTextConfig);

        IFACEMETHODIMP get_Value(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig** valueTextConfig);
        IFACEMETHODIMP put_Value(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextConfig* valueTextConfig);

        IFACEMETHODIMP get_Spacing(_Out_ UINT32 *value);
        IFACEMETHODIMP put_Spacing(_In_ UINT32 value);

    private:
        FactSetConfig m_sharedFactSetConfig;
    };

    ActivatableClass(AdaptiveFactSetConfig);
}}