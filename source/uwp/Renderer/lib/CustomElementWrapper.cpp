#include "pch.h"
#include "CustomElementWrapper.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::Rendering::Uwp;

namespace AdaptiveCards { namespace Rendering { namespace Uwp
{

    bool CustomElementWrapper::GetSeparator() const
    {
        boolean hasSeparator;
        THROW_IF_FAILED(m_cardElement->get_Separator(&hasSeparator));
        return hasSeparator;
    }

    void CustomElementWrapper::SetSeparator(const bool value)
    {
        THROW_IF_FAILED(m_cardElement->put_Separator(value));
    }

    Spacing CustomElementWrapper::GetSpacing() const
    {
        ABI::AdaptiveCards::Rendering::Uwp::Spacing spacing;
        THROW_IF_FAILED(m_cardElement->get_Spacing(&spacing));

        return static_cast<Spacing> (spacing);
    }

    void CustomElementWrapper::SetSpacing(const Spacing value)
    {
        THROW_IF_FAILED(m_cardElement->put_Spacing(static_cast<ABI::AdaptiveCards::Rendering::Uwp::Spacing>(value)));
    }

    std::string CustomElementWrapper::GetId() const
    {
        Wrappers::HString id; 
        THROW_IF_FAILED(m_cardElement->get_Id(id.GetAddressOf()));
        return HStringToUTF8(id.Get());
    }

    void CustomElementWrapper::SetId(const std::string value)
    {
        Wrappers::HString id; 
        THROW_IF_FAILED(UTF8ToHString(value, id.GetAddressOf()));
        THROW_IF_FAILED(m_cardElement->put_Id(id.Get()));
    }

    Json::Value CustomElementWrapper::SerializeToJsonValue()
    {
        ComPtr<ABI::Windows::Data::Json::IJsonObject> jsonObject;
        THROW_IF_FAILED(m_cardElement->ToJson(&jsonObject));

        Json::Value jsonCppValue;
        JsonObjectToJsonCpp(jsonObject.Get(), &jsonCppValue);

        return jsonCppValue;
    }

    HRESULT CustomElementWrapper::GetWrappedElement(ABI::AdaptiveCards::Rendering::Uwp::IAdaptiveCardElement** cardElement)
    {
        return m_cardElement.CopyTo(cardElement);
    }
}}}
