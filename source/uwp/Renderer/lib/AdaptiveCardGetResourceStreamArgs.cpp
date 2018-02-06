#include "pch.h"
#include "AdaptiveCardGetResourceStreamArgs.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{
    _Use_decl_annotations_
    HRESULT AdaptiveCardGetResourceStreamArgs::RuntimeClassInitialize(IUriRuntimeClass* url)
    {
        m_url = url;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardGetResourceStreamArgs::get_Url(IUriRuntimeClass** url)
    {
        ComPtr<IUriRuntimeClass> localUrl(m_url);
        *url = localUrl.Detach();
        return S_OK;
    }
}}}
