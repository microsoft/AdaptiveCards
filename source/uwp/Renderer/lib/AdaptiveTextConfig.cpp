#include "pch.h"
#include "Util.h"
#include "AdaptiveTextConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Uwp;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveTextConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveTextConfig::RuntimeClassInitialize(TextConfig textConfig) noexcept
    {
        m_sharedTextConfig = textConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::get_Size(ABI::AdaptiveCards::Uwp::TextSize* textSize)
    {
        *textSize = static_cast<ABI::AdaptiveCards::Uwp::TextSize>(m_sharedTextConfig.size);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::put_Size(ABI::AdaptiveCards::Uwp::TextSize textSize)
    {
        m_sharedTextConfig.size = static_cast<AdaptiveCards::TextSize>(textSize);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::get_Weight(ABI::AdaptiveCards::Uwp::TextWeight* textWeight)
    {
        *textWeight = static_cast<ABI::AdaptiveCards::Uwp::TextWeight>(m_sharedTextConfig.weight);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::put_Weight(ABI::AdaptiveCards::Uwp::TextWeight textWeight)
    {
        m_sharedTextConfig.weight = static_cast<AdaptiveCards::TextWeight>(textWeight);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::get_Color(ABI::AdaptiveCards::Uwp::ForegroundColor* textColor)
    {
        *textColor = static_cast<ABI::AdaptiveCards::Uwp::ForegroundColor>(m_sharedTextConfig.color);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::put_Color(ABI::AdaptiveCards::Uwp::ForegroundColor textColor)
    {
        m_sharedTextConfig.color = static_cast<AdaptiveCards::ForegroundColor>(textColor);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::get_IsSubtle(boolean* isSubtle)
    {
        *isSubtle = m_sharedTextConfig.isSubtle;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::put_IsSubtle(boolean isSubtle)
    {
        m_sharedTextConfig.isSubtle = Boolify(isSubtle);
        return S_OK;
    }
    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::get_Wrap(boolean* wrap)
    {
        *wrap = m_sharedTextConfig.wrap;
        return S_OK;
    }
    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::put_Wrap(boolean wrap)
    {
        m_sharedTextConfig.wrap = Boolify(wrap);
        return S_OK;
    }
    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::get_MaxWidth(UINT32* maxWidth)
    {
        *maxWidth = m_sharedTextConfig.maxWidth;
        return S_OK;
    }
    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::put_MaxWidth(UINT32 maxWidth)
    {
        m_sharedTextConfig.maxWidth = maxWidth;
        return S_OK;
    }
}
}
