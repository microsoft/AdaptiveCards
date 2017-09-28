#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveContainerStylesDefinition :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            ABI::AdaptiveCards::Uwp::IAdaptiveContainerStylesDefinition>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveContainerStylesDefinition, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ContainerStylesDefinition stylesDefinition) noexcept;

        IFACEMETHODIMP get_Default(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Default(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition* value);

        IFACEMETHODIMP get_Emphasis(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition** value);
        IFACEMETHODIMP put_Emphasis(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveContainerStyleDefinition* value);

    private:
        ContainerStylesDefinition m_sharedContainerStylesDefinition;
    };

    ActivatableClass(AdaptiveContainerStylesDefinition);
}}