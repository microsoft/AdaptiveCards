#include "pch.h"
#include "AdaptiveFontWeightsConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveFontWeightsConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveFontWeightsConfig::RuntimeClassInitialize(FontWeightsConfig fontWeightsConfig) noexcept
    {
        m_sharedFontWeightsConfig = fontWeightsConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontWeightsConfig::get_Lighter(UINT16* lighter)
    {
        *lighter = m_sharedFontWeightsConfig.lighterWeight;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontWeightsConfig::put_Lighter(UINT16 lighter)
    {
        m_sharedFontWeightsConfig.lighterWeight = lighter;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontWeightsConfig::get_Default(UINT16* default)
    {
        *default = m_sharedFontWeightsConfig.defaultWeight;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontWeightsConfig::put_Default(UINT16 default)
    {
        m_sharedFontWeightsConfig.defaultWeight = default;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontWeightsConfig::get_Bolder(UINT16* bolder)
    {
        *bolder = m_sharedFontWeightsConfig.bolderWeight;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveFontWeightsConfig::put_Bolder(UINT16 bolder)
    {
        m_sharedFontWeightsConfig.bolderWeight = bolder;
        return S_OK;
    }
}
}
