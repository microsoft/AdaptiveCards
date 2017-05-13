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
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_XamlCardRenderer, BaseTrust)

    public:
        XamlCardRenderer();
        HRESULT RuntimeClassInitialize();

        IFACEMETHODIMP SetRenderOptions(_In_ ABI::AdaptiveCards::XamlCardRenderer::RenderOptions options);
        IFACEMETHODIMP SetOverrideStyles(_In_ ABI::Windows::UI::Xaml::IResourceDictionary* overrideDictionary);
        IFACEMETHODIMP RenderCardAsXaml(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* adaptiveCard,
            _COM_Outptr_ ABI::Windows::UI::Xaml::IUIElement** root);
        IFACEMETHODIMP RenderCardAsImage(_In_ ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveCard* adaptiveCard,
            _COM_Outptr_result_maybenull_ ABI::Windows::Foundation::IAsyncOperation<ABI::AdaptiveCards::XamlCardRenderer::ImageRenderResult*>** result);
    };

    ActivatableClass(XamlCardRenderer);
}}