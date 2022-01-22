// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "BaseActionElement.h"
#include "ActionParserRegistration.h"
#include "ToggleVisibilityTarget.h"

namespace AdaptiveCards
{
class ToggleVisibilityAction : public BaseActionElement
{
    friend class ToggleVisibilityActionParser;

public:
    ToggleVisibilityAction();

    const std::vector<std::shared_ptr<ToggleVisibilityTarget>>& GetTargetElements() const;
    std::vector<std::shared_ptr<ToggleVisibilityTarget>>& GetTargetElements();

    Json::Value SerializeToJsonValue() const override;

private:
    void PopulateKnownPropertiesSet();

    std::vector<std::shared_ptr<ToggleVisibilityTarget>> m_targetElements;
};

class ToggleVisibilityActionParser : public ActionElementParser
{
public:
    ToggleVisibilityActionParser() = default;
    ToggleVisibilityActionParser(const ToggleVisibilityActionParser&) = default;
    ToggleVisibilityActionParser(ToggleVisibilityActionParser&&) = default;
    ToggleVisibilityActionParser& operator=(const ToggleVisibilityActionParser&) = default;
    ToggleVisibilityActionParser& operator=(ToggleVisibilityActionParser&&) = default;
    virtual ~ToggleVisibilityActionParser() = default;

    std::shared_ptr<BaseActionElement> Deserialize(ParseContext& context, const Json::Value& value) override;
    std::shared_ptr<BaseActionElement> DeserializeFromString(ParseContext& context, const std::string& jsonString) override;
};
} // namespace AdaptiveCards
