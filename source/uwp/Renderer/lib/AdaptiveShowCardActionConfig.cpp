#include "pch.h"
#include "Util.h"
#include "AdaptiveSpacingDefinition.h"
#include "AdaptiveShowCardActionConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer
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
    HRESULT  AdaptiveShowCardActionConfig::get_ActionMode(ABI::AdaptiveCards::XamlCardRenderer::ActionMode* value)
    {
        *value = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ActionMode>(m_sharedShowCardActionConfig.actionMode);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT  AdaptiveShowCardActionConfig::put_ActionMode(ABI::AdaptiveCards::XamlCardRenderer::ActionMode value)
    {
        m_sharedShowCardActionConfig.actionMode = static_cast<AdaptiveCards::ActionMode>(value);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardActionConfig::get_BackgroundColor(ABI::Windows::UI::Color* value)
    {
        return GetColorFromString(m_sharedShowCardActionConfig.backgroundColor, value);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardActionConfig::put_BackgroundColor(ABI::Windows::UI::Color /*value*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardActionConfig::get_Padding(IAdaptiveSpacingDefinition** spacingDefinition)
    {
        return MakeAndInitialize<AdaptiveSpacingDefinition>(spacingDefinition, m_sharedShowCardActionConfig.padding);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardActionConfig::put_Padding(IAdaptiveSpacingDefinition* /*value*/)
    {
        return E_NOTIMPL;
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
