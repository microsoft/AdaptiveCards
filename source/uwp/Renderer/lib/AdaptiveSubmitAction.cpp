#include "pch.h"
#include "AdaptiveSubmitAction.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Uwp;
using namespace ABI::Windows::Data::Json;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveSubmitAction::RuntimeClassInitialize() noexcept try
    {
        m_sharedSubmitAction = std::make_shared<SubmitAction>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::SubmitAction>& sharedSubmitAction)
    {
        if (sharedSubmitAction == nullptr)
        {
            return E_INVALIDARG;
        }

        m_sharedSubmitAction = sharedSubmitAction;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::get_Title(HSTRING* title)
    {
        return UTF8ToHString(m_sharedSubmitAction->GetTitle(), title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::put_Title(HSTRING title)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(title, out));
        m_sharedSubmitAction->SetTitle(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::get_ActionType(ABI::AdaptiveCards::Uwp::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveCards::Uwp::ActionType::Submit;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::get_DataJson(IJsonObject** data)
    {
        return StringToJsonObject(m_sharedSubmitAction->GetDataJson(), data);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::put_DataJson(IJsonObject* data)
    {
        std::string jsonAsString;
        RETURN_IF_FAILED(JsonObjectToString(data, jsonAsString));
        m_sharedSubmitAction->SetDataJson(jsonAsString);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedSubmitAction->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedSubmitAction->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::get_ActionTypeString(HSTRING* type)
    {
        ::ActionType typeEnum;
        RETURN_IF_FAILED(get_ActionType(&typeEnum));
        return ProjectedActionTypeToHString(typeEnum, type);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return JsonCppToJsonObject(m_sharedSubmitAction->GetAdditionalProperties(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveSubmitAction::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        Json::Value jsonCpp;
        RETURN_IF_FAILED(JsonObjectToJsonCpp(jsonObject, &jsonCpp));
        m_sharedSubmitAction->SetAdditionalProperties(jsonCpp);
        return S_OK;
    }
}}
