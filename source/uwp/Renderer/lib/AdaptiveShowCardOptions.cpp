#include "pch.h"
#include "Util.h"
#include "AdaptiveShowCardOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveShowCardOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveShowCardOptions::RuntimeClassInitialize(AdaptiveCards::ShowCardOptions showCardOptions) noexcept
    {
        m_sharedShowCardOptions = showCardOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveShowCardOptions::get_ActionMode(ABI::AdaptiveCards::XamlCardRenderer::ActionMode * value)
    {
        *value = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ActionMode>(m_sharedShowCardOptions.actionMode);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveShowCardOptions::put_ActionMode(ABI::AdaptiveCards::XamlCardRenderer::ActionMode value)
    {
        m_sharedShowCardOptions.actionMode = static_cast<AdaptiveCards::ActionMode>(value);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardOptions::get_BackgroundColor(Color* value)
    {
        return GetColorFromString(m_sharedShowCardOptions.backgroundColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardOptions::put_BackgroundColor(Color value)
    {
        return E_NOTIMPL;
    }

    IFACEMETHODIMP AdaptiveShowCardOptions::get_AutoPadding(boolean * autoPadding)
    {
        *autoPadding = m_sharedShowCardOptions.autoPadding;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveShowCardOptions::put_AutoPadding(boolean autoPadding)
    {
        m_sharedShowCardOptions.autoPadding = Boolify(autoPadding);
        return S_OK;
    }
}}
