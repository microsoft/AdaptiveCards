#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

AdaptiveNamespaceStart
    class AdaptiveRenderArgs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveNamespace::IAdaptiveRenderArgs>
    {
        AdaptiveRuntime(AdaptiveRenderArgs)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(
            ABI::AdaptiveNamespace::ContainerStyle containerStyle,
            IInspectable* parentElement) noexcept;

        IFACEMETHODIMP get_ContainerStyle(_Out_ ABI::AdaptiveNamespace::ContainerStyle *value);
        IFACEMETHODIMP put_ContainerStyle(_In_ ABI::AdaptiveNamespace::ContainerStyle value);
        IFACEMETHODIMP get_ParentElement(_COM_Outptr_ IInspectable** value);
        IFACEMETHODIMP put_ParentElement(_In_ IInspectable* value);

    private:
        ABI::AdaptiveNamespace::ContainerStyle m_containerStyle;
        Microsoft::WRL::ComPtr<IInspectable> m_parentElement;
    };

    ActivatableClass(AdaptiveRenderArgs);
AdaptiveNamespaceEnd
