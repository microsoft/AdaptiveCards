// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "AuthCardButton.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;

std::string AuthCardButton::GetType()
{
    return m_type;
}

const std::string AuthCardButton::GetType() const
{
    return m_type;
}

void AuthCardButton::SetType(std::string type)
{
    m_type = type;
}

std::string AuthCardButton::GetTitle()
{
    return m_title;
}

const std::string AuthCardButton::GetTitle() const
{
    return m_title;
}

void AuthCardButton::SetTitle(std::string title)
{
    m_title = title;
}

std::string AuthCardButton::GetImage()
{
    return m_image;
}

const std::string AuthCardButton::GetImage() const
{
    return m_image;
}

void AuthCardButton::SetImage(std::string image)
{
    m_image = image;
}

std::string AuthCardButton::GetValue()
{
    return m_value;
}

const std::string AuthCardButton::GetValue() const
{
    return m_value;
}

void AuthCardButton::SetValue(std::string value)
{
    m_value = value;
}

// Indicates non-default values have been set. If false, serialization can be safely skipped.
bool AuthCardButton::ShouldSerialize() const
{
    return !m_type.empty() || !m_title.empty() || !m_image.empty() || !m_value.empty();
}

std::string AuthCardButton::Serialize() const
{
    return ParseUtil::JsonToString(SerializeToJsonValue());
}

Json::Value AuthCardButton::SerializeToJsonValue() const
{
    Json::Value root;

    if (!m_type.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Type)] = m_type;
    }

    if (!m_title.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Title)] = m_title;
    }

    if (!m_image.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Image)] = m_image;
    }

    if (!m_value.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Value)] = m_value;
    }

    return root;
}

std::shared_ptr<AuthCardButton> AuthCardButton::Deserialize(ParseContext&, const Json::Value& json)
{
    std::shared_ptr<AuthCardButton> button = std::make_shared<AuthCardButton>();

    button->SetType(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Type));
    button->SetTitle(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Title));
    button->SetImage(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Image));
    button->SetValue(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Value));

    return button;
}

std::shared_ptr<AuthCardButton> AuthCardButton::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return AuthCardButton::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
