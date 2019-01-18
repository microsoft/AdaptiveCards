#pragma once

#include "AdaptiveCards.Rendering.Uwp.h"

namespace AdaptiveNamespace
{
    class AdaptiveRenderArgs
        : public Microsoft::WRL::RuntimeClass<Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>, ABI::AdaptiveNamespace::IAdaptiveRenderArgs>
    {
        AdaptiveRuntime(AdaptiveRenderArgs);

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        HRESULT RuntimeClassInitialize(ABI::AdaptiveNamespace::ContainerStyle containerStyle, _In_ IInspectable* parentElement) noexcept;

        IFACEMETHODIMP get_ContainerStyle(_Out_ ABI::AdaptiveNamespace::ContainerStyle* value);
        IFACEMETHODIMP put_ContainerStyle(ABI::AdaptiveNamespace::ContainerStyle value);
        IFACEMETHODIMP get_ParentElement(_COM_Outptr_ IInspectable** value);
        IFACEMETHODIMP put_ParentElement(_In_ IInspectable* value);
        IFACEMETHODIMP get_AncestorHasFallback(_Out_ boolean* hasFallback);
        IFACEMETHODIMP put_AncestorHasFallback(boolean hasFallback);

    private:
        ABI::AdaptiveNamespace::ContainerStyle m_containerStyle;
        Microsoft::WRL::ComPtr<IInspectable> m_parentElement;
        boolean m_ancestorHasFallback;
    };

    ActivatableClass(AdaptiveRenderArgs);
}
