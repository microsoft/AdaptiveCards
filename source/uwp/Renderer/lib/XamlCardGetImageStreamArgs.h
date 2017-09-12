#pragma once
#include "AdaptiveCards.XamlCardRenderer.h"

namespace AdaptiveCards { namespace XamlCardRenderer
{
    class XamlCardGetImageStreamArgs :
        public Microsoft::WRL::RuntimeClass<
        Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::RuntimeClassType::WinRt>,
        ABI::AdaptiveCards::XamlCardRenderer::IXamlCardGetImageStreamArgs>
    {
        InspectableClass(RuntimeClass_AdaptiveCards_XamlCardRenderer_XamlCardGetImageStreamArgs, BaseTrust)

    public:
        HRESULT RuntimeClassInitialize(_In_ ABI::Windows::Foundation::IUriRuntimeClass* url);

        IFACEMETHODIMP get_Url(_Outptr_ ABI::Windows::Foundation::IUriRuntimeClass** url);

    private:
        Microsoft::WRL::ComPtr<ABI::Windows::Foundation::IUriRuntimeClass> m_url;
    };
}}