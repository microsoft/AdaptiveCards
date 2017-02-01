#pragma once

#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    // This class is effectively a singleton, and stays around between subsequent renders.
    class XamlCardRenderer :
        public Microsoft::WRL::RuntimeClass<
            Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRtClassicComMix>,
            Microsoft::WRL::FtmBase,
            ABI::AdaptiveCards::XamlCardRenderer::IXamlCardRenderer>
    {
        InspectableClass(L"AdaptiveCards.XamlCardRenderer", BaseTrust)

    public:
        XamlCardRenderer();
        HRESULT RuntimeClassInitialize();

        IFACEMETHODIMP RenderCardAsXaml(ABI::Windows::UI::Xaml::IUIElement** root);
        IFACEMETHODIMP RenderCardAsImage();

    };

    ActivatableClass(XamlCardRenderer);
}}