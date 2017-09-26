#include "pch.h"
#include "XamlCardResourceResolvers.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT XamlCardResourceResolvers::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT XamlCardResourceResolvers::Set(HSTRING scheme, IXamlCardResourceResolver* resolver)
    {
        std::string schemeString;
        RETURN_IF_FAILED(HStringToUTF8(scheme, schemeString));
        m_resourceResolvers[schemeString] = resolver;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT XamlCardResourceResolvers::Get(HSTRING scheme, IXamlCardResourceResolver** resolver)
    {
        std::string schemeString;
        RETURN_IF_FAILED(HStringToUTF8(scheme, schemeString));
        ComPtr<IXamlCardResourceResolver> resolverPtr = m_resourceResolvers[schemeString];
        ComPtr<IXamlCardResourceResolver> localResolver(resolverPtr);
        *resolver = localResolver.Detach();
        return S_OK;
    }
}}