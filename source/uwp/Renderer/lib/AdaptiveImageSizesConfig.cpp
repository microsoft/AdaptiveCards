#include "pch.h"
#include "AdaptiveImageSizesConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveImageSizesConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveImageSizesConfig::RuntimeClassInitialize(ImageSizesConfig imageSizesConfig) noexcept
    {
        m_sharedImageSizesConfig = imageSizesConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::get_Small(UINT32* smallSize)
    {
        *smallSize = m_sharedImageSizesConfig.smallSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::put_Small(UINT32 smallSize)
    {
        m_sharedImageSizesConfig.smallSize = smallSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::get_Medium(UINT32* mediumSize)
    {
        *mediumSize = m_sharedImageSizesConfig.mediumSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::put_Medium(UINT32 mediumSize)
    {
        m_sharedImageSizesConfig.mediumSize = mediumSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::get_Large(UINT32* largeSize)
    {
        *largeSize = m_sharedImageSizesConfig.largeSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::put_Large(UINT32 largeSize)
    {
        m_sharedImageSizesConfig.largeSize = largeSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::get_SquareImageButton(UINT32* squareImageButtonSize)
    {
        *squareImageButtonSize = m_sharedImageSizesConfig.squareImageButtonSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveImageSizesConfig::put_SquareImageButton(UINT32 squareImageButtonSize)
    {
        m_sharedImageSizesConfig.largeSize = squareImageButtonSize;
        return S_OK;
    }
}
}
