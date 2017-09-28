#pragma once

#include "AdaptiveCards.Uwp.h"
#include "Enums.h"
#include "HostConfig.h"

namespace AdaptiveCards { namespace Uwp
{
    class AdaptiveColorsConfig :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Uwp::IAdaptiveColorsConfig>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Uwp_AdaptiveColorsConfig, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;
        HRESULT RuntimeClassInitialize(ColorsConfig colorsConfig) noexcept;

        IFACEMETHODIMP get_Default(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Default(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Accent(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Accent(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Dark(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Dark(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Light(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Light(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Good(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Good(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Warning(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Warning(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* value);

        IFACEMETHODIMP get_Attention(_Out_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig** value);
        IFACEMETHODIMP put_Attention(_In_ ABI::AdaptiveCards::Uwp::IAdaptiveColorConfig* value);

    private:
        ColorsConfig m_sharedColorsConfig;
    };

    ActivatableClass(AdaptiveColorsConfig);
}
}