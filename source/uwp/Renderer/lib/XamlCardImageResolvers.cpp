#include "pch.h"
#include "XamlCardImageResolvers.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT XamlCardImageResolvers::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT XamlCardImageResolvers::Set(HSTRING scheme, IXamlCardImageResolver* resolver)
    {
        m_imageResolvers[scheme] = resolver;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardImageResolvers::Get(HSTRING scheme, IXamlCardImageResolver** resolver)
    {
        *resolver = m_imageResolvers[scheme];
        return S_OK;
    }
}}