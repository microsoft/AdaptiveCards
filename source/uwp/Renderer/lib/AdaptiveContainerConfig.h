#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class AdaptiveContainerConfig :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_AdaptiveContainerConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ContainerConfig containerConfig) noexcept;

        IFACEMETHODIMP get_Normal(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleConfig** containerStyleconfig);
        IFACEMETHODIMP put_Normal(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleConfig* containerStyleconfig);

        IFACEMETHODIMP get_Emphasis(_Out_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleConfig** containerStyleconfig);
        IFACEMETHODIMP put_Emphasis(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveContainerStyleConfig* containerStyleconfig);

    private:
        ContainerConfig m_sharedContainerConfig;
    };

    ActivatableClass(AdaptiveContainerConfig);
}}