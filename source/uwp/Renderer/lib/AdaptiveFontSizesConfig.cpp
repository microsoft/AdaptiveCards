#include "pch.h"
#include "AdaptiveFontSizesConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

AdaptiveNamespaceStart
    HRESULT AdaptiveFontSizesConfig::RuntimeClassInitialize() noexcept try
    {
        FontSizesConfig fontSizesConfig;
        return RuntimeClassInitialize(fontSizesConfig);
    } CATCH_RETURN;

    HRESULT AdaptiveFontSizesConfig::RuntimeClassInitialize(FontSizesConfig fontSizesConfig) noexcept
    {
        m_default = fontSizesConfig.defaultFontSize;
        m_small = fontSizesConfig.smallFontSize;
        m_medium = fontSizesConfig.mediumFontSize;
        m_large = fontSizesConfig.largeFontSize;
        m_extraLarge = fontSizesConfig.extraLargeFontSize;

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::get_Small(UINT32* smallFontSize)
    {
        *smallFontSize = m_small;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::put_Small(UINT32 smallFontSize)
    {
        m_small= smallFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::get_Default(UINT32* defaultFontSize)
    {
        *defaultFontSize = m_default;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::put_Default(UINT32 defaultFontSize)
    {
        m_default = defaultFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::get_Medium(UINT32* mediumFontSize)
    {
        *mediumFontSize = m_medium;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::put_Medium(UINT32 mediumFontSize)
    {
        m_medium = mediumFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::get_Large(UINT32* largeFontSize)
    {
        *largeFontSize = m_large;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::put_Large(UINT32 largeFontSize)
    {
        m_large = largeFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::get_ExtraLarge(UINT32* extraLargeFontSize)
    {
        *extraLargeFontSize = m_extraLarge;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizesConfig::put_ExtraLarge(UINT32 extraLargeFontSize)
    {
        m_extraLarge = extraLargeFontSize;
        return S_OK;
    }
AdaptiveNamespaceEnd
