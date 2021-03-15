// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Authentication.h"
#include "ParseUtil.h"

using namespace AdaptiveSharedNamespace;


std::string Authentication::GetText()
{
    return m_text;
}

const std::string Authentication::GetText() const
{
    return m_text;
}

void Authentication::SetText(std::string text)
{
    m_text = text;
}

std::string Authentication::GetConnectionName()
{
    return m_connectionName;
}

const std::string Authentication::GetConnectionName() const
{
    return m_connectionName;
}

void Authentication::SetConnectionName(std::string connectionName)
{
    m_connectionName = connectionName;
}

std::shared_ptr<TokenExchangeResource> Authentication::GetTokenExchangeResource()
{
    return m_tokenExchangeResource;
}

const std::shared_ptr<TokenExchangeResource> Authentication::GetTokenExchangeResource() const
{
    return m_tokenExchangeResource;
}

void Authentication::SetTokenExchangeResource(std::shared_ptr<TokenExchangeResource> tokenExchangeResource)
{
    m_tokenExchangeResource = tokenExchangeResource;
}

std::vector<std::shared_ptr<AuthCardButton>>& AdaptiveSharedNamespace::Authentication::GetButtons()
{
    return m_buttons;
}

const std::vector<std::shared_ptr<AuthCardButton>>& AdaptiveSharedNamespace::Authentication::GetButtons() const
{
    return m_buttons;
}

void AdaptiveSharedNamespace::Authentication::SetButtons(std::vector<std::shared_ptr<AuthCardButton>> buttons)
{
    m_buttons = buttons;
}

// Indicates non-default values have been set. If false, serialization can be safely skipped.
bool Authentication::ShouldSerialize() const
{
    return !m_text.empty() || !m_connectionName.empty() || !m_buttons.empty() ||
        (m_tokenExchangeResource != nullptr && m_tokenExchangeResource->ShouldSerialize());
}

std::string Authentication::Serialize() const
{
    return ParseUtil::JsonToString(SerializeToJsonValue());
}

Json::Value Authentication::SerializeToJsonValue() const
{
    Json::Value root;

    if (!m_text.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Text)] = m_text;
    }

    if (!m_connectionName.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::ConnectionName)] = m_connectionName;
    }

    if (m_tokenExchangeResource != nullptr && m_tokenExchangeResource->ShouldSerialize())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::TokenExchangeResource)] = m_tokenExchangeResource->SerializeToJsonValue();
    }

    if (!m_buttons.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Buttons)] = Json::Value(Json::arrayValue);
        for (std::shared_ptr<AuthCardButton> button : m_buttons)
        {
            if (button != nullptr && button->ShouldSerialize())
            {
                root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Buttons)].append(button->SerializeToJsonValue());
            }
        }
    }

    return root;
}

std::shared_ptr<Authentication> Authentication::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<Authentication> authentication = std::make_shared<Authentication>();

    authentication->SetText(ParseUtil::GetString(json, AdaptiveCardSchemaKey::Text));
    authentication->SetConnectionName(ParseUtil::GetString(json, AdaptiveCardSchemaKey::ConnectionName));
    authentication->SetTokenExchangeResource(
        ParseUtil::DeserializeValue<TokenExchangeResource>(context, json, AdaptiveCardSchemaKey::TokenExchangeResource, TokenExchangeResource::Deserialize));
    authentication->SetButtons(std::move(
        ParseUtil::GetElementCollectionOfSingleType<AuthCardButton>(context, json, AdaptiveCardSchemaKey::Buttons, AuthCardButton::Deserialize)));

    return authentication;
}

std::shared_ptr<Authentication> Authentication::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return Authentication::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}

