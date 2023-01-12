// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "CustomElementWrapper.h"

namespace AdaptiveCards::ObjectModel::Xaml_OM
{
    CustomElementWrapper::CustomElementWrapper(winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveCardElement const& cardElement) :
        BaseCardElement(AdaptiveCards::CardElementType::Custom), m_cardElement(cardElement)
    {
        BaseElement::SetId(GetCardElementId());
    }

    bool CustomElementWrapper::GetSeparator() const
    {
        return m_cardElement.Separator();
    }

    void CustomElementWrapper::SetSeparator(bool value) { m_cardElement.Separator(value); }

    Spacing CustomElementWrapper::GetSpacing() const
    {
        return static_cast<Spacing>(m_cardElement.Spacing());
    }

    void CustomElementWrapper::SetSpacing(Spacing value)
    {
        m_cardElement.Spacing(static_cast<winrt::AdaptiveCards::ObjectModel::Xaml_OM::Spacing>(value));
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
        return JsonObjectToJsonCpp(m_cardElement.ToJson());
    }

    void CustomElementWrapper::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
    {
        if (auto remoteResources =
                m_cardElement.as<winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveElementWithRemoteResources>())
        {
            RemoteResourceElementToRemoteResourceInformationVector(remoteResources, resourceInfo);
        }
    }

    winrt::AdaptiveCards::ObjectModel::Xaml_OM::IAdaptiveCardElement CustomElementWrapper::GetWrappedElement()
    {
        return m_cardElement;
    }

    std::string CustomElementWrapper::GetCardElementId() const
    {
        return HStringToUTF8(m_cardElement.Id());
    }

    void CustomElementWrapper::SetCardElementId(const std::string& value)
    {
        m_cardElement.Id(UTF8ToHString(value));
    }
}
