#include "pch.h"
#include "Util.h"
#include "AdaptiveColorConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveColorConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveColorConfig::RuntimeClassInitialize(ColorConfig colorConfig) noexcept
    {
        m_sharedColorConfig = colorConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorConfig::get_Normal(ABI::Windows::UI::Color* value)
    {
        return GetColorFromString(m_sharedColorConfig.normal, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorConfig::put_Normal(ABI::Windows::UI::Color /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorConfig::get_Subtle(ABI::Windows::UI::Color* value)
    {
        return GetColorFromString(m_sharedColorConfig.subtle, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorConfig::put_Subtle(ABI::Windows::UI::Color /*value*/)
    {
        return E_NOTIMPL;
    }
}
}
