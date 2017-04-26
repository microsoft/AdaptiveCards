#include "pch.h"
#include "AdaptiveHostOptions.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "XamlCardRendererComponent.h"
#include "AdaptiveColorOption.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI;
using namespace ABI::Windows::UI::Xaml;

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
    HRESULT AdaptiveColorOption::get_Normal(ABI::Windows::UI::Color* value)
    {
        return GetColorFromString(m_sharedColorOption.normal, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOption::put_Normal(ABI::Windows::UI::Color value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOption::get_Subtle(ABI::Windows::UI::Color* value)
    {
        return GetColorFromString(m_sharedColorOption.subtle, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveColorOption::put_Subtle(ABI::Windows::UI::Color value)
    {
        return E_NOTIMPL;
    }
}
}
