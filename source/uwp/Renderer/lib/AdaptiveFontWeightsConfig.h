#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveFontWeightsConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveFontWeightsConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveFontWeightsConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(FontWeightsConfig fontWeightsConfig) noexcept;

        IFACEMETHODIMP get_Lighter(_Out_ UINT16 *value);
        IFACEMETHODIMP put_Lighter(_In_ UINT16 value);

        IFACEMETHODIMP get_Default(_Out_ UINT16 *value);
        IFACEMETHODIMP put_Default(_In_ UINT16 value);

        IFACEMETHODIMP get_Bolder(_Out_ UINT16 *value);
        IFACEMETHODIMP put_Bolder(_In_ UINT16 value);

    private:
        FontWeightsConfig m_sharedFontWeightsConfig;
    };

    ActivatableClass(AdaptiveFontWeightsConfig);
}}