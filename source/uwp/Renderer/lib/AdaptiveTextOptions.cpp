#include "pch.h"
#include "AdaptiveHostOptions.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "XamlCardRendererComponent.h"
#include "AdaptiveTextOptions.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveTextOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveTextOptions::RuntimeClassInitialize(TextOptions textOptions) noexcept
    {
        m_sharedTextOptions = textOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextOptions::get_Size(ABI::AdaptiveCards::XamlCardRenderer::TextSize* textSize)
    {
        *textSize = static_cast<ABI::AdaptiveCards::XamlCardRenderer::TextSize>(m_sharedTextOptions.size);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextOptions::put_Size(ABI::AdaptiveCards::XamlCardRenderer::TextSize textSize)
    {
        m_sharedTextOptions.size = static_cast<AdaptiveCards::TextSize>(textSize);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextOptions::get_Weight(ABI::AdaptiveCards::XamlCardRenderer::TextWeight* textWeight)
    {
        *textWeight = static_cast<ABI::AdaptiveCards::XamlCardRenderer::TextWeight>(m_sharedTextOptions.weight);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextOptions::put_Weight(ABI::AdaptiveCards::XamlCardRenderer::TextWeight textWeight)
    {
        m_sharedTextOptions.weight = static_cast<AdaptiveCards::TextWeight>(textWeight);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextOptions::get_Color(ABI::AdaptiveCards::XamlCardRenderer::TextColor* textColor)
    {
        *textColor = static_cast<ABI::AdaptiveCards::XamlCardRenderer::TextColor>(m_sharedTextOptions.color);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextOptions::put_Color(ABI::AdaptiveCards::XamlCardRenderer::TextColor textColor)
    {
        m_sharedTextOptions.color = static_cast<AdaptiveCards::TextColor>(textColor);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextOptions::get_IsSubtle(boolean* isSubtle)
    {
        *isSubtle = m_sharedTextOptions.isSubtle;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveTextOptions::put_IsSubtle(boolean isSubtle)
    {
        m_sharedTextOptions.isSubtle = Boolify(isSubtle);
        return S_OK;
    }
}
}
