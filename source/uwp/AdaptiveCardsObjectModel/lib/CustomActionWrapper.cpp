// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "CustomActionWrapper.h"

namespace AdaptiveCards::ObjectModel::Uwp
{
    CustomActionWrapper::CustomActionWrapper(_In_ winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement const& actionElement) :
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
        auto jsonObject = m_actionElement.ToJson();
        return JsonObjectToJsonCpp(jsonObject);
    }

    winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveActionElement CustomActionWrapper::GetWrappedElement()
    {
        return m_actionElement;
    }

    void CustomActionWrapper::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
    {
        if (auto resources = m_actionElement.try_as<winrt::AdaptiveCards::ObjectModel::Uwp::IAdaptiveElementWithRemoteResources>())
        {
            RemoteResourceElementToRemoteResourceInformationVector(resources, resourceInfo);
        }
    }

    std::string CustomActionWrapper::GetActionElementId() const { return HStringToUTF8(m_actionElement.Id()); }

    void CustomActionWrapper::SetActionElementId(const std::string& value) { m_actionElement.Id(UTF8ToHString(value)); }

    std::string CustomActionWrapper::GetActionElementTitle() const
    {
        try
        {
            return HStringToUTF8(m_actionElement.Title());
        }
        catch (...)
        {
            return "";
        }
    }

    void CustomActionWrapper::SetActionElementTitle(const std::string& value)
    {
        m_actionElement.Title(UTF8ToHString(value));
    }
}
