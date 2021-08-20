// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "CustomElementWrapper.h"

using namespace Microsoft::WRL;
using namespace ABI::AdaptiveCards::ObjectModel::Uwp;

namespace AdaptiveCards::ObjectModel::Uwp
{
    CustomElementWrapper::CustomElementWrapper(_In_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement* cardElement) :
        BaseCardElement(AdaptiveCards::CardElementType::Custom), m_cardElement(cardElement)
    {
        BaseElement::SetId(GetCardElementId());
    }

    bool CustomElementWrapper::GetSeparator() const
    {
        boolean hasSeparator;
        THROW_IF_FAILED(m_cardElement->get_Separator(&hasSeparator));
        return hasSeparator;
    }

    void CustomElementWrapper::SetSeparator(bool value) { THROW_IF_FAILED(m_cardElement->put_Separator(value)); }

    Spacing CustomElementWrapper::GetSpacing() const
    {
        ABI::AdaptiveCards::ObjectModel::Uwp::Spacing spacing;
        THROW_IF_FAILED(m_cardElement->get_Spacing(&spacing));

        return static_cast<Spacing>(spacing);
    }

    void CustomElementWrapper::SetSpacing(Spacing value)
    {
        THROW_IF_FAILED(m_cardElement->put_Spacing(static_cast<ABI::AdaptiveCards::ObjectModel::Uwp::Spacing>(value)));
    }

    void CustomElementWrapper::SetId(std::string&& value)
    {
        SetCardElementId(value);
        BaseElement::SetId(std::move(value));
    }

    void CustomElementWrapper::SetId(const std::string& value)
    {
        SetCardElementId(value);
        BaseElement::SetId(value);
    }

    Json::Value CustomElementWrapper::SerializeToJsonValue() const
    {
        ComPtr<ABI::Windows::Data::Json::IJsonObject> jsonObject;
        THROW_IF_FAILED(m_cardElement->ToJson(&jsonObject));

        Json::Value jsonCppValue;
        JsonObjectToJsonCpp(jsonObject.Get(), &jsonCppValue);

        return jsonCppValue;
    }

    void CustomElementWrapper::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
    {
        ComPtr<ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementWithRemoteResources> remoteResources;
        if (SUCCEEDED(m_cardElement.As(&remoteResources)))
        {
            RemoteResourceElementToRemoteResourceInformationVector(remoteResources.Get(), resourceInfo);
        }
    }

    HRESULT CustomElementWrapper::GetWrappedElement(_COM_Outptr_ ABI::AdaptiveCards::ObjectModel::Uwp::IAdaptiveCardElement** cardElement)
    {
        return m_cardElement.CopyTo(cardElement);
    }

    std::string CustomElementWrapper::GetCardElementId() const
    {
        Wrappers::HString id;
        THROW_IF_FAILED(m_cardElement->get_Id(id.GetAddressOf()));
        return HStringToUTF8(id.Get());
    }

    void CustomElementWrapper::SetCardElementId(const std::string& value)
    {
        Wrappers::HString id;
        THROW_IF_FAILED(UTF8ToHString(value, id.GetAddressOf()));
        THROW_IF_FAILED(m_cardElement->put_Id(id.Get()));
    }
}
