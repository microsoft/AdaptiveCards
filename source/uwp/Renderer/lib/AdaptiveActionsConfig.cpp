// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionsConfig.h"
#include "AdaptiveShowCardActionConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveActionsConfig::RuntimeClassInitialize() noexcept try
    {
        ActionsConfig actionsConfig;
        return RuntimeClassInitialize(actionsConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveActionsConfig::RuntimeClassInitialize(AdaptiveSharedNamespace::ActionsConfig actionsConfig) noexcept
    {
        m_actionAlignment = static_cast<ABI::AdaptiveNamespace::ActionAlignment>(actionsConfig.actionAlignment);
        m_actionsOrientation = static_cast<ABI::AdaptiveNamespace::ActionsOrientation>(actionsConfig.actionsOrientation);
        m_buttonSpacing = actionsConfig.buttonSpacing;
        m_maxActions = actionsConfig.maxActions;
        m_spacing = static_cast<ABI::AdaptiveNamespace::Spacing>(actionsConfig.spacing);
        m_iconPlacement = static_cast<ABI::AdaptiveNamespace::IconPlacement>(actionsConfig.iconPlacement);
        m_iconSize = actionsConfig.iconSize;

        RETURN_IF_FAILED(MakeAndInitialize<AdaptiveShowCardActionConfig>(m_showCardActionConfig.GetAddressOf(),
                                                                         actionsConfig.showCard));

        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::get_ShowCard(_COM_Outptr_ IAdaptiveShowCardActionConfig** showCardActionConfig)
    {
        return m_showCardActionConfig.CopyTo(showCardActionConfig);
    }

    HRESULT AdaptiveActionsConfig::put_ShowCard(_In_ IAdaptiveShowCardActionConfig* showCardActionConfig)
    {
        m_showCardActionConfig = showCardActionConfig;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::get_ButtonSpacing(_Out_ UINT32* value)
    {
        *value = m_buttonSpacing;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::put_ButtonSpacing(UINT32 value)
    {
        m_buttonSpacing = value;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::get_MaxActions(_Out_ UINT32* value)
    {
        *value = m_maxActions;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::put_MaxActions(UINT32 value)
    {
        m_maxActions = value;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::get_Spacing(_Out_ ABI::AdaptiveNamespace::Spacing* value)
    {
        *value = m_spacing;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::put_Spacing(ABI::AdaptiveNamespace::Spacing value)
    {
        m_spacing = value;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::get_ActionAlignment(_Out_ ABI::AdaptiveNamespace::ActionAlignment* value)
    {
        *value = m_actionAlignment;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::put_ActionAlignment(ABI::AdaptiveNamespace::ActionAlignment value)
    {
        m_actionAlignment = value;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::get_ActionsOrientation(_Out_ ABI::AdaptiveNamespace::ActionsOrientation* value)
    {
        *value = m_actionsOrientation;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::put_ActionsOrientation(ABI::AdaptiveNamespace::ActionsOrientation value)
    {
        m_actionsOrientation = value;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::get_IconPlacement(_Out_ ABI::AdaptiveNamespace::IconPlacement* value)
    {
        *value = m_iconPlacement;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::put_IconPlacement(ABI::AdaptiveNamespace::IconPlacement value)
    {
        m_iconPlacement = value;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::get_IconSize(_Out_ UINT32* value)
    {
        *value = m_iconSize;
        return S_OK;
    }

    HRESULT AdaptiveActionsConfig::put_IconSize(UINT32 value)
    {
        m_iconSize = value;
        return S_OK;
    }
}
