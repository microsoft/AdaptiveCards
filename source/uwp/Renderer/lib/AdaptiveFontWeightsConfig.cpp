#include "pch.h"
#include "AdaptiveFontWeightsConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Uwp;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveFontWeightsConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveFontWeightsConfig::RuntimeClassInitialize(FontWeightsConfig fontWeightsConfig) noexcept
    {
        m_default = fontWeightsConfig.defaultWeight;
        m_lighter = fontWeightsConfig.lighterWeight;
        m_bolder = fontWeightsConfig.bolderWeight;

        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontWeightsConfig::get_Lighter(UINT16* lighter)
    {
        *lighter = m_lighter;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontWeightsConfig::put_Lighter(UINT16 lighter)
    {
        m_lighter = lighter;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontWeightsConfig::get_Default(UINT16* default)
    {
        *default = m_default;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontWeightsConfig::put_Default(UINT16 default)
    {
        m_default = default;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveFontWeightsConfig::get_Bolder(UINT16* bolder)
    {
        *bolder = m_bolder;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveFontWeightsConfig::put_Bolder(UINT16 bolder)
    {
        m_bolder = bolder;
        return S_OK;
    }
}
}
