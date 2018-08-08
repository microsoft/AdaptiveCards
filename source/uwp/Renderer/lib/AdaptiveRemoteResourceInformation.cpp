#include "pch.h"
#include "AdaptiveRemoteResourceInformation.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

AdaptiveNamespaceStart
    HRESULT AdaptiveRemoteResourceInformation::RuntimeClassInitialize() noexcept try
    {
        RemoteResourceInformation uriInformation;
        return RuntimeClassInitialize(uriInformation);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveRemoteResourceInformation::RuntimeClassInitialize(RemoteResourceInformation& uriInformation) try
    {
        RETURN_IF_FAILED(UTF8ToHString(uriInformation.url, m_url.GetAddressOf()));
        RETURN_IF_FAILED(UTF8ToHString(uriInformation.mimeType, m_mimeType.GetAddressOf()));
        m_urlType = static_cast<ABI::AdaptiveNamespace::ElementType>(uriInformation.resourceType);

        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveRemoteResourceInformation::get_Url(HSTRING* url)
    {
        return m_url.CopyTo(url);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRemoteResourceInformation::put_Url(HSTRING url)
    {
        return m_url.Set(url);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRemoteResourceInformation::get_MimeType(HSTRING* mimeType)
    {
        return m_mimeType.CopyTo(mimeType);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRemoteResourceInformation::put_MimeType(HSTRING mimeType)
    {
        return m_mimeType.Set(mimeType);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRemoteResourceInformation::get_ResourceType(ElementType* elementType)
    {
        *elementType = m_urlType;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveRemoteResourceInformation::put_ResourceType(ElementType elementType)
    {
        m_urlType = elementType;
        return S_OK;
    }

AdaptiveNamespaceEnd
