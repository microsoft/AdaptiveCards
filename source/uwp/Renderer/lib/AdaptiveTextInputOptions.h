#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostOptions.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveTextInputOptions :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveTextInputOptions>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveTextInputOptions, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(TextInputOptions textInputOptions) noexcept;

        IFACEMETHODIMP get_Separation(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions** separationOptions);
        IFACEMETHODIMP put_Separation(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions* separationOptions);

    private:
        TextInputOptions m_sharedTextInputOptions;
    };

    ActivatableClass(AdaptiveTextInputOptions);
}}