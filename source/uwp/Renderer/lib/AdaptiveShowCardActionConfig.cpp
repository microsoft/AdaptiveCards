#include "pch.h"
#include "Util.h"
#include "AdaptiveShowCardActionConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespaceRef;
using namespace ABI::Windows::UI;

AdaptiveNamespaceStart
    HRESULT AdaptiveShowCardActionConfig::RuntimeClassInitialize() noexcept try
    {
        ShowCardActionConfig showCardActionConfig;
        return RuntimeClassInitialize(showCardActionConfig);
    } CATCH_RETURN;

    HRESULT AdaptiveShowCardActionConfig::RuntimeClassInitialize(AdaptiveCards::ShowCardActionConfig sharedShowCardActionConfig) noexcept
    {
        m_actionMode = static_cast<ABI::AdaptiveNamespaceRef::ActionMode>(sharedShowCardActionConfig.actionMode);
        m_containerStyle = static_cast<ABI::AdaptiveNamespaceRef::ContainerStyle>(sharedShowCardActionConfig.style);
        m_inlineTopMargin = sharedShowCardActionConfig.inlineTopMargin;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveShowCardActionConfig::get_ActionMode(ABI::AdaptiveNamespaceRef::ActionMode* value)
    {
        *value = m_actionMode;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveShowCardActionConfig::put_ActionMode(ABI::AdaptiveNamespaceRef::ActionMode value)
    {
        m_actionMode = value;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveShowCardActionConfig::get_Style(ABI::AdaptiveNamespaceRef::ContainerStyle* style)
    {
        *style = m_containerStyle;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveShowCardActionConfig::put_Style(ABI::AdaptiveNamespaceRef::ContainerStyle style)
    {
        m_containerStyle = style;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardActionConfig::get_InlineTopMargin(UINT32* inlineTopMargin)
    {
        *inlineTopMargin = m_inlineTopMargin;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardActionConfig::put_InlineTopMargin(UINT32 inlineTopMargin)
    {
        m_inlineTopMargin = inlineTopMargin;
        return S_OK;
    }
AdaptiveNamespaceEnd
