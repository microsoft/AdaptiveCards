#include "pch.h"
#include "Util.h"
#include "AdaptiveTextConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
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
    HRESULT AdaptiveTextConfig::get_Size(ABI::AdaptiveCards::XamlCardRenderer::TextSize* textSize)
    {
        *textSize = static_cast<ABI::AdaptiveCards::XamlCardRenderer::TextSize>(m_sharedTextConfig.size);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::put_Size(ABI::AdaptiveCards::XamlCardRenderer::TextSize textSize)
    {
        m_sharedTextConfig.size = static_cast<AdaptiveCards::TextSize>(textSize);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::get_Weight(ABI::AdaptiveCards::XamlCardRenderer::TextWeight* textWeight)
    {
        *textWeight = static_cast<ABI::AdaptiveCards::XamlCardRenderer::TextWeight>(m_sharedTextConfig.weight);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::put_Weight(ABI::AdaptiveCards::XamlCardRenderer::TextWeight textWeight)
    {
        m_sharedTextConfig.weight = static_cast<AdaptiveCards::TextWeight>(textWeight);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::get_Color(ABI::AdaptiveCards::XamlCardRenderer::ForegroundColor* textColor)
    {
        *textColor = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ForegroundColor>(m_sharedTextConfig.color);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::put_Color(ABI::AdaptiveCards::XamlCardRenderer::ForegroundColor textColor)
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
