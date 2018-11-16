#include "pch.h"
#include "AdaptiveToggleViewStateAction.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;
using namespace ABI::Windows::Data::Json;

namespace AdaptiveNamespace
{
    HRESULT AdaptiveToggleViewStateAction::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ToggleViewStateAction> toggleViewStateAction =
            std::make_shared<AdaptiveSharedNamespace::ToggleViewStateAction>();
        return RuntimeClassInitialize(toggleViewStateAction);
    }
    CATCH_RETURN;

    _Use_decl_annotations_ HRESULT AdaptiveToggleViewStateAction::RuntimeClassInitialize(
        const std::shared_ptr<AdaptiveSharedNamespace::ToggleViewStateAction>& sharedToggleViewStateAction) try
    {
        if (sharedToggleViewStateAction == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(UTF8ToHString(sharedToggleViewStateAction->GetToggleId(), m_toggleId.GetAddressOf()));

        InitializeBaseElement(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(sharedToggleViewStateAction));
        return S_OK;
    }
    CATCH_RETURN;

    _Use_decl_annotations_ HRESULT AdaptiveToggleViewStateAction::get_ActionType(ABI::AdaptiveNamespace::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveNamespace::ActionType::ToggleViewState;
        return S_OK;
    }

    _Use_decl_annotations_ HRESULT AdaptiveToggleViewStateAction::get_ToggleId(HSTRING* toggleId)
    {
        return m_toggleId.CopyTo(toggleId);
    }

    _Use_decl_annotations_ HRESULT AdaptiveToggleViewStateAction::put_ToggleId(HSTRING toggleId)
    {
        return m_toggleId.Set(toggleId);
    }

    HRESULT AdaptiveToggleViewStateAction::GetSharedModel(std::shared_ptr<AdaptiveSharedNamespace::BaseActionElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveSharedNamespace::ToggleViewStateAction> toggleViewStateAction =
            std::make_shared<AdaptiveSharedNamespace::ToggleViewStateAction>();
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveSharedNamespace::BaseActionElement>(toggleViewStateAction)));

        std::string toggleId;
        RETURN_IF_FAILED(HStringToUTF8(m_toggleId.Get(), toggleId));
        toggleViewStateAction->SetToggleId(toggleId);

        sharedModel = toggleViewStateAction;
        return S_OK;
    }
    CATCH_RETURN;
}
