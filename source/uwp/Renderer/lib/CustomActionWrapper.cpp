#include "pch.h"
#include "CustomActionWrapper.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveNamespace;

AdaptiveNamespaceStart

std::string CustomActionWrapper::GetId() const
{
    Wrappers::HString id;
    THROW_IF_FAILED(m_actionElement->get_Id(id.GetAddressOf()));
    return HStringToUTF8(id.Get());
}

void CustomActionWrapper::SetId(const std::string value)
{
    Wrappers::HString id;
    THROW_IF_FAILED(UTF8ToHString(value, id.GetAddressOf()));
    THROW_IF_FAILED(m_actionElement->put_Id(id.Get()));
}

std::string CustomActionWrapper::GetTitle() const
{
    Wrappers::HString title; 
    THROW_IF_FAILED(m_actionElement->get_Title(title.GetAddressOf()));
    return HStringToUTF8(title.Get());
}

void CustomActionWrapper::SetTitle(const std::string value)
{
    Wrappers::HString title; 
    THROW_IF_FAILED(UTF8ToHString(value, title.GetAddressOf()));
    THROW_IF_FAILED(m_actionElement->put_Title(title.Get()));
}

Json::Value CustomActionWrapper::SerializeToJsonValue()
{
    ComPtr<ABI::Windows::Data::Json::IJsonObject> jsonObject;
    THROW_IF_FAILED(m_actionElement->ToJson(&jsonObject));

    Json::Value jsonCppValue;
    JsonObjectToJsonCpp(jsonObject.Get(), &jsonCppValue);

    return jsonCppValue;
}

HRESULT CustomActionWrapper::GetWrappedElement(ABI::AdaptiveNamespace::IAdaptiveActionElement** actionElement)
{
    return m_actionElement.CopyTo(actionElement);
}

AdaptiveNamespaceEnd
