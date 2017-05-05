#include "pch.h"
#include "AdaptiveFontSizeOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveFontSizeOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveFontSizeOptions::RuntimeClassInitialize(FontSizeOptions fontSizeOptions) noexcept
    {
        m_sharedFontSizeOptions = fontSizeOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::get_Small(UINT32* smallFontSize)
    {
        *smallFontSize = m_sharedFontSizeOptions.smallFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::put_Small(UINT32 smallFontSize)
    {
        m_sharedFontSizeOptions.smallFontSize = smallFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::get_Normal(UINT32* normalFontSize)
    {
        *normalFontSize = m_sharedFontSizeOptions.normalFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::put_Normal(UINT32 normalFontSize)
    {
        m_sharedFontSizeOptions.normalFontSize = normalFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::get_Medium(UINT32* mediumFontSize)
    {
        *mediumFontSize = m_sharedFontSizeOptions.mediumFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::put_Medium(UINT32 mediumFontSize)
    {
        m_sharedFontSizeOptions.mediumFontSize = mediumFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::get_Large(UINT32* largeFontSize)
    {
        *largeFontSize = m_sharedFontSizeOptions.largeFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::put_Large(UINT32 largeFontSize)
    {
        m_sharedFontSizeOptions.largeFontSize = largeFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::get_ExtraLarge(UINT32* extraLargeFontSize)
    {
        *extraLargeFontSize = m_sharedFontSizeOptions.extraLargeFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::put_ExtraLarge(UINT32 extraLargeFontSize)
    {
        m_sharedFontSizeOptions.extraLargeFontSize = extraLargeFontSize;
        return S_OK;
    }
}
}
