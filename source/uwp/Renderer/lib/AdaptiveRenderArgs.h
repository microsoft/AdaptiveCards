#pragma once

#include "AdaptiveCards.Uwp.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveRenderArgs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Uwp::IAdaptiveRenderArgs>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveRenderArgs, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(
            ABI::AdaptiveCards::Uwp::ContainerStyle containerStyle) noexcept;

        IFACEMETHODIMP get_ContainerStyle(_Out_ ABI::AdaptiveCards::Uwp::ContainerStyle *value);
        IFACEMETHODIMP put_ContainerStyle(_In_ ABI::AdaptiveCards::Uwp::ContainerStyle value);


    private:
        ABI::AdaptiveCards::Uwp::ContainerStyle m_containerStyle;
    };

    ActivatableClass(AdaptiveRenderArgs);
}}
#pragma once
