// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "BaseActionElement.h"
#include "BaseElement.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

constexpr const char* const BaseActionElement::defaultStyle;

BaseActionElement::BaseActionElement(ActionType type) :
    m_style(BaseActionElement::defaultStyle), m_type(type)
{
    SetTypeString(ActionTypeToString(type));
    PopulateKnownPropertiesSet();
}

std::string BaseActionElement::GetTitle() const
{
    return m_title;
}

void BaseActionElement::SetTitle(const std::string& value)
{
    m_title = value;
}

std::string BaseActionElement::GetIconUrl() const
{
    return m_iconUrl;
}

void BaseActionElement::SetIconUrl(const std::string& value)
{
    m_iconUrl = value;
}

std::string BaseActionElement::GetStyle() const
{
    return m_style;
}

void BaseActionElement::SetStyle(const std::string& value)
{
    m_style = value;
}

const ActionType BaseActionElement::GetElementType() const
{
    return m_type;
}

Json::Value BaseActionElement::SerializeToJsonValue() const
{
    Json::Value root = BaseElement::SerializeToJsonValue();

    if (!m_iconUrl.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IconUrl)] = m_iconUrl;
    }

    if (!m_title.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title)] = m_title;
    }

    if (!m_style.empty() && (m_style.compare(defaultStyle) != 0))
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style)] = m_style;
    }

    return root;
}

void BaseActionElement::PopulateKnownPropertiesSet()
{
    m_knownProperties.insert({AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::IconUrl),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Style),
                              AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title)});
}

void BaseActionElement::GetResourceInformation(std::vector<RemoteResourceInformation>& resourceInfo)
{
    if (!m_iconUrl.empty())
    {
        RemoteResourceInformation imageResourceInfo;
        imageResourceInfo.url = m_iconUrl;
        imageResourceInfo.mimeType = "image";
        resourceInfo.push_back(imageResourceInfo);
    }
}

void BaseActionElement::ParseJsonObject(AdaptiveSharedNamespace::ParseContext& context,
                                        const Json::Value& json,
                                        std::shared_ptr<BaseElement>& baseElement)
{
    baseElement = ParseUtil::GetActionFromJsonValue(context, json);
}
