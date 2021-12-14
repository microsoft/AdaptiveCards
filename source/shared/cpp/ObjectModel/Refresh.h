// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseActionElement.h"

namespace AdaptiveCards
{
class Refresh
{
public:
    Refresh()
    {
    }
    Refresh(std::shared_ptr<BaseActionElement> action, const std::vector<std::string> userIds) :
        m_action(action), m_userIds(userIds)
    {
    }

    std::shared_ptr<BaseActionElement> GetAction();
    const std::shared_ptr<BaseActionElement> GetAction() const;
    void SetAction(std::shared_ptr<BaseActionElement>);

    std::vector<std::string>& GetUserIds();
    const std::vector<std::string>& GetUserIds() const;
    void SetUserIds(std::vector<std::string>);

    bool ShouldSerialize() const;
    std::string Serialize() const;
    Json::Value SerializeToJsonValue() const;

    static std::shared_ptr<Refresh> Deserialize(ParseContext& context, const Json::Value& json);
    static std::shared_ptr<Refresh> DeserializeFromString(ParseContext& context, const std::string& jsonString);

private:
    std::shared_ptr<BaseActionElement> m_action;
    std::vector<std::string> m_userIds;
};
} // namespace AdaptiveCards
