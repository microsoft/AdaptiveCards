// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AdaptiveActionSet.h"

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveCards::ObjectModel::WinUI3;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::WinUI3
{
    AdaptiveActionSet::AdaptiveActionSet() { m_actions = winrt::single_threaded_vector<winrt::AdaptiveCards::ObjectModel::WinUI3::IAdaptiveActionElement>(); }

    HRESULT AdaptiveActionSet::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::ActionSet> ActionSet = std::make_shared<AdaptiveCards::ActionSet>();
        return RuntimeClassInitialize(ActionSet);
    }
    CATCH_RETURN;

    HRESULT AdaptiveActionSet::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ActionSet>& sharedActionSet)
    try
    {
        if (sharedActionSet == nullptr)
        {
            return E_INVALIDARG;
        }

        m_actions = GenerateActionsProjection(sharedActionSet->GetActions());
        InitializeBaseElement(std::static_pointer_cast<BaseCardElement>(sharedActionSet));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveActionSet::get_Actions(_COM_Outptr_ IVector<IAdaptiveActionElement*>** items)
    {
        copy_to_abi(m_actions, items);
        return S_OK;
    }

    HRESULT AdaptiveActionSet::get_ElementType(_Out_ ElementType* elementType)
    {
        *elementType = ElementType::ActionSet;
        return S_OK;
    }

    std::shared_ptr<::AdaptiveCards::BaseCardElement> AdaptiveActionSet::GetSharedModel()
    {
        auto actionSet = std::make_shared<AdaptiveCards::ActionSet>();
        THROW_IF_FAILED(CopySharedElementProperties(*actionSet));

        actionSet->GetActions() = GenerateSharedActions(m_actions);
        return actionSet;
    }
}
