// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "ActionParserRegistration.h"

namespace AdaptiveCards
{
enum IsVisible
{
    IsVisibleToggle,
    IsVisibleTrue,
    IsVisibleFalse
};

class ToggleVisibilityTarget
{
public:
    ToggleVisibilityTarget();

    std::string GetElementId() const;
    void SetElementId(const std::string& value);

    IsVisible GetIsVisible() const;
    void SetIsVisible(IsVisible value);

    std::string Serialize();
    Json::Value SerializeToJsonValue();

    static std::shared_ptr<ToggleVisibilityTarget> Deserialize(ParseContext& context, const Json::Value& root);
    static std::shared_ptr<ToggleVisibilityTarget> DeserializeFromString(ParseContext& context, const std::string& jsonString);

private:
    std::string m_targetId;
    IsVisible m_visibilityToggle;
};
} // namespace AdaptiveCards
