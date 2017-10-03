#include "pch.h"
#include "Util.h"
#include "AdaptiveShowCardActionConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveShowCardActionConfig::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveShowCardActionConfig::RuntimeClassInitialize(AdaptiveCards::ShowCardActionConfig ShowCardActionConfig) noexcept
    {
        m_sharedShowCardActionConfig = ShowCardActionConfig;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveShowCardActionConfig::get_ActionMode(ABI::AdaptiveCards::Uwp::ActionMode* value)
    {
        *value = static_cast<ABI::AdaptiveCards::Uwp::ActionMode>(m_sharedShowCardActionConfig.actionMode);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveShowCardActionConfig::put_ActionMode(ABI::AdaptiveCards::Uwp::ActionMode value)
    {
        m_sharedShowCardActionConfig.actionMode = static_cast<AdaptiveCards::ActionMode>(value);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveShowCardActionConfig::get_Style(ABI::AdaptiveCards::Uwp::ContainerStyle* style)
    {
        *style = static_cast<ABI::AdaptiveCards::Uwp::ContainerStyle>(m_sharedShowCardActionConfig.style);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveShowCardActionConfig::put_Style(ABI::AdaptiveCards::Uwp::ContainerStyle style)
    {
        m_sharedShowCardActionConfig.style = static_cast<AdaptiveCards::ContainerStyle>(style);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardActionConfig::get_InlineTopMargin(UINT32* inlineTopMargin)
    {
        *inlineTopMargin = m_sharedShowCardActionConfig.inlineTopMargin;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardActionConfig::put_InlineTopMargin(UINT32 inlineTopMargin)
    {
        m_sharedShowCardActionConfig.inlineTopMargin = inlineTopMargin;
        return S_OK;
    }
}}
