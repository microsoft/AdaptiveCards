#pragma once
#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class XamlCardResourceResolvers :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IXamlCardResourceResolvers>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_XamlCardResourceResolvers, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING scheme, _In_ ABI::AdaptiveCards::XamlCardRenderer::IXamlCardResourceResolver* resolver);
        IFACEMETHODIMP Get(_In_ HSTRING scheme, _Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IXamlCardResourceResolver** resolver);

    private:
        std::map<std::string, Microsoft::WRL::ComPtr<ABI::AdaptiveCards::XamlCardRenderer::IXamlCardResourceResolver>> m_resourceResolvers;
    };

    ActivatableClass(XamlCardResourceResolvers);
}}