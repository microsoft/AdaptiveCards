#include "pch.h"
#include "AdaptiveHostOptions.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "XamlCardRendererComponent.h"
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
    HRESULT AdaptiveFontSizeOptions::get_Small(INT32* smallFontSize)
    {
        *smallFontSize = m_sharedFontSizeOptions.smallFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::put_Small(INT32 smallFontSize)
    {
        m_sharedFontSizeOptions.smallFontSize = smallFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::get_Normal(INT32* normalFontSize)
    {
        *normalFontSize = m_sharedFontSizeOptions.normalFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::put_Normal(INT32 normalFontSize)
    {
        m_sharedFontSizeOptions.normalFontSize = normalFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::get_Medium(INT32* mediumFontSize)
    {
        *mediumFontSize = m_sharedFontSizeOptions.mediumFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::put_Medium(INT32 mediumFontSize)
    {
        m_sharedFontSizeOptions.mediumFontSize = mediumFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::get_Large(INT32* largeFontSize)
    {
        *largeFontSize = m_sharedFontSizeOptions.largeFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::put_Large(INT32 largeFontSize)
    {
        m_sharedFontSizeOptions.largeFontSize = largeFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::get_ExtraLarge(INT32* extraLargeFontSize)
    {
        *extraLargeFontSize = m_sharedFontSizeOptions.extraLargeFontSize;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontSizeOptions::put_ExtraLarge(INT32 extraLargeFontSize)
    {
        m_sharedFontSizeOptions.extraLargeFontSize = extraLargeFontSize;
        return S_OK;
    }
}
}
