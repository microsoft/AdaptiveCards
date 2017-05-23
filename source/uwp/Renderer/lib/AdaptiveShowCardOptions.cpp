#include "pch.h"
#include "Util.h"
#include "AdaptiveBoundaryOptions.h"
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
    HRESULT  AdaptiveShowCardOptions::get_ActionMode(ABI::AdaptiveCards::XamlCardRenderer::ActionMode* value)
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

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardOptions::get_Padding(IAdaptiveBoundaryOptions** boundaryOptions)
    {
        return MakeAndInitialize<AdaptiveBoundaryOptions>(boundaryOptions, m_sharedShowCardOptions.padding);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardOptions::put_Padding(IAdaptiveBoundaryOptions* value)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardOptions::get_InlineTopMargin(UINT32* inlineTopMargin)
    {
        *inlineTopMargin = m_sharedShowCardOptions.inlineTopMargin;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardOptions::put_InlineTopMargin(UINT32 inlineTopMargin)
    {
        m_sharedShowCardOptions.inlineTopMargin = inlineTopMargin;
        return S_OK;
    }
}}
