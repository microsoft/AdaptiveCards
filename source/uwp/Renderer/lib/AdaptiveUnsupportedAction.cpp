#include "pch.h"

#include "AdaptiveUnsupportedAction.h"

#include "Util.h"
#include <windows.foundation.collections.h>

using namespace Microsoft::WRL;
using namespace Microsoft::WRL::Wrappers;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Foundation::Collections;
using namespace ABI::Windows::UI::Xaml;
using namespace ABI::Windows::UI::Xaml::Controls;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveUnsupportedAction::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::UnknownAction> unknownAction =
            std::make_shared<AdaptiveSharedNamespace::UnknownAction>();
        return RuntimeClassInitialize(unknownAction);
    }
    CATCH_RETURN;

    HRESULT AdaptiveUnsupportedAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveSharedNamespace::UnknownAction>& sharedUnknown) try
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

    HRESULT AdaptiveUnsupportedAction::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedUnknown) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::UnknownAction> unknownAction =
            std::make_shared<AdaptiveSharedNamespace::UnknownAction>();

        HString typeString;
        RETURN_IF_FAILED(get_ActionTypeString(typeString.GetAddressOf()));
        unknownAction->SetElementTypeString(HStringToUTF8(typeString.Get()));
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(unknownAction)));

        sharedUnknown = unknownAction;
        return S_OK;
    }
    CATCH_RETURN;
}
