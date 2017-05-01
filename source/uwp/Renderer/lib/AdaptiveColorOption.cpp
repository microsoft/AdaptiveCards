#include "pch.h"
#include "Util.h"
#include "AdaptiveColorOption.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveColorOption::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveColorOption::RuntimeClassInitialize(ColorOption colorOption) noexcept
    {
        m_sharedColorOption = colorOption;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOption::get_Normal(Color* value)
    {
        return GetColorFromString(m_sharedColorOption.normal, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOption::put_Normal(Color value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOption::get_Subtle(Color* value)
    {
        return GetColorFromString(m_sharedColorOption.subtle, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOption::put_Subtle(Color value)
    {
        return E_NOTIMPL;
    }
}
}
