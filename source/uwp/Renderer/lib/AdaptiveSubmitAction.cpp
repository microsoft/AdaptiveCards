#include "pch.h"
#include "AdaptiveSubmitAction.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespaceRef;
using namespace ABI::Windows::Data::Json;

AdaptiveNamespaceStart
    HRESULT AdaptiveSubmitAction::RuntimeClassInitialize() noexcept try
    {
        std::shared_ptr<AdaptiveCards::SubmitAction> submitAction = std::make_shared<AdaptiveCards::SubmitAction>();
        return RuntimeClassInitialize(submitAction);
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::SubmitAction>& sharedSubmitAction) try
    {
        if (sharedSubmitAction == nullptr)
        {
            return E_INVALIDARG;
        }

        RETURN_IF_FAILED(StringToJsonValue(sharedSubmitAction->GetDataJson(), &m_dataJson));
        InitializeBaseElement(std::static_pointer_cast<AdaptiveCards::BaseActionElement>(sharedSubmitAction));
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::get_ActionType(ABI::AdaptiveNamespaceRef::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveNamespaceRef::ActionType::Submit;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::get_DataJson(IJsonValue** data)
    {
        return m_dataJson.CopyTo(data);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::put_DataJson(IJsonValue* data)
    {
        m_dataJson = data;
        return S_OK;
    }

    HRESULT AdaptiveSubmitAction::GetSharedModel(std::shared_ptr<AdaptiveCards::BaseActionElement>& sharedModel) try
    {
        std::shared_ptr<AdaptiveCards::SubmitAction> submitAction = std::make_shared<AdaptiveCards::SubmitAction>();
        RETURN_IF_FAILED(SetSharedElementProperties(std::static_pointer_cast<AdaptiveCards::BaseActionElement>(submitAction)));

        std::string jsonAsString;
        RETURN_IF_FAILED(JsonValueToString(m_dataJson.Get(), jsonAsString));
        submitAction->SetDataJson(jsonAsString);

        sharedModel = submitAction;
        return S_OK;
    }CATCH_RETURN;
AdaptiveNamespaceEnd
