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
    HRESULT AdaptiveTextConfig::get_Color(ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor* textColor)
    {
        *textColor = static_cast<ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor>(m_sharedTextConfig.color);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextConfig::put_Color(ABI::AdaptiveCards::XamlCardRenderer::AdaptiveColor textColor)
    {
        m_sharedTextConfig.color = static_cast<AdaptiveCards::Color>(textColor);
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
}
}
