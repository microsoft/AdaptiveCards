#include "pch.h"
#include "AdaptiveColorOptions.h"
#include "AdaptiveColorOption.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveColorOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveColorOptions::RuntimeClassInitialize(ColorOptions colorOptions) noexcept
    {
        m_sharedColorOptions = colorOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::get_Default(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** defaultColorOption)
    {
        return MakeAndInitialize<AdaptiveColorOption>(defaultColorOption, m_sharedColorOptions.defaultColor);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::put_Default(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::get_Accent(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** accentColorOption)
    {
        return MakeAndInitialize<AdaptiveColorOption>(accentColorOption, m_sharedColorOptions.accent);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::put_Accent(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::get_Dark(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** darkColorOption)
    {
        return MakeAndInitialize<AdaptiveColorOption>(darkColorOption, m_sharedColorOptions.dark);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::put_Dark(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::get_Light(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** lightColorOption)
    {
        return MakeAndInitialize<AdaptiveColorOption>(lightColorOption, m_sharedColorOptions.light);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::put_Light(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::get_Good(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** goodColorOption)
    {
        return MakeAndInitialize<AdaptiveColorOption>(goodColorOption, m_sharedColorOptions.good);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::put_Good(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value)
    {
        return E_NOTIMPL;
    }
    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::get_Warning(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** warningColorOption)
    {
        return MakeAndInitialize<AdaptiveColorOption>(warningColorOption, m_sharedColorOptions.warning);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::put_Warning(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value)
    {
        return E_NOTIMPL;
    }
    
    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::get_Attention(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption** attentionColorOption)
    {
        return MakeAndInitialize<AdaptiveColorOption>(attentionColorOption, m_sharedColorOptions.attention);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOptions::put_Attention(ABI::AdaptiveCards::XamlCardRenderer::IAdaptiveColorOption* value)
    {
        return E_NOTIMPL;
    }
}
}
