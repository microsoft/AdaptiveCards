// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveShowCardActionConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::UI;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveShowCardActionConfig::RuntimeClassInitialize() noexcept
    try
    {
        ShowCardActionConfig showCardActionConfig;
        return RuntimeClassInitialize(showCardActionConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveShowCardActionConfig::RuntimeClassInitialize(AdaptiveSharedNamespace::ShowCardActionConfig sharedShowCardActionConfig) noexcept
    {
        m_actionMode = static_cast<ABI::AdaptiveNamespace::ActionMode>(sharedShowCardActionConfig.actionMode);
        m_containerStyle = static_cast<ABI::AdaptiveNamespace::ContainerStyle>(sharedShowCardActionConfig.style);
        m_inlineTopMargin = sharedShowCardActionConfig.inlineTopMargin;
        return S_OK;
    }

    HRESULT AdaptiveShowCardActionConfig::get_ActionMode(_Out_ ABI::AdaptiveNamespace::ActionMode* value)
    {
        *value = m_actionMode;
        return S_OK;
    }

    HRESULT AdaptiveShowCardActionConfig::put_ActionMode(ABI::AdaptiveNamespace::ActionMode value)
    {
        m_actionMode = value;
        return S_OK;
    }

    HRESULT AdaptiveShowCardActionConfig::get_Style(_Out_ ABI::AdaptiveNamespace::ContainerStyle* style)
    {
        *style = m_containerStyle;
        return S_OK;
    }

    HRESULT AdaptiveShowCardActionConfig::put_Style(ABI::AdaptiveNamespace::ContainerStyle style)
    {
        m_containerStyle = style;
        return S_OK;
    }

    HRESULT AdaptiveShowCardActionConfig::get_InlineTopMargin(_Out_ UINT32* inlineTopMargin)
    {
        *inlineTopMargin = m_inlineTopMargin;
        return S_OK;
    }

    HRESULT AdaptiveShowCardActionConfig::put_InlineTopMargin(UINT32 inlineTopMargin)
    {
        m_inlineTopMargin = inlineTopMargin;
        return S_OK;
    }
}
