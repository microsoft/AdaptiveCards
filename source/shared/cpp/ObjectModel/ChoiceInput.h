// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
#pragma once

#include "pch.h"
#include "ParseContext.h"

namespace AdaptiveCards
{
class ChoiceInput
{
public:
    ChoiceInput();

    std::string Serialize();
    Json::Value SerializeToJsonValue();

    std::string GetTitle() const;
    void SetTitle(const std::string& value);

    std::string GetValue() const;
    void SetValue(const std::string& value);

    static std::shared_ptr<ChoiceInput> Deserialize(ParseContext&, const Json::Value& root);
    static std::shared_ptr<ChoiceInput> DeserializeFromString(ParseContext&, const std::string& jsonString);

private:
    std::string m_title;
    std::string m_value;
};
} // namespace AdaptiveCards
