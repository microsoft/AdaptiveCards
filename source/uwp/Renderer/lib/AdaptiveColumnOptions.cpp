#include "pch.h"
#include "AdaptiveHostOptions.h"
#include "Util.h"
#include <windows.foundation.collections.h>
#include "XamlCardRendererComponent.h"
#include "AdaptiveColumnOptions.h"
#include "AdaptiveSeparationOptions.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveColumnOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;


    HRESULT AdaptiveColumnOptions::RuntimeClassInitialize(ColumnOptions columnOptions) noexcept
    {
        m_sharedColumnOptions = columnOptions;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveColumnOptions::get_DefaultSeparation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedColumnOptions.defaultSeparation);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveColumnOptions::put_DefaultSeparation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveColumnOptions::get_StrongSeparation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedColumnOptions.strongSeparation);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveColumnOptions::put_StrongSeparation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }
}
}
