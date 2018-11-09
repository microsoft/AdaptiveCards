#include "pch.h"
#include "AdaptiveFontWeightsConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveFontWeightsConfig::RuntimeClassInitialize() noexcept try
    {
        FontWeightsConfig fontWeightsConfig;
        return RuntimeClassInitialize(fontWeightsConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveFontWeightsConfig::RuntimeClassInitialize(FontWeightsConfig fontWeightsConfig) noexcept
    {
        m_default = static_cast<UINT16>(fontWeightsConfig.GetFontWeight(AdaptiveCards::TextWeight::Default));
        m_lighter = static_cast<UINT16>(fontWeightsConfig.GetFontWeight(AdaptiveCards::TextWeight::Lighter));
        m_bolder = static_cast<UINT16>(fontWeightsConfig.GetFontWeight(AdaptiveCards::TextWeight::Bolder));

        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontWeightsConfig::get_Lighter(UINT16* lighter)
    {
        *lighter = m_lighter;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontWeightsConfig::put_Lighter(UINT16 lighter)
    {
        m_lighter = lighter;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontWeightsConfig::get_Default(UINT16* default)
    {
        *default = m_default;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontWeightsConfig::put_Default(UINT16 default)
    {
        m_default = default;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontWeightsConfig::get_Bolder(UINT16* bolder)
    {
        *bolder = m_bolder;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveFontWeightsConfig::put_Bolder(UINT16 bolder)
    {
        m_bolder = bolder;
        return S_OK;
    }
}
