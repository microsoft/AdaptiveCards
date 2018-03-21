#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    class AdaptiveRenderArgs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveRenderArgs>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_Rendering_Uwp_AdaptiveRenderArgs, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(
            ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle containerStyle,
            IInspectable* parentElement,
            ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement* parentAdaptiveElement) noexcept;

        IFACEMETHODIMP get_ContainerStyle(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle *value);
        IFACEMETHODIMP put_ContainerStyle(_In_ ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle value);
        IFACEMETHODIMP get_ParentElement(_COM_Outptr_ IInspectable** value);
        IFACEMETHODIMP put_ParentElement(_In_ IInspectable* value);
        IFACEMETHODIMP get_ParentAdaptiveElement(_COM_Outptr_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement** value);
        IFACEMETHODIMP put_ParentAdaptiveElement(_In_ ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement* value);

    private:
        ABI::AdaptiveCards::Rendering::Uwp::ContainerStyle m_containerStyle;
        Microsoft::WRL::ComPtr<IInspectable> m_parentElement;
        Microsoft::WRL::ComPtr<ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement> m_parentAdaptiveElement;
    };

    ActivatableClass(AdaptiveRenderArgs);
}}}
