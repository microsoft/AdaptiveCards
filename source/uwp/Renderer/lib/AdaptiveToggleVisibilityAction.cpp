// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveToggleVisibilityAction.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;
using namespace ABI::Windows::Foundation::Collections;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveToggleVisibilityAction::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityAction> toggleVisibilityAction =
            std::make_shared<AdaptiveSharedNamespace::ToggleVisibilityAction>();
        return RuntimeClassInitialize(toggleVisibilityAction);
    }
    CATCH_RETURN;

    HRESULT AdaptiveToggleVisibilityAction::RuntimeClassInitialize(
        const std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityAction>& sharedToggleVisibilityAction) try
    {
        if (sharedToggleVisibilityAction == nullptr)
        {
            return E_INVALIDARG;
        }

        m_targetElements = Microsoft::WRL::Make<Vector<AdaptiveToggleVisibilityTarget*>>();
        GenerateToggleTargetProjection(sharedToggleVisibilityAction->GetTargetElements(), m_targetElements.Get());

        InitializeBaseElement(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(sharedToggleVisibilityAction));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveToggleVisibilityAction::get_ActionType(_Out_ ABI::AdaptiveNamespace::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveNamespace::ActionType::ToggleVisibility;
        return S_OK;
    }

    HRESULT AdaptiveToggleVisibilityAction::get_TargetElements(_COM_Outptr_ IVector<AdaptiveToggleVisibilityTarget*>** targetElements)
    {
        return m_targetElements.CopyTo(targetElements);
    }

    HRESULT AdaptiveToggleVisibilityAction::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ToggleVisibilityAction> toggleVisibilityAction =
            std::make_shared<AdaptiveSharedNamespace::ToggleVisibilityAction>();
        RETURN_IF_FAILED(SetSharedElementProperties(
            std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(toggleVisibilityAction)));

        RETURN_IF_FAILED(GenerateSharedToggleElements(m_targetElements.Get(), toggleVisibilityAction->GetTargetElements()));

        sharedModel = toggleVisibilityAction;
        return S_OK;
    }
    CATCH_RETURN;
}
