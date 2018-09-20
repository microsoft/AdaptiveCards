#include "pch.h"
#include "AdaptiveCardResourceResolvers.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation;

AdaptiveNamespaceStart
    HRESULT AdaptiveCardResourceResolvers::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveCardResourceResolvers::Set(HSTRING scheme, IAdaptiveCardResourceResolver* resolver)
    {
        std::string schemeString;
        RETURN_IF_FAILED(HStringToUTF8(scheme, schemeString));
        m_resourceResolvers[schemeString] = resolver;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveCardResourceResolvers::Get(HSTRING scheme, IAdaptiveCardResourceResolver** resolver)
    {
        std::string schemeString;
        RETURN_IF_FAILED(HStringToUTF8(scheme, schemeString));
        ComPtr<IAdaptiveCardResourceResolver> resolverPtr = m_resourceResolvers[schemeString];
        return resolverPtr.CopyTo(resolver);
    }
AdaptiveNamespaceEnd