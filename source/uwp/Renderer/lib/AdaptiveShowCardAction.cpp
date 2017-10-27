#include "pch.h"
#include "AdaptiveCard.h"
#include "AdaptiveShowCardAction.h"
#include "Util.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Uwp;

namespace AdaptiveCards { namespace Uwp
{
    HRESULT AdaptiveShowCardAction::RuntimeClassInitialize() noexcept try
    {
        m_sharedShowCardAction = std::make_shared<ShowCardAction>();
        return S_OK;
    } CATCH_RETURN;

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::RuntimeClassInitialize(const std::shared_ptr<AdaptiveCards::ShowCardAction>& sharedShowCardAction)
    {
        if (sharedShowCardAction == nullptr)
        {
            return E_INVALIDARG;
        }

        m_sharedShowCardAction = sharedShowCardAction;
        return S_OK;
    }

    IFACEMETHODIMP AdaptiveShowCardAction::get_Card(ABI::AdaptiveCards::Uwp::IAdaptiveCard** card)
    {
        return MakeAndInitialize<AdaptiveCard>(card, m_sharedShowCardAction->GetCard());
    }

    IFACEMETHODIMP AdaptiveShowCardAction::put_Card(ABI::AdaptiveCards::Uwp::IAdaptiveCard* /*card*/)
    {
        return E_NOTIMPL;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::get_Title(HSTRING* title)
    {
        return UTF8ToHString(m_sharedShowCardAction->GetTitle(), title);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::put_Title(HSTRING title)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(title, out));
        m_sharedShowCardAction->SetTitle(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::get_ActionType(ABI::AdaptiveCards::Uwp::ActionType* actionType)
    {
        *actionType = ABI::AdaptiveCards::Uwp::ActionType::ShowCard;
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::get_Id(HSTRING* id)
    {
        return UTF8ToHString(m_sharedShowCardAction->GetId(), id);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::put_Id(HSTRING id)
    {
        std::string out;
        RETURN_IF_FAILED(HStringToUTF8(id, out));
        m_sharedShowCardAction->SetId(out);
        return S_OK;
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::get_ActionTypeString(HSTRING* type)
    {
        ::ActionType typeEnum;
        RETURN_IF_FAILED(get_ActionType(&typeEnum));
        return ProjectedActionTypeToHString(typeEnum, type);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::get_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject** result)
    {
        return JsonCppToJsonObject(m_sharedShowCardAction->GetAdditionalProperties(), result);
    }

    _Use_decl_annotations_
    HRESULT AdaptiveShowCardAction::put_AdditionalProperties(ABI::Windows::Data::Json::IJsonObject* jsonObject)
    {
        Json::Value jsonCpp;
        RETURN_IF_FAILED(JsonObjectToJsonCpp(jsonObject, &jsonCpp));
        m_sharedShowCardAction->SetAdditionalProperties(jsonCpp);
        return S_OK;
    }
}}
