#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostOptions.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveFactSetOptions :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFactSetOptions>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveFactSetOptions, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(FactSetOptions factSetOptions) noexcept;

        IFACEMETHODIMP get_Title(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextOptions** titleTextOptions);
        IFACEMETHODIMP put_Title(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextOptions* titleTextOptions);

        IFACEMETHODIMP get_Value(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextOptions** valueTextOptions);
        IFACEMETHODIMP put_Value(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextOptions* valueTextOptions);

        IFACEMETHODIMP get_Spacing(_Out_ INT32 *value);
        IFACEMETHODIMP put_Spacing(_In_ INT32 value);

        IFACEMETHODIMP get_Separation(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions** separationOptions);
        IFACEMETHODIMP put_Separation(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions* separationOptions);

    private:
        FactSetOptions m_sharedFactSetOptions;
    };

    ActivatableClass(AdaptiveFactSetOptions);
}}