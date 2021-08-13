// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "CustomActionWrapper.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;

namespace AdaptiveCards::ObjectModel::Uwp
{
    CustomActionWrapper::CustomActionWrapper(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement* actionElement) :
        AdaptiveCards::BaseActionElement(AdaptiveCards::ActionType::Custom), m_actionElement(actionElement)
    {
        BaseElement::SetId(GetActionElementId());
        BaseActionElement::SetTitle(GetActionElementTitle());
    }

    void CustomActionWrapper::SetId(std::string&& value)
    {
        SetActionElementId(value);
        BaseElement::SetId(std::move(value));
    }

    void CustomActionWrapper::SetId(const std::string& value)
    {
        SetActionElementId(value);
        BaseElement::SetId(value);
    }

    void CustomActionWrapper::SetTitle(std::string&& value)
    {
        SetActionElementTitle(value);
        BaseActionElement::SetTitle(std::move(value));
    }

    void CustomActionWrapper::SetTitle(const std::string& value)
    {
        SetActionElementTitle(value);
        BaseActionElement::SetTitle(value);
    }

    Json::Value CustomActionWrapper::SerializeToJsonValue() const
    {
        ComPtr<ABI::Windows::Data::Json::IJsonObject> jsonObject;
        THROW_IF_FAILED(m_actionElement->ToJson(&jsonObject));

        Json::Value jsonCppValue;
        JsonObjectToJsonCpp(jsonObject.Get(), &jsonCppValue);

        return jsonCppValue;
    }

    HRESULT CustomActionWrapper::GetWrappedElement(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement** actionElement)
    {
        return m_actionElement.CopyTo(actionElement);
    }

    void CustomActionWrapper::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
    {
        ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementWithRemoteResources> remoteResources;
        if (SUCCEEDED(m_actionElement.As(&remoteResources)))
        {
            RemoteResourceElementToRemoteResourceInformationVector(remoteResources.Get(), resourceInfo);
        }
    }

    std::string CustomActionWrapper::GetActionElementId() const
    {
        Wrappers::HString id;
        THROW_IF_FAILED(m_actionElement->get_Id(id.GetAddressOf()));
        return HStringToUTF8(id.Get());
    }

    void CustomActionWrapper::SetActionElementId(const std::string& value)
    {
        Wrappers::HString id;
        THROW_IF_FAILED(UTF8ToHString(value, id.GetAddressOf()));
        THROW_IF_FAILED(m_actionElement->put_Id(id.Get()));
    }

    std::string CustomActionWrapper::GetActionElementTitle() const
    {
        Wrappers::HString title;
        if (SUCCEEDED(m_actionElement->get_Title(title.GetAddressOf())) && title.IsValid())
        {
            return HStringToUTF8(title.Get());
        }
        else
        {
            return "";
        }
    }

    void CustomActionWrapper::SetActionElementTitle(const std::string& value)
    {
        Wrappers::HString title;
        THROW_IF_FAILED(UTF8ToHString(value, title.GetAddressOf()));
        THROW_IF_FAILED(m_actionElement->put_Title(title.Get()));
    }
}
