#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class AdaptiveContainerStylesDefinition :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStylesDefinition>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveContainerStylesDefinition, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ContainerStylesDefinition stylesDefinition) noexcept;

        IFACEMETHODIMP get_Default(_Out_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Default(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Emphasis(_Out_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Emphasis(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition* value);

    private:
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition> m_default;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveContainerStyleDefinition> m_emphasis;
    };

    ActivatableClass(AdaptiveContainerStylesDefinition);
}}}