#include "pch.h"
#include "AdaptiveImageSizesConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

AdaptiveNamespaceStart
    HRESULT AdaptiveImageSizesConfig::RuntimeClassInitialize() noexcept try
    {
        ImageSizesConfig imageSizesConfig;
        return RuntimeClassInitialize(imageSizesConfig);
    } CATCH_RETURN;

    HRESULT AdaptiveImageSizesConfig::RuntimeClassInitialize(ImageSizesConfig imageSizesConfig) noexcept
    {
        m_small = imageSizesConfig.smallSize;
        m_medium = imageSizesConfig.mediumSize;
        m_large = imageSizesConfig.largeSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::get_Small(UINT32* smallSize)
    {
        *smallSize = m_small;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::put_Small(UINT32 smallSize)
    {
        m_small = smallSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::get_Medium(UINT32* mediumSize)
    {
        *mediumSize = m_medium;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::put_Medium(UINT32 mediumSize)
    {
        m_medium = mediumSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::get_Large(UINT32* largeSize)
    {
        *largeSize = m_large;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::put_Large(UINT32 largeSize)
    {
        m_large = largeSize;
        return S_OK;
    }
AdaptiveNamespaceEnd
