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
        std::string schemeString;
        RETURN_IF_FAILED(HStringToUTF8(scheme, schemeString));
        m_imageResolvers[schemeString] = resolver;
        /*ComPtr<IXamlCardImageResolver> localResolver(resolver);
        m_imageResolvers[scheme] = localResolver;*/
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardImageResolvers::Get(HSTRING scheme, IXamlCardImageResolver** resolver)
    {
        std::string schemeString;
        RETURN_IF_FAILED(HStringToUTF8(scheme, schemeString));
        //*resolver = m_imageResolvers[scheme];
        ComPtr<IXamlCardImageResolver> resolverPtr = m_imageResolvers[schemeString];
        ComPtr<IXamlCardImageResolver> localResolver(resolverPtr);
        *resolver = localResolver.Detach();
        return S_OK;
    }
}}