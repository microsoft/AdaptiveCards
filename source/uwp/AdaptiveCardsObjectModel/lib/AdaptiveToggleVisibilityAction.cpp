// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveToggleVisibilityAction.h"
#include "AdaptiveToggleVisibilityTarget.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveToggleVisibilityAction::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::ToggleVisibilityAction> toggleVisibilityAction =
            std::make_shared<AdaptiveCards::ToggleVisibilityAction>();
        return RuntimeClassInitialize(toggleVisibilityAction);
    }
    CATCH_RETURN;

    HRESULT AdaptiveToggleVisibilityAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ToggleVisibilityAction>& sharedToggleVisibilityAction)
    try
    {
        if (sharedToggleVisibilityAction == nullptr)
        {
            return E_INVALIDARG;
        }

        m_targetElements = Microsoft::WRL::Make<Vector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveToggleVisibilityTarget*>>();
        GenerateToggleTargetProjection(sharedToggleVisibilityAction->GetTargetElements(), m_targetElements.Get());

        InitializeBaseElement(std::static_pointer_cast<AdaptiveCards::BaseActionElement>(sharedToggleVisibilityAction));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveToggleVisibilityAction::get_ActionType(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveCards::ObjectModel::Uwp::ActionType::ToggleVisibility;
        return S_OK;
    }

    HRESULT AdaptiveToggleVisibilityAction::get_TargetElements(
        _COM_Outptr_ IVector<ABI::AdaptiveCards::ObjectModel::Uwp::AdaptiveToggleVisibilityTarget*>** targetElements)
    {
        return m_targetElements.CopyTo(targetElements);
    }

    HRESULT AdaptiveToggleVisibilityAction::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedModel)
    try
    {
        std::shared_ptr<AdaptiveCards::ToggleVisibilityAction> toggleVisibilityAction =
            std::make_shared<AdaptiveCards::ToggleVisibilityAction>();
        RETURN_IF_FAILED(CopySharedElementProperties(*toggleVisibilityAction));

        RETURN_IF_FAILED(GenerateSharedToggleElements(m_targetElements.Get(), toggleVisibilityAction->GetTargetElements()));

        sharedModel = std::move(toggleVisibilityAction);
        return S_OK;
    }
    CATCH_RETURN;
}
