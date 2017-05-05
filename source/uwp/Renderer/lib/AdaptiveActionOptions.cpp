#include "pch.h"
#include "Util.h"
#include "AdaptiveActionOptions.h"
#include "AdaptiveSeparationOptions.h"
#include "AdaptiveShowCardOptions.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::XamlCardRenderer;
using namespace ABI::Windows::UI;

namespace AdaptiveCards { namespace XamlCardRenderer
{
    HRESULT AdaptiveActionOptions::RuntimeClassInitialize() noexcept try
    {
        return S_OK;
    } CATCH_RETURN;

    HRESULT AdaptiveActionOptions::RuntimeClassInitialize(AdaptiveCards::ActionOptions actionOptions) noexcept
    {
        m_sharedActionOptions = actionOptions;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_ShowCard(IAdaptiveShowCardOptions** showCardOptions)
    {
        return MakeAndInitialize<AdaptiveShowCardOptions>(showCardOptions, m_sharedActionOptions.showCard);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_ShowCard(IAdaptiveShowCardOptions* showCardOptions)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_ButtonSpacing(UINT32* value)
    {
        *value = m_sharedActionOptions.buttonSpacing;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_ButtonSpacing(UINT32 value)
    {
        m_sharedActionOptions.buttonSpacing = value;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveActionOptions::get_MaxActions(UINT32* value)
    {
        *value = m_sharedActionOptions.maxActions;
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveActionOptions::put_MaxActions(UINT32 value)
    {
        m_sharedActionOptions.maxActions = value;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_ActionAlignment(ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment* value)
    {
        *value = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment>(m_sharedActionOptions.actionAlignment);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_ActionAlignment(ABI::AdaptiveCards::XamlCardRenderer::ActionAlignment value)
    {
        m_sharedActionOptions.actionAlignment = static_cast<AdaptiveCards::ActionAlignment>(value);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::get_ActionsOrientation(ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation* value)
    {
        *value = static_cast<ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation>(m_sharedActionOptions.actionsOrientation);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveActionOptions::put_ActionsOrientation(ABI::AdaptiveCards::XamlCardRenderer::ActionsOrientation value)
    {
        m_sharedActionOptions.actionsOrientation = static_cast<AdaptiveCards::ActionsOrientation>(value);
        return S_OK;
    }

    _Use_decl_annotations_
        HRESULT AdaptiveActionOptions::get_Separation(IAdaptiveSeparationOptions** separationOptions)
    {
        return MakeAndInitialize<AdaptiveSeparationOptions>(separationOptions, m_sharedActionOptions.separation);
    }

    _Use_decl_annotations_
        HRESULT AdaptiveActionOptions::put_Separation(IAdaptiveSeparationOptions*)
    {
        return E_NOTIMPL;
    }
}}
