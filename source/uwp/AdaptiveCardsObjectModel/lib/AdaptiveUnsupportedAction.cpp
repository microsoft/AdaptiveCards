// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveUnsupportedAction.h"

using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveCards::ObjectModel::Uwp
{
    HRESULT AdaptiveUnsupportedAction::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveCards::UnknownAction> unknownAction = std::make_shared<AdaptiveCards::UnknownAction>();
        return RuntimeClassInitialize(unknownAction);
    }
    CATCH_RETURN;

    HRESULT AdaptiveUnsupportedAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::UnknownAction>& sharedUnknown)
    try
    {
        if (sharedUnknown == nullptr)
        {
            return E_INVALIDARG;
        }

        InitializeBaseElement(std::static_pointer_cast<BaseActionElement>(sharedUnknown));
        return S_OK;
    }
    CATCH_RETURN;

    HRESULT AdaptiveUnsupportedAction::get_ActionType(_Out_ ABI::AdaptiveCards::ObjectModel::Uwp::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveCards::ObjectModel::Uwp::ActionType::Unsupported;
        return S_OK;
    }

    HRESULT AdaptiveUnsupportedAction::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedUnknown)
    try
    {
        std::shared_ptr<AdaptiveCards::UnknownAction> unknownAction = std::make_shared<AdaptiveCards::UnknownAction>();

        HString typeString;
        RETURN_IF_FAILED(get_ActionTypeString(typeString.GetAddressOf()));
        unknownAction->SetElementTypeString(HStringToUTF8(typeString.Get()));
        RETURN_IF_FAILED(CopySharedElementProperties(*unknownAction));

        sharedUnknown = std::move(unknownAction);
        return S_OK;
    }
    CATCH_RETURN;
}
