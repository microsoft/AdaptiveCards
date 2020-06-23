// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"

#include "AdaptiveUnsupportedAction.h"

using namespace Microsoft::WRL::Wrappers;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveUnsupportedAction::RuntimeClassInitialize() noexcept
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::UnknownAction> unknownAction =
            std::make_shared<AdaptiveSharedNamespace::UnknownAction>();
        return RuntimeClassInitialize(unknownAction);
    }
    CATCH_RETURN;

    HRESULT AdaptiveUnsupportedAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::UnknownAction>& sharedUnknown)
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

    HRESULT AdaptiveUnsupportedAction::get_ActionType(_Out_ ABI::AdaptiveNamespace::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveNamespace::ActionType::Unsupported;
        return S_OK;
    }

    HRESULT AdaptiveUnsupportedAction::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedUnknown)
    try
    {
        std::shared_ptr<AdaptiveSharedNamespace::UnknownAction> unknownAction =
            std::make_shared<AdaptiveSharedNamespace::UnknownAction>();

        HString typeString;
        RETURN_IF_FAILED(get_ActionTypeString(typeString.GetAddressOf()));
        unknownAction->SetElementTypeString(HStringToUTF8(typeString.Get()));
        RETURN_IF_FAILED(CopySharedElementProperties(*unknownAction));

        sharedUnknown = unknownAction;
        return S_OK;
    }
    CATCH_RETURN;
}
