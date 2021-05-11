// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#include "pch.h"
#include "Refresh.h"
#include "ParseUtil.h"

using namespace AdaptiveCards;

std::shared_ptr<BaseActionElement> Refresh::GetAction()
{
    return m_action;
}

const std::shared_ptr<BaseActionElement> Refresh::GetAction() const
{
    return m_action;
}

void Refresh::SetAction(std::shared_ptr<BaseActionElement> action)
{
    m_action = action;
}

std::vector<std::string>& Refresh::GetUserIds()
{
    return m_userIds;
}

const std::vector<std::string>& Refresh::GetUserIds() const
{
    return m_userIds;
}

void Refresh::SetUserIds(std::vector<std::string> userIds)
{
    m_userIds = userIds;
}

// Indicates non-default values have been set. If false, serialization can be safely skipped.
bool Refresh::ShouldSerialize() const
{
    return (m_action != nullptr) || !m_userIds.empty();
}

std::string Refresh::Serialize() const
{
    return ParseUtil::JsonToString(SerializeToJsonValue());
}

Json::Value Refresh::SerializeToJsonValue() const
{
    Json::Value root;

    if (m_action != nullptr)
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::Action)] = m_action->SerializeToJsonValue();
    }

    if (!m_userIds.empty())
    {
        root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::UserIds)] = Json::Value(Json::arrayValue);
        for (std::string userId : m_userIds)
        {
            root[AdaptiveCardSchemaKeyToString(AdaptiveCardSchemaKey::UserIds)].append(userId);
        }
    }

    return root;
}

std::shared_ptr<Refresh> Refresh::Deserialize(ParseContext& context, const Json::Value& json)
{
    std::shared_ptr<Refresh> refresh = std::make_shared<Refresh>();

    refresh->SetAction(ParseUtil::GetAction(context, json, AdaptiveCardSchemaKey::Action));
    refresh->SetUserIds(std::move(ParseUtil::GetStringArray(json, AdaptiveCardSchemaKey::UserIds)));

    return refresh;
}

std::shared_ptr<Refresh> Refresh::DeserializeFromString(ParseContext& context, const std::string& jsonString)
{
    return Refresh::Deserialize(context, ParseUtil::GetJsonValueFromString(jsonString));
}
