#pragma once
#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class XamlCardImageResolvers :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
        ABI::AdaptiveCards::XamlCardRenderer::IXamlCardImageResolvers>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_XamlCardImageResolvers, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize() noexcept;

        IFACEMETHODIMP Set(_In_ HSTRING scheme, _In_ ABI::AdaptiveCards::XamlCardRenderer::IXamlCardImageResolver* resolver);
        IFACEMETHODIMP Get(_In_ HSTRING scheme, _Outptr_ ABI::AdaptiveCards::XamlCardRenderer::IXamlCardImageResolver** resolver);

    private:
        std::map<HSTRING, ABI::AdaptiveCards::XamlCardRenderer::IXamlCardImageResolver*> m_imageResolvers;
    };

    ActivatableClass(XamlCardImageResolvers);
}}