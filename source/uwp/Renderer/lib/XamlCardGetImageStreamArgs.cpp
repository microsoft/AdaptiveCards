#include "pch.h"
#include "XamlCardGetImageStreamArgs.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    _Use_decl_annotations_
    HRESULT XamlCardGetImageStreamArgs::RuntimeClassInitialize(IUriRuntimeClass* url)
    {
        m_url = url;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardGetImageStreamArgs::get_Url(IUriRuntimeClass** url)
    {
        ComPtr<IUriRuntimeClass> localUrl(m_url);
        *url = localUrl.Detach();
        return S_OK;
    }
}}