#include "pch.h"
#include "AdaptiveImageSizeOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveImageSizeOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveImageSizeOptions::RuntimeClassInitialize(ImageSizeOptions imageSizeOptions) noexcept
    {
        m_sharedImageSizeOptions = imageSizeOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizeOptions::get_Small(UINT32* smallSize)
    {
        *smallSize = m_sharedImageSizeOptions.smallSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizeOptions::put_Small(UINT32 smallSize)
    {
        m_sharedImageSizeOptions.smallSize = smallSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizeOptions::get_Medium(UINT32* mediumSize)
    {
        *mediumSize = m_sharedImageSizeOptions.mediumSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizeOptions::put_Medium(UINT32 mediumSize)
    {
        m_sharedImageSizeOptions.mediumSize = mediumSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizeOptions::get_Large(UINT32* largeSize)
    {
        *largeSize = m_sharedImageSizeOptions.largeSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizeOptions::put_Large(UINT32 largeSize)
    {
        m_sharedImageSizeOptions.largeSize = largeSize;
        return S_OK;
    }
}
}
