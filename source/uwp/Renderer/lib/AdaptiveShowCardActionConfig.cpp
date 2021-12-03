// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveShowCardActionConfig.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;
using namespace ABI::Windows::UI;

namespace AdaptiveCards::Rendering::Uwp
{
    HRESULT AdaptiveShowCardActionConfig::RuntimeClassInitialize() noexcept
    try
    {
        ShowCardActionConfig showCardActionConfig;
        return RuntimeClassInitialize(showCardActionConfig);
    }
    CATCH_RETURN;

    HRESULT AdaptiveShowCardActionConfig::RuntimeClassInitialize(AdaptiveCards::ShowCardActionConfig sharedShowCardActionConfig) noexcept
    {
        m_actionMode = static_cast<ABI::AdaptiveCards::Rendering::Uwp::ActionMode>(sharedShowCardActionConfig.actionMode);
        m_containerStyle = static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle>(sharedShowCardActionConfig.style);
        m_inlineTopMargin = sharedShowCardActionConfig.inlineTopMargin;
        return S_OK;
    }

    HRESULT AdaptiveShowCardActionConfig::get_ActionMode(_Out_ ABI::AdaptiveCards::Rendering::Uwp::ActionMode* value)
    {
        *value = m_actionMode;
        return S_OK;
    }

    HRESULT AdaptiveShowCardActionConfig::put_ActionMode(ABI::AdaptiveCards::Rendering::Uwp::ActionMode value)
    {
        m_actionMode = value;
        return S_OK;
    }

    HRESULT AdaptiveShowCardActionConfig::get_Style(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle* style)
    {
        *style = m_containerStyle;
        return S_OK;
    }

    HRESULT AdaptiveShowCardActionConfig::put_Style(ABI::AdaptiveCards::ObjectModel::Uwp::ContainerStyle style)
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
