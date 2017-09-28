#include "pch.h"
#include "AdaptiveFontSizesConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Uwp;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveFontSizesConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveFontSizesConfig::RuntimeClassInitialize(FontSizesConfig fontSizesConfig) noexcept
    {
        m_sharedFontSizesConfig = fontSizesConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::get_Small(UINT32* smallFontSize)
    {
        *smallFontSize = m_sharedFontSizesConfig.smallFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::put_Small(UINT32 smallFontSize)
    {
        m_sharedFontSizesConfig.smallFontSize = smallFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::get_Default(UINT32* defaultFontSize)
    {
        *defaultFontSize = m_sharedFontSizesConfig.defaultFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::put_Default(UINT32 defaultFontSize)
    {
        m_sharedFontSizesConfig.defaultFontSize = defaultFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::get_Medium(UINT32* mediumFontSize)
    {
        *mediumFontSize = m_sharedFontSizesConfig.mediumFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::put_Medium(UINT32 mediumFontSize)
    {
        m_sharedFontSizesConfig.mediumFontSize = mediumFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::get_Large(UINT32* largeFontSize)
    {
        *largeFontSize = m_sharedFontSizesConfig.largeFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::put_Large(UINT32 largeFontSize)
    {
        m_sharedFontSizesConfig.largeFontSize = largeFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::get_ExtraLarge(UINT32* extraLargeFontSize)
    {
        *extraLargeFontSize = m_sharedFontSizesConfig.extraLargeFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::put_ExtraLarge(UINT32 extraLargeFontSize)
    {
        m_sharedFontSizesConfig.extraLargeFontSize = extraLargeFontSize;
        return S_OK;
    }
}
}
