#include "pch.h"
#include "AdaptiveMediaEventArgs.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;

AdaptiveNamespaceStart
    HRESULT AdaptiveMediaEventArgs::RuntimeClassInitialize()
    {
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveMediaEventArgs::RuntimeClassInitialize(IAdaptiveMedia* media)
    {
        m_media = media;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveMediaEventArgs::get_Media(IAdaptiveMedia** media)
    {
        return m_media.CopyTo(media);
    }
AdaptiveNamespaceEnd
