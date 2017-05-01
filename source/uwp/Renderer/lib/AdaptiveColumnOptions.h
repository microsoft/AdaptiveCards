#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostOptions.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveColumnOptions :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColumnOptions>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveColumnOptions, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ColumnOptions columnOptions) noexcept;

        IFACEMETHODIMP get_DefaultSeparation(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions** separationOptions);
        IFACEMETHODIMP put_DefaultSeparation(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions* separationOptions);

        IFACEMETHODIMP get_StrongSeparation(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions** separationOptions);
        IFACEMETHODIMP put_StrongSeparation(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveSeparationOptions* separationOptions);

    private:
        ColumnOptions m_sharedColumnOptions;
    };

    ActivatableClass(AdaptiveColumnOptions);
}}