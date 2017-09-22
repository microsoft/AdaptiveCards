#include "pch.h"
#include "XamlCardGetResourceStreamArgs.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    _Use_decl_annotations_
    HRESULT XamlCardGetResourceStreamArgs::RuntimeClassInitialize(IUriRuntimeClass* url)
    {
        m_url = url;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardGetResourceStreamArgs::get_Url(IUriRuntimeClass** url)
    {
        ComPtr<IUriRuntimeClass> localUrl(m_url);
        *url = localUrl.Detach();
        return S_OK;
    }
}}